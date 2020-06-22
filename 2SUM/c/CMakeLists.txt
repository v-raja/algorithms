cmake_minimum_required(VERSION 3.10)

project(2sum)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(Sodium REQUIRED)
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${sodium_INCLUDE_DIR}")

add_executable(2sum src/main.c src/hash_table.c)
target_link_libraries(2sum ${sodium_LIBRARY_RELEASE})
