# Network Programming

## Socket Programming Basics
```cpp
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class TCPServer {
private:
    int server_fd;
    struct sockaddr_in address;
    
public:
    TCPServer(int port) {
        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd == 0) {
            throw std::runtime_error("Socket creation failed");
        }
        
        int opt = 1;
        setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
        
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);
        
        if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
            throw std::runtime_error("Bind failed");
        }
        
        if (listen(server_fd, 3) < 0) {
            throw std::runtime_error("Listen failed");
        }
    }
    
    int acceptConnection() {
        int addrlen = sizeof(address);
        int client_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        if (client_socket < 0) {
            throw std::runtime_error("Accept failed");
        }
        return client_socket;
    }
    
    ~TCPServer() {
        close(server_fd);
    }
};
```

## HTTP Server
```cpp
#include <sstream>
#include <unordered_map>

class HTTPServer {
private:
    TCPServer server;
    std::unordered_map<std::string, std::function<std::string(const std::string&)>> routes;
    
public:
    HTTPServer(int port) : server(port) {}
    
    void addRoute(const std::string& path, std::function<std::string(const std::string&)> handler) {
        routes[path] = handler;
    }
    
    void start() {
        while (true) {
            int client_socket = server.acceptConnection();
            std::thread([this, client_socket]() {
                handleClient(client_socket);
            }).detach();
        }
    }
    
private:
    void handleClient(int client_socket) {
        char buffer[1024] = {0};
        read(client_socket, buffer, 1024);
        
        std::string request(buffer);
        auto [method, path, body] = parseRequest(request);
        
        std::string response;
        if (routes.find(path) != routes.end()) {
            std::string content = routes[path](body);
            response = createResponse(200, content);
        } else {
            response = createResponse(404, "Not Found");
        }
        
        send(client_socket, response.c_str(), response.length(), 0);
        close(client_socket);
    }
    
    std::tuple<std::string, std::string, std::string> parseRequest(const std::string& request) {
        std::istringstream iss(request);
        std::string method, path, version;
        iss >> method >> path >> version;
        
        // Extract body (simplified)
        size_t body_pos = request.find("\r\n\r\n");
        std::string body = (body_pos != std::string::npos) ? 
                          request.substr(body_pos + 4) : "";
        
        return {method, path, body};
    }
    
    std::string createResponse(int status_code, const std::string& content) {
        std::ostringstream response;
        response << "HTTP/1.1 " << status_code << " OK\r\n";
        response << "Content-Type: text/html\r\n";
        response << "Content-Length: " << content.length() << "\r\n";
        response << "Connection: close\r\n\r\n";
        response << content;
        return response.str();
    }
};
```

## Asynchronous I/O with epoll
```cpp
#include <sys/epoll.h>

class AsyncServer {
private:
    int server_fd, epoll_fd;
    static const int MAX_EVENTS = 64;
    
public:
    AsyncServer(int port) {
        // Create server socket (similar to TCPServer)
        server_fd = createServerSocket(port);
        
        // Create epoll instance
        epoll_fd = epoll_create1(0);
        if (epoll_fd == -1) {
            throw std::runtime_error("epoll_create1 failed");
        }
        
        // Add server socket to epoll
        struct epoll_event event;
        event.events = EPOLLIN;
        event.data.fd = server_fd;
        epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &event);
    }
    
    void run() {
        struct epoll_event events[MAX_EVENTS];
        
        while (true) {
            int nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
            
            for (int i = 0; i < nfds; ++i) {
                if (events[i].data.fd == server_fd) {
                    // New connection
                    int client_fd = accept(server_fd, nullptr, nullptr);
                    setNonBlocking(client_fd);
                    
                    struct epoll_event event;
                    event.events = EPOLLIN | EPOLLET;  // Edge-triggered
                    event.data.fd = client_fd;
                    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &event);
                } else {
                    // Data available on client socket
                    handleClientData(events[i].data.fd);
                }
            }
        }
    }
    
private:
    void handleClientData(int client_fd) {
        char buffer[1024];
        ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer));
        
        if (bytes_read <= 0) {
            // Connection closed or error
            epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client_fd, nullptr);
            close(client_fd);
        } else {
            // Process data and send response
            std::string response = processRequest(std::string(buffer, bytes_read));
            send(client_fd, response.c_str(), response.length(), 0);
        }
    }
};
```

## WebSocket Implementation
```cpp
#include <openssl/sha.h>
#include <openssl/evp.h>

class WebSocketServer {
private:
    static const std::string WEBSOCKET_MAGIC = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
    
public:
    std::string generateAcceptKey(const std::string& client_key) {
        std::string combined = client_key + WEBSOCKET_MAGIC;
        
        unsigned char hash[SHA_DIGEST_LENGTH];
        SHA1(reinterpret_cast<const unsigned char*>(combined.c_str()), 
             combined.length(), hash);
        
        // Base64 encode
        return base64Encode(hash, SHA_DIGEST_LENGTH);
    }
    
    std::string createHandshakeResponse(const std::string& accept_key) {
        std::ostringstream response;
        response << "HTTP/1.1 101 Switching Protocols\r\n";
        response << "Upgrade: websocket\r\n";
        response << "Connection: Upgrade\r\n";
        response << "Sec-WebSocket-Accept: " << accept_key << "\r\n\r\n";
        return response.str();
    }
    
    struct WebSocketFrame {
        bool fin;
        uint8_t opcode;
        bool masked;
        uint64_t payload_length;
        uint32_t masking_key;
        std::vector<uint8_t> payload;
    };
    
    WebSocketFrame parseFrame(const std::vector<uint8_t>& data) {
        WebSocketFrame frame;
        size_t offset = 0;
        
        // First byte: FIN + opcode
        frame.fin = (data[offset] & 0x80) != 0;
        frame.opcode = data[offset] & 0x0F;
        offset++;
        
        // Second byte: MASK + payload length
        frame.masked = (data[offset] & 0x80) != 0;
        uint8_t len = data[offset] & 0x7F;
        offset++;
        
        // Extended payload length
        if (len == 126) {
            frame.payload_length = (data[offset] << 8) | data[offset + 1];
            offset += 2;
        } else if (len == 127) {
            frame.payload_length = 0;
            for (int i = 0; i < 8; ++i) {
                frame.payload_length = (frame.payload_length << 8) | data[offset + i];
            }
            offset += 8;
        } else {
            frame.payload_length = len;
        }
        
        // Masking key
        if (frame.masked) {
            frame.masking_key = (data[offset] << 24) | (data[offset + 1] << 16) |
                               (data[offset + 2] << 8) | data[offset + 3];
            offset += 4;
        }
        
        // Payload
        frame.payload.resize(frame.payload_length);
        for (uint64_t i = 0; i < frame.payload_length; ++i) {
            frame.payload[i] = data[offset + i];
            if (frame.masked) {
                frame.payload[i] ^= ((uint8_t*)&frame.masking_key)[i % 4];
            }
        }
        
        return frame;
    }
};
```
