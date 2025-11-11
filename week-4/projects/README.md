# Week 4 Projects

## Project 1: HTTP Server with REST API
**Duration**: Day 1-2
**Skills**: Network programming, HTTP protocol, REST API design

### Requirements
- Multi-threaded HTTP server
- REST API endpoints (GET, POST, PUT, DELETE)
- JSON request/response handling
- Static file serving
- Middleware support (logging, authentication)

### Files
- `http_server.h/cpp` - Core HTTP server
- `request_parser.h/cpp` - HTTP request parsing
- `response_builder.h/cpp` - HTTP response building
- `router.h/cpp` - URL routing system
- `middleware.h/cpp` - Middleware framework
- `json_handler.h/cpp` - JSON processing

### Starter Code
```cpp
class HTTPServer {
    int port;
    std::unique_ptr<ThreadPool> thread_pool;
    Router router;
    std::vector<Middleware> middlewares;
    
public:
    HTTPServer(int port);
    void add_route(const std::string& method, const std::string& path, 
                  std::function<Response(const Request&)> handler);
    void add_middleware(Middleware middleware);
    void start();
    void stop();
};

struct Request {
    std::string method;
    std::string path;
    std::unordered_map<std::string, std::string> headers;
    std::unordered_map<std::string, std::string> params;
    std::string body;
};

struct Response {
    int status_code = 200;
    std::unordered_map<std::string, std::string> headers;
    std::string body;
};

class Router {
    struct Route {
        std::string method;
        std::regex path_regex;
        std::function<Response(const Request&)> handler;
    };
    std::vector<Route> routes;
    
public:
    void add_route(const std::string& method, const std::string& path, 
                  std::function<Response(const Request&)> handler);
    std::optional<Response> handle_request(const Request& request);
};
```

## Project 2: Database ORM Framework
**Duration**: Day 3
**Skills**: Database integration, ORM design, SQL generation

### Requirements
- SQLite/PostgreSQL connection management
- Object-relational mapping
- Query builder with fluent interface
- Migration system
- Connection pooling

### Files
- `database.h/cpp` - Database connection management
- `orm.h/cpp` - Object-relational mapping
- `query_builder.h/cpp` - SQL query builder
- `migration.h/cpp` - Database migration system
- `connection_pool.h/cpp` - Connection pooling

### Starter Code
```cpp
class Database {
    std::string connection_string;
    std::unique_ptr<ConnectionPool> pool;
    
public:
    Database(const std::string& conn_str);
    std::unique_ptr<Connection> get_connection();
    void execute(const std::string& sql);
    ResultSet query(const std::string& sql);
};

template<typename T>
class ORM {
    Database& db;
    std::string table_name;
    
public:
    ORM(Database& database, const std::string& table);
    
    void create_table();
    void save(const T& object);
    std::optional<T> find(int id);
    std::vector<T> find_all();
    void update(const T& object);
    void remove(int id);
    
    QueryBuilder<T> where(const std::string& condition);
};

template<typename T>
class QueryBuilder {
    Database& db;
    std::string table_name;
    std::string where_clause;
    std::string order_clause;
    int limit_value = -1;
    
public:
    QueryBuilder<T>& where(const std::string& condition);
    QueryBuilder<T>& order_by(const std::string& column);
    QueryBuilder<T>& limit(int count);
    std::vector<T> get();
    std::optional<T> first();
};

// Usage example:
struct User {
    int id;
    std::string name;
    std::string email;
    
    // Reflection/serialization methods
    static std::string table_name() { return "users"; }
    std::unordered_map<std::string, std::string> to_map() const;
    static User from_map(const std::unordered_map<std::string, std::string>& data);
};
```

## Project 3: Distributed Cache System
**Duration**: Day 4
**Skills**: Distributed systems, caching, network protocols

### Requirements
- Distributed hash table implementation
- Consistent hashing for node distribution
- Replication and fault tolerance
- Cache eviction policies (LRU, LFU)
- Network protocol for cache operations

### Files
- `cache_node.h/cpp` - Individual cache node
- `consistent_hash.h/cpp` - Consistent hashing
- `replication.h/cpp` - Data replication
- `eviction_policy.h/cpp` - Cache eviction strategies
- `cache_client.h/cpp` - Client library

### Starter Code
```cpp
class CacheNode {
    std::unordered_map<std::string, std::string> cache;
    std::unique_ptr<EvictionPolicy> eviction_policy;
    std::vector<std::string> replica_nodes;
    
public:
    void set(const std::string& key, const std::string& value);
    std::optional<std::string> get(const std::string& key);
    void remove(const std::string& key);
    void replicate_to_nodes(const std::string& key, const std::string& value);
};

class ConsistentHash {
    std::map<uint64_t, std::string> ring;
    std::hash<std::string> hasher;
    int virtual_nodes;
    
public:
    ConsistentHash(int virtual_nodes = 150);
    void add_node(const std::string& node);
    void remove_node(const std::string& node);
    std::string get_node(const std::string& key);
    std::vector<std::string> get_nodes(const std::string& key, int count);
};

class DistributedCache {
    std::vector<std::unique_ptr<CacheNode>> nodes;
    ConsistentHash hash_ring;
    int replication_factor;
    
public:
    DistributedCache(int replication_factor = 3);
    void add_node(const std::string& address);
    void set(const std::string& key, const std::string& value);
    std::optional<std::string> get(const std::string& key);
    void remove(const std::string& key);
};
```

## Project 4: Microservices Platform
**Duration**: Day 5
**Skills**: Microservices architecture, service discovery, load balancing

### Requirements
- Service registry and discovery
- Load balancer with multiple strategies
- API gateway with routing
- Health checking and monitoring
- Configuration management

### Files
- `service_registry.h/cpp` - Service discovery
- `load_balancer.h/cpp` - Load balancing strategies
- `api_gateway.h/cpp` - API gateway implementation
- `health_checker.h/cpp` - Health monitoring
- `config_manager.h/cpp` - Configuration management

### Starter Code
```cpp
struct ServiceInfo {
    std::string name;
    std::string address;
    int port;
    std::unordered_map<std::string, std::string> metadata;
    std::chrono::steady_clock::time_point last_heartbeat;
};

class ServiceRegistry {
    std::unordered_map<std::string, std::vector<ServiceInfo>> services;
    std::mutex registry_mutex;
    
public:
    void register_service(const ServiceInfo& service);
    void deregister_service(const std::string& name, const std::string& address);
    std::vector<ServiceInfo> discover_services(const std::string& name);
    void heartbeat(const std::string& name, const std::string& address);
    void cleanup_stale_services();
};

class LoadBalancer {
public:
    enum class Strategy { RoundRobin, LeastConnections, Random, WeightedRandom };
    
private:
    Strategy strategy;
    std::atomic<size_t> round_robin_counter{0};
    std::unordered_map<std::string, int> connection_counts;
    
public:
    LoadBalancer(Strategy s) : strategy(s) {}
    ServiceInfo select_service(const std::vector<ServiceInfo>& services);
    void update_connection_count(const std::string& address, int delta);
};

class APIGateway {
    ServiceRegistry& registry;
    LoadBalancer load_balancer;
    std::unordered_map<std::string, std::string> route_mappings;
    
public:
    APIGateway(ServiceRegistry& reg);
    void add_route(const std::string& path, const std::string& service_name);
    Response handle_request(const Request& request);
    void proxy_request(const Request& request, const ServiceInfo& target);
};
```

## Project 5: Real-Time Communication System
**Duration**: Day 6
**Skills**: WebSocket, real-time messaging, pub-sub patterns

### Requirements
- WebSocket server implementation
- Publish-subscribe messaging
- Room-based communication
- Message persistence
- Scalable architecture

### Files
- `websocket_server.h/cpp` - WebSocket server
- `message_broker.h/cpp` - Pub-sub message broker
- `room_manager.h/cpp` - Room-based messaging
- `message_store.h/cpp` - Message persistence
- `client_manager.h/cpp` - Client connection management

### Starter Code
```cpp
class WebSocketServer {
    HTTPServer http_server;
    std::unordered_map<int, std::unique_ptr<WebSocketConnection>> connections;
    MessageBroker& message_broker;
    
public:
    WebSocketServer(int port, MessageBroker& broker);
    void handle_websocket_upgrade(const Request& request, int client_fd);
    void handle_websocket_message(int client_fd, const std::string& message);
    void broadcast_message(const std::string& message);
    void send_to_client(int client_fd, const std::string& message);
};

class MessageBroker {
    std::unordered_map<std::string, std::vector<std::function<void(const Message&)>>> subscribers;
    std::queue<Message> message_queue;
    std::mutex broker_mutex;
    
public:
    void subscribe(const std::string& topic, std::function<void(const Message&)> handler);
    void unsubscribe(const std::string& topic, int subscriber_id);
    void publish(const std::string& topic, const Message& message);
    void process_messages();
};

struct Message {
    std::string id;
    std::string topic;
    std::string sender;
    std::string content;
    std::chrono::system_clock::time_point timestamp;
    std::unordered_map<std::string, std::string> metadata;
};

class RoomManager {
    std::unordered_map<std::string, std::set<int>> rooms; // room_id -> client_fds
    std::unordered_map<int, std::set<std::string>> client_rooms; // client_fd -> room_ids
    
public:
    void join_room(int client_fd, const std::string& room_id);
    void leave_room(int client_fd, const std::string& room_id);
    void broadcast_to_room(const std::string& room_id, const Message& message);
    std::set<int> get_room_clients(const std::string& room_id);
};
```

## Project 6: System Monitoring Dashboard
**Duration**: Day 7
**Skills**: System monitoring, metrics collection, web dashboard

### Requirements
- System metrics collection (CPU, memory, network)
- Time-series data storage
- Real-time dashboard with WebSocket updates
- Alerting system
- Historical data analysis

### Files
- `metrics_collector.h/cpp` - System metrics collection
- `time_series_db.h/cpp` - Time-series database
- `dashboard_server.h/cpp` - Web dashboard server
- `alert_manager.h/cpp` - Alerting system
- `data_analyzer.h/cpp` - Historical data analysis

### Starter Code
```cpp
struct SystemMetrics {
    double cpu_usage;
    double memory_usage;
    double disk_usage;
    double network_in;
    double network_out;
    std::chrono::system_clock::time_point timestamp;
};

class MetricsCollector {
    std::thread collector_thread;
    std::atomic<bool> running{false};
    std::function<void(const SystemMetrics&)> callback;
    
public:
    MetricsCollector(std::function<void(const SystemMetrics&)> cb);
    void start();
    void stop();
    
private:
    SystemMetrics collect_metrics();
    double get_cpu_usage();
    double get_memory_usage();
    double get_disk_usage();
};

class TimeSeriesDB {
    struct DataPoint {
        std::chrono::system_clock::time_point timestamp;
        double value;
    };
    
    std::unordered_map<std::string, std::vector<DataPoint>> series;
    std::mutex db_mutex;
    
public:
    void insert(const std::string& metric, double value, 
               std::chrono::system_clock::time_point timestamp);
    std::vector<DataPoint> query(const std::string& metric, 
                                std::chrono::system_clock::time_point start,
                                std::chrono::system_clock::time_point end);
    void cleanup_old_data(std::chrono::hours retention_period);
};
```

## Portfolio Project Options
Choose one major integration project:

### Option A: Quantitative Trading Platform
- Real-time market data processing
- Order management system
- Risk management and portfolio optimization
- Backtesting framework
- Performance analytics dashboard

### Option B: Distributed Database System
- Distributed storage with sharding
- ACID transaction support
- Query optimization engine
- Replication and fault tolerance
- Management console

### Option C: Real-Time Game Engine
- Entity-component system
- Physics simulation
- Network synchronization
- Asset management
- Scripting integration

### Option D: High-Frequency Data Processor
- Low-latency data ingestion
- Stream processing pipeline
- Complex event processing
- Real-time analytics
- Monitoring and alerting

## Assessment Criteria
- System architecture and design
- Network programming proficiency
- Database integration skills
- Performance and scalability
- Code quality and documentation
- Real-world applicability
