cmake_minimum_required(VERSION 3.10)

project(Mythical-Creature-Catalouge)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

file(GLOB SOURCE_FILES "src/*.cpp")

add_executable(out ${SOURCE_FILES})

target_include_directories(out PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/creatures.txt
               ${CMAKE_CURRENT_BINARY_DIR}/creatures.txt COPYONLY)
