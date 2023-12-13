cmake_minimum_required(VERSION 3.13)

project(ImplementTree)

set(CMAKE_CXX_STANDARD 11)

find_package(GTest REQUIRED)
message("GTest_INCLUDE_DIRS = ${GTest_INCLUDE_DIRS}")

add_library(common_library AVLTree.cc)

add_executable(mainApp main.cc)
target_link_libraries(mainApp common_library)

add_executable(unitTestRunner test_runner.cc)
target_link_libraries(unitTestRunner common_library ${GTEST_LIBRARIES})

