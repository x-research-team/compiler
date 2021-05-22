cmake_minimum_required(VERSION 3.20.2)
project(compiler VERSION 0.1.0)

include(CTest)
enable_testing()

set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS        OFF)  # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.75 COMPONENTS date_time filesystem system)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  add_executable(compiler main.cpp token/Token.hpp token/Blocks.hpp token/FlipMap.hpp token/Keyword.hpp token/Operators.hpp lexer/Lexer.hpp)
  target_link_libraries(compiler ${Boost_LIBRARIES})
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_compile_features(compiler PUBLIC cxx_std_20)
