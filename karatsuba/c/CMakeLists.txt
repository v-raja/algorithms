cmake_minimum_required(VERSION 3.10)

# CXX required for googletest
project(k_mult)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include_directories("${PROJECT_SOURCE_DIR}/include")
add_executable(k_mult src/karatsuba.c src/main.c)

### For testing
include(CTest) # Comment this line to disable building tests
if(BUILD_TESTING)
  find_package(GTest REQUIRED)
  find_package(Sodium REQUIRED)
  include_directories("${PROJECT_SOURCE_DIR}/src")
  add_executable(k_mult_tests test/karatsuba.cpp)
  target_compile_features(k_mult_tests PRIVATE cxx_std_17)
  target_link_libraries(k_mult_tests ${GTEST_LIBRARY} ${sodium_LIBRARY_RELEASE})
  gtest_discover_tests(k_mult_tests)
endif()

