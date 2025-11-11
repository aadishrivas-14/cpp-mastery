cmake_minimum_required(VERSION 3.20)
project(week1_projects)

# Calculator Project
add_subdirectory(calculator)

# Banking System Project  
add_subdirectory(banking)

# Smart Pointers Project
add_subdirectory(smart_pointers)

# Memory Pool Project
add_subdirectory(memory_pool)

# Collect all test targets
if(ENABLE_TESTING)
    add_custom_target(week1-tests
        DEPENDS 
            calculator-tests
            banking-tests
            smart-pointers-tests
            memory-pool-tests
        COMMENT "Running Week 1 tests"
    )
endif()
