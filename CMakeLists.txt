cmake_minimum_required(VERSION 3.22)
project(test_for_y)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(y)

add_executable(test_for_y main.cc )
target_link_libraries(test_for_y PRIVATE  pthread y)
add_test(test_for_y ${CMAKE_BINARY_DIR}/test_for_y)

add_executable(performance ${CMAKE_SOURCE_DIR}/test/performance.cc)
target_link_libraries(performance PRIVATE pthread y)
add_test(performance ${CMAKE_BINARY_DIR}/test_for_y)


include_directories(
.
test
/usr/local/Cellar/googletest/1.14.0/include
y/includes)