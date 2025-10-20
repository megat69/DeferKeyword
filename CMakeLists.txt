cmake_minimum_required(VERSION 3.14)
project("Deferlib")

add_executable(test_deferlib "test/main.cpp")

target_include_directories(test_deferlib PUBLIC "src/")
