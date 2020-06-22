cmake_minimum_required(VERSION 3.10)

project(heap_median)
include_directories("${PROJECT_SOURCE_DIR}/include")
add_executable(median src/heap.c src/main.c src/median_maintainance.c)
