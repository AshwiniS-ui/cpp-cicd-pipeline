cmake_minimum_required(VERSION 3.15)

project(CPPCICDPipeline VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_library(calculator
    src/calculator.cpp
)

add_executable(calculator_app
    src/main.cpp
)

target_link_libraries(calculator_app calculator)

enable_testing()