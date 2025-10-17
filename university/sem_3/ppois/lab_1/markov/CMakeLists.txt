cmake_minimum_required(VERSION 3.10)
project(Markov LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(--coverage -O0 -g)
add_link_options(--coverage)

add_executable(markov_app
    Markov.cpp
    lab1_markov.cpp
)

add_executable(markov_tests
    Markov.cpp
    markov_test.cpp
)

find_library(UNITTESTPP_LIB UnitTest++)
if (NOT UNITTESTPP_LIB)
    message(FATAL_ERROR "UnitTest++ library not found")
endif()

target_link_libraries(markov_tests ${UNITTESTPP_LIB})