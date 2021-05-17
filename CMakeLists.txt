cmake_minimum_required(VERSION 3.20.2)
project(compiler VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(compiler main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_compile_features(compiler PUBLIC cxx_std_20)
