# CMake generated Testfile for 
# Source directory: /Users/huoweiyuan/projects/test_for_y
# Build directory: /Users/huoweiyuan/projects/test_for_y/build_vs
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[test_for_y]=] "/Users/huoweiyuan/projects/test_for_y/build_vs/test_for_y")
set_tests_properties([=[test_for_y]=] PROPERTIES  _BACKTRACE_TRIPLES "/Users/huoweiyuan/projects/test_for_y/CMakeLists.txt;13;add_test;/Users/huoweiyuan/projects/test_for_y/CMakeLists.txt;0;")
add_test([=[performance]=] "/Users/huoweiyuan/projects/test_for_y/build_vs/test_for_y")
set_tests_properties([=[performance]=] PROPERTIES  _BACKTRACE_TRIPLES "/Users/huoweiyuan/projects/test_for_y/CMakeLists.txt;17;add_test;/Users/huoweiyuan/projects/test_for_y/CMakeLists.txt;0;")
subdirs("y")
