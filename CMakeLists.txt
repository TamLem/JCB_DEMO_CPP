cmake_minimum_required(VERSION "3.0")

project("JCMDemo")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

set(BOOST_PATH "/Users/tlemma/goinfre/boost_1_80_0/")

include_directories(${BOOST_PATH})
include_directories("include")

add_executable("JCMDemo" "src/main.cpp" "src/Game.cpp" "src/Player.cpp" "src/Game_utils.cpp")

install(TARGETS JCMDemo DESTINATION bin)