#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include "http_server.h"
#include "request_parser.h"
#include "response_builder.h"
#include "router.h"
#include "middleware.h"

// Request parser tests
class RequestParserTest : public ::testing::Test {
protected:
    RequestParser parser;
};

TEST_F(RequestParserTest, ParsesSimpleGETRequest) {
    std::string raw_request = 
        "GET /hello HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "User-Agent: TestClient/1.0\r\n"
        "\r\n";
    
    auto request = parser.parse(raw_request);
    
    EXPECT_EQ(request.method, "GET");
    EXPECT_EQ(request.path, "/hello");
    EXPECT_EQ(request.version, "HTTP/1.1");
    EXPECT_EQ(request.headers["Host"], "localhost:8080");
    EXPECT_EQ(request.headers["User-Agent"], "TestClient/1.0");
    EXPECT_TRUE(request.body.empty());
}

TEST_F(RequestParserTest, ParsesPOSTRequestWithBody) {
    std::string raw_request = 
        "POST /api/users HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 25\r\n"
        "\r\n"
        "{\"name\":\"John\",\"age\":30}";
    
    auto request = parser.parse(raw_request);
    
    EXPECT_EQ(request.method, "POST");
    EXPECT_EQ(request.path, "/api/users");
    EXPECT_EQ(request.headers["Content-Type"], "application/json");
    EXPECT_EQ(request.headers["Content-Length"], "25");
    EXPECT_EQ(request.body, "{\"name\":\"John\",\"age\":30}");
}

TEST_F(RequestParserTest, ParsesQueryParameters) {
    std::string raw_request = 
        "GET /search?q=test&limit=10&offset=20 HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "\r\n";
    
    auto request = parser.parse(raw_request);
    
    EXPECT_EQ(request.path, "/search");
    EXPECT_EQ(request.query_params["q"], "test");
    EXPECT_EQ(request.query_params["limit"], "10");
    EXPECT_EQ(request.query_params["offset"], "20");
}

TEST_F(RequestParserTest, HandlesURLEncoding) {
    std::string raw_request = 
        "GET /search?q=hello%20world&name=John%20Doe HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "\r\n";
    
    auto request = parser.parse(raw_request);
    
    EXPECT_EQ(request.query_params["q"], "hello world");
    EXPECT_EQ(request.query_params["name"], "John Doe");
}

TEST_F(RequestParserTest, ThrowsOnMalformedRequest) {
    std::string malformed_request = "INVALID REQUEST";
    
    EXPECT_THROW(parser.parse(malformed_request), std::invalid_argument);
}

// Response builder tests
class ResponseBuilderTest : public ::testing::Test {
protected:
    ResponseBuilder builder;
};

TEST_F(ResponseBuilderTest, BuildsSimpleResponse) {
    Response response;
    response.status_code = 200;
    response.headers["Content-Type"] = "text/plain";
    response.body = "Hello, World!";
    
    std::string raw_response = builder.build(response);
    
    EXPECT_TRUE(raw_response.find("HTTP/1.1 200 OK") != std::string::npos);
    EXPECT_TRUE(raw_response.find("Content-Type: text/plain") != std::string::npos);
    EXPECT_TRUE(raw_response.find("Content-Length: 13") != std::string::npos);
    EXPECT_TRUE(raw_response.find("Hello, World!") != std::string::npos);
}

TEST_F(ResponseBuilderTest, BuildsJSONResponse) {
    Response response;
    response.status_code = 201;
    response.headers["Content-Type"] = "application/json";
    response.body = "{\"id\":1,\"name\":\"John\"}";
    
    std::string raw_response = builder.build(response);
    
    EXPECT_TRUE(raw_response.find("HTTP/1.1 201 Created") != std::string::npos);
    EXPECT_TRUE(raw_response.find("Content-Type: application/json") != std::string::npos);
    EXPECT_TRUE(raw_response.find("{\"id\":1,\"name\":\"John\"}") != std::string::npos);
}

TEST_F(ResponseBuilderTest, BuildsErrorResponse) {
    Response response;
    response.status_code = 404;
    response.body = "Not Found";
    
    std::string raw_response = builder.build(response);
    
    EXPECT_TRUE(raw_response.find("HTTP/1.1 404 Not Found") != std::string::npos);
    EXPECT_TRUE(raw_response.find("Not Found") != std::string::npos);
}

TEST_F(ResponseBuilderTest, AddsDefaultHeaders) {
    Response response;
    response.status_code = 200;
    response.body = "Test";
    
    std::string raw_response = builder.build(response);
    
    EXPECT_TRUE(raw_response.find("Server: HTTPServer/1.0") != std::string::npos);
    EXPECT_TRUE(raw_response.find("Connection: close") != std::string::npos);
}

// Router tests
class RouterTest : public ::testing::Test {
protected:
    Router router;
};

TEST_F(RouterTest, RoutesSimplePath) {
    bool handler_called = false;
    
    router.addRoute("GET", "/hello", [&](const Request& req) {
        handler_called = true;
        Response resp;
        resp.status_code = 200;
        resp.body = "Hello!";
        return resp;
    });
    
    Request request;
    request.method = "GET";
    request.path = "/hello";
    
    auto response = router.handleRequest(request);
    
    EXPECT_TRUE(handler_called);
    EXPECT_TRUE(response.has_value());
    EXPECT_EQ(response->status_code, 200);
    EXPECT_EQ(response->body, "Hello!");
}

TEST_F(RouterTest, RoutesWithPathParameters) {
    router.addRoute("GET", "/users/{id}", [](const Request& req) {
        Response resp;
        resp.status_code = 200;
        resp.body = "User ID: " + req.path_params.at("id");
        return resp;
    });
    
    Request request;
    request.method = "GET";
    request.path = "/users/123";
    
    auto response = router.handleRequest(request);
    
    EXPECT_TRUE(response.has_value());
    EXPECT_EQ(response->body, "User ID: 123");
}

TEST_F(RouterTest, RoutesWithMultipleParameters) {
    router.addRoute("GET", "/users/{user_id}/posts/{post_id}", [](const Request& req) {
        Response resp;
        resp.status_code = 200;
        resp.body = "User: " + req.path_params.at("user_id") + 
                   ", Post: " + req.path_params.at("post_id");
        return resp;
    });
    
    Request request;
    request.method = "GET";
    request.path = "/users/456/posts/789";
    
    auto response = router.handleRequest(request);
    
    EXPECT_TRUE(response.has_value());
    EXPECT_EQ(response->body, "User: 456, Post: 789");
}

TEST_F(RouterTest, ReturnsNulloptForUnmatchedRoute) {
    Request request;
    request.method = "GET";
    request.path = "/nonexistent";
    
    auto response = router.handleRequest(request);
    
    EXPECT_FALSE(response.has_value());
}

TEST_F(RouterTest, MatchesMethodSpecifically) {
    router.addRoute("GET", "/test", [](const Request& req) {
        Response resp;
        resp.status_code = 200;
        resp.body = "GET response";
        return resp;
    });
    
    router.addRoute("POST", "/test", [](const Request& req) {
        Response resp;
        resp.status_code = 201;
        resp.body = "POST response";
        return resp;
    });
    
    Request get_request;
    get_request.method = "GET";
    get_request.path = "/test";
    
    Request post_request;
    post_request.method = "POST";
    post_request.path = "/test";
    
    auto get_response = router.handleRequest(get_request);
    auto post_response = router.handleRequest(post_request);
    
    EXPECT_EQ(get_response->body, "GET response");
    EXPECT_EQ(post_response->body, "POST response");
}

// Middleware tests
class MiddlewareTest : public ::testing::Test {
protected:
    Router router;
    std::vector<std::string> execution_order;
};

TEST_F(MiddlewareTest, ExecutesMiddlewareInOrder) {
    auto middleware1 = [&](const Request& req, std::function<Response()> next) {
        execution_order.push_back("middleware1_before");
        auto response = next();
        execution_order.push_back("middleware1_after");
        return response;
    };
    
    auto middleware2 = [&](const Request& req, std::function<Response()> next) {
        execution_order.push_back("middleware2_before");
        auto response = next();
        execution_order.push_back("middleware2_after");
        return response;
    };
    
    router.addMiddleware(middleware1);
    router.addMiddleware(middleware2);
    
    router.addRoute("GET", "/test", [&](const Request& req) {
        execution_order.push_back("handler");
        Response resp;
        resp.status_code = 200;
        return resp;
    });
    
    Request request;
    request.method = "GET";
    request.path = "/test";
    
    router.handleRequest(request);
    
    std::vector<std::string> expected = {
        "middleware1_before",
        "middleware2_before", 
        "handler",
        "middleware2_after",
        "middleware1_after"
    };
    
    EXPECT_EQ(execution_order, expected);
}

TEST_F(MiddlewareTest, LoggingMiddleware) {
    std::vector<std::string> logs;
    
    auto logging_middleware = [&](const Request& req, std::function<Response()> next) {
        logs.push_back("Request: " + req.method + " " + req.path);
        auto response = next();
        logs.push_back("Response: " + std::to_string(response.status_code));
        return response;
    };
    
    router.addMiddleware(logging_middleware);
    router.addRoute("GET", "/api/test", [](const Request& req) {
        Response resp;
        resp.status_code = 200;
        return resp;
    });
    
    Request request;
    request.method = "GET";
    request.path = "/api/test";
    
    router.handleRequest(request);
    
    EXPECT_EQ(logs.size(), 2);
    EXPECT_EQ(logs[0], "Request: GET /api/test");
    EXPECT_EQ(logs[1], "Response: 200");
}

TEST_F(MiddlewareTest, AuthenticationMiddleware) {
    auto auth_middleware = [](const Request& req, std::function<Response()> next) {
        if (req.headers.find("Authorization") == req.headers.end()) {
            Response resp;
            resp.status_code = 401;
            resp.body = "Unauthorized";
            return resp;
        }
        return next();
    };
    
    router.addMiddleware(auth_middleware);
    router.addRoute("GET", "/protected", [](const Request& req) {
        Response resp;
        resp.status_code = 200;
        resp.body = "Protected resource";
        return resp;
    });
    
    // Request without authorization
    Request unauthorized_request;
    unauthorized_request.method = "GET";
    unauthorized_request.path = "/protected";
    
    auto response1 = router.handleRequest(unauthorized_request);
    EXPECT_EQ(response1->status_code, 401);
    
    // Request with authorization
    Request authorized_request;
    authorized_request.method = "GET";
    authorized_request.path = "/protected";
    authorized_request.headers["Authorization"] = "Bearer token123";
    
    auto response2 = router.handleRequest(authorized_request);
    EXPECT_EQ(response2->status_code, 200);
    EXPECT_EQ(response2->body, "Protected resource");
}

// HTTP Server integration tests
class HTTPServerTest : public ::testing::Test {
protected:
    void SetUp() override {
        server = std::make_unique<HTTPServer>(8080);
    }
    
    void TearDown() override {
        if (server) {
            server->stop();
        }
    }
    
    std::unique_ptr<HTTPServer> server;
};

TEST_F(HTTPServerTest, StartsAndStops) {
    EXPECT_NO_THROW(server->start());
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    EXPECT_NO_THROW(server->stop());
}

TEST_F(HTTPServerTest, HandlesMultipleRoutes) {
    server->addRoute("GET", "/", [](const Request& req) {
        Response resp;
        resp.status_code = 200;
        resp.body = "Home page";
        return resp;
    });
    
    server->addRoute("GET", "/about", [](const Request& req) {
        Response resp;
        resp.status_code = 200;
        resp.body = "About page";
        return resp;
    });
    
    server->addRoute("POST", "/api/data", [](const Request& req) {
        Response resp;
        resp.status_code = 201;
        resp.headers["Content-Type"] = "application/json";
        resp.body = "{\"message\":\"Data created\"}";
        return resp;
    });
    
    // Start server in background
    std::thread server_thread([&]() {
        server->start();
    });
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // Test routes (would need actual HTTP client for full integration test)
    // For unit test, we verify routes are registered
    EXPECT_TRUE(server->hasRoute("GET", "/"));
    EXPECT_TRUE(server->hasRoute("GET", "/about"));
    EXPECT_TRUE(server->hasRoute("POST", "/api/data"));
    EXPECT_FALSE(server->hasRoute("GET", "/nonexistent"));
    
    server->stop();
    server_thread.join();
}

TEST_F(HTTPServerTest, ServesStaticFiles) {
    server->setStaticDirectory("./static");
    
    // Would test actual file serving in integration test
    EXPECT_TRUE(server->hasStaticDirectory());
}

// JSON handling tests
class JSONHandlerTest : public ::testing::Test {};

TEST_F(JSONHandlerTest, ParsesValidJSON) {
    std::string json_str = "{\"name\":\"John\",\"age\":30,\"active\":true}";
    
    auto json = JSONHandler::parse(json_str);
    
    EXPECT_EQ(json["name"].asString(), "John");
    EXPECT_EQ(json["age"].asInt(), 30);
    EXPECT_TRUE(json["active"].asBool());
}

TEST_F(JSONHandlerTest, SerializesToJSON) {
    JSONObject json;
    json["name"] = "Jane";
    json["age"] = 25;
    json["scores"] = JSONArray{95, 87, 92};
    
    std::string json_str = JSONHandler::stringify(json);
    
    EXPECT_TRUE(json_str.find("\"name\":\"Jane\"") != std::string::npos);
    EXPECT_TRUE(json_str.find("\"age\":25") != std::string::npos);
    EXPECT_TRUE(json_str.find("[95,87,92]") != std::string::npos);
}

TEST_F(JSONHandlerTest, ThrowsOnInvalidJSON) {
    std::string invalid_json = "{\"name\":\"John\",\"age\":}";
    
    EXPECT_THROW(JSONHandler::parse(invalid_json), std::invalid_argument);
}

// Performance tests
TEST_F(HTTPServerTest, HandlesMultipleConnections) {
    const int NUM_REQUESTS = 100;
    std::atomic<int> requests_handled{0};
    
    server->addRoute("GET", "/test", [&](const Request& req) {
        requests_handled++;
        Response resp;
        resp.status_code = 200;
        resp.body = "OK";
        return resp;
    });
    
    // Start server
    std::thread server_thread([&]() {
        server->start();
    });
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // Simulate multiple concurrent requests
    std::vector<std::thread> client_threads;
    for (int i = 0; i < NUM_REQUESTS; ++i) {
        client_threads.emplace_back([&]() {
            // In real test, would make actual HTTP request
            // For unit test, simulate request handling
            Request req;
            req.method = "GET";
            req.path = "/test";
            server->simulateRequest(req); // Hypothetical method
        });
    }
    
    for (auto& thread : client_threads) {
        thread.join();
    }
    
    server->stop();
    server_thread.join();
    
    // In actual implementation, would verify all requests were handled
    EXPECT_GT(requests_handled.load(), 0);
}
