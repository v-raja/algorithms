cmake_minimum_required(VERSION 3.10)

project(scc)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(scc src/main.c src/graph.c src/scc.c)

