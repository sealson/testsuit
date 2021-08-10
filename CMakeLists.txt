cmake_minimum_required(VERSION 3.16)

project(testsuit)

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD_REQUIRED 11)
set(CMAKE_CXX_STANDARD_REQUIRED 11)
set(CMAKE_BUILD_TYPE Debug)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME}
    main.cpp
    config.cpp
    balancer.cpp
    )

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    pthread
    )
