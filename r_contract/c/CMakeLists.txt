cmake_minimum_required(VERSION 3.10)

project(r_contract)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(Sodium REQUIRED)
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${sodium_INCLUDE_DIR}")

add_executable(r_contract src/main.c src/graph.c src/r_contract.c)
target_link_libraries(r_contract ${sodium_LIBRARY_RELEASE})
