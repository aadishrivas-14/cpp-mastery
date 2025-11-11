cmake_minimum_required(VERSION 3.20)
project(week4_projects)

# HTTP Server
add_subdirectory(http_server)

# Database ORM
add_subdirectory(database_orm)

# Distributed Cache
add_subdirectory(distributed_cache)

# Microservices Platform
add_subdirectory(microservices)

# Real-time Communication
add_subdirectory(realtime_comm)

# Monitoring System
add_subdirectory(monitoring)

# Collect all test targets
if(ENABLE_TESTING)
    add_custom_target(week4-tests
        DEPENDS 
            http-server-tests
            database-orm-tests
            distributed-cache-tests
            microservices-tests
            realtime-comm-tests
            monitoring-tests
        COMMENT "Running Week 4 tests"
    )
endif()
