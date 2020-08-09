cmake_minimum_required(VERSION 3.10)

project(dsp)
include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(dsp src/main.c src/graph.c src/heap.c src/mst.c)
