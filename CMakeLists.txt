cmake_minimum_required(VERSION 3.1)

set (PROJECT_NAME "date")

project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)


set(CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic -Wshadow -Wundef -Wno-missing-field-initializers -std=c++11")

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp  ${CMAKE_CURRENT_SOURCE_DIR}/Date.class.cpp)
