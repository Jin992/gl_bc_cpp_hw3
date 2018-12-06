cmake_minimum_required(VERSION 3.0)

set (PROJECT_NAME "date")

project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDART 11)
set(CMAKE_CXX_STANDART REQUIRED TRUE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic -Wshadow -Wundef -Wno-missing-field-initializers")

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp  ${CMAKE_CURRENT_SOURCE_DIR}/Date.class.cpp)
