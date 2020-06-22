cmake_minimum_required(VERSION 3.10)

# CXX required for googletest
project(greedy)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(Sodium REQUIRED)
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${sodium_INCLUDE_DIR}")

add_executable(greedy src/qsort.c src/main.c src/job.c)
target_link_libraries(greedy ${sodium_LIBRARY_RELEASE})
