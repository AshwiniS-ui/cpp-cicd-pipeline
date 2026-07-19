cmake_minimum_required(VERSION 3.15)

project(CPPCICDPipeline VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

# Calculator library
add_library(calculator
    src/calculator.cpp
)

target_include_directories(calculator PUBLIC include)

# Main application
add_executable(calculator_app
    src/main.cpp
)

target_link_libraries(calculator_app PRIVATE calculator)

# Enable testing
enable_testing()

# Future Google Test
# add_subdirectory(tests)