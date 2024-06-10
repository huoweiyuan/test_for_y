cmake_minimum_required(VERSION 3.22)
project(test_for_y)

set(CMAKE_CXX_STANDARD 17)

enable_testing()
find_package(GTest REQUIRED)
add_subdirectory(y)

SET(TESTING_SRC )
add_executable(test_for_y main.cc ${TESTING_SRC})
target_link_libraries(test_for_y PRIVATE ${GTEST_LIBRARIES} pthread y)
add_test(test_for_y ${CMAKE_BINARY_DIR}/test_for_y)

include_directories(
.
test
/usr/local/Cellar/googletest/1.14.0/include
y/includes)