cmake_minimum_required(VERSION 3.10)
project(vectors)

# Define the header-only library
add_library(vectors INTERFACE)
target_include_directories(vectors INTERFACE src)

# Enable C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executables for each example
file(GLOB EXAMPLE_SOURCES "examples/*.cpp")

foreach(SOURCE_FILE ${EXAMPLE_SOURCES})
    get_filename_component(EXE_NAME ${SOURCE_FILE} NAME_WE)
    add_executable(${EXE_NAME} ${SOURCE_FILE})
    target_link_libraries(${EXE_NAME} vectors)
endforeach()
