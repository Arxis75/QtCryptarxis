cmake_minimum_required(VERSION 3.0)

project(hello_tests NONE)

add_executable(QtCryptarxis_test main.cpp)

target_link_libraries(QtCryptarxis_test PRIVATE GTest::gtest)

add_subdirectory(unit_tests)

include(GoogleTest)
gtest_discover_tests(QtCryptarxis_test)