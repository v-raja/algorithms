cmake_minimum_required(VERSION 3.10)

# CXX required for googletest
project(qsort)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(Sodium REQUIRED)
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${sodium_INCLUDE_DIR}")

add_executable(qsort src/quick_sort.c src/main.c)
target_link_libraries(qsort ${sodium_LIBRARY_RELEASE})

### For testing
include(CTest) # Comment this line to disable building tests
if(BUILD_TESTING)
  find_package(GTest REQUIRED)
  include_directories("${PROJECT_SOURCE_DIR}/src")
  add_executable(qsort_tests test/quick_sort.cpp)
  target_compile_features(qsort_tests PRIVATE cxx_std_17)
  target_link_libraries(qsort_tests ${GTEST_LIBRARY} ${sodium_LIBRARY_RELEASE})
  gtest_discover_tests(qsort_tests)
endif()

