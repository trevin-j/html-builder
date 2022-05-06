cmake_minimum_required(VERSION 3.10)

# set project name
project(HTMLBuilderExample)

# all source files
file(GLOB SOURCES src/*.cpp)

# add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# add include directory
target_include_directories(${PROJECT_NAME} PRIVATE "include")