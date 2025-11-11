cmake_minimum_required(VERSION 3.20)
project(week3_projects)

# Thread Pool
add_subdirectory(thread_pool)

# Lock-Free Structures
add_subdirectory(lockfree_structures)

# Modern C++ Features
add_subdirectory(modern_cpp)

# Design Patterns
add_subdirectory(design_patterns)

# HPC Library
add_subdirectory(hpc_library)

# Trading Engine
add_subdirectory(trading_engine)

# Collect all test targets
if(ENABLE_TESTING)
    add_custom_target(week3-tests
        DEPENDS 
            thread-pool-tests
            lockfree-tests
            modern-cpp-tests
            design-patterns-tests
            hpc-library-tests
            trading-engine-tests
        COMMENT "Running Week 3 tests"
    )
endif()
