cmake_minimum_required(VERSION 3.20)
project(week2_projects)

# STL Benchmark Suite
add_subdirectory(stl_benchmark)

# Generic Container Library
add_subdirectory(generic_container)

# Expression Template System
add_subdirectory(expression_template)

# BST with Iterators
add_subdirectory(bst_iterator)

# Graph Visualizer
add_subdirectory(graph_visualizer)

# Collect all test targets
if(ENABLE_TESTING)
    add_custom_target(week2-tests
        DEPENDS 
            stl-benchmark-tests
            generic-container-tests
            expression-template-tests
            bst-iterator-tests
            graph-visualizer-tests
        COMMENT "Running Week 2 tests"
    )
endif()
