cmake_minimum_required(VERSION 3.11)

project(BVHParser)

add_executable(BVHParser main.cpp bvhparser.cpp skeleton.cpp)

target_include_directories(BVHParser PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Boost REQUIRED COMPONENTS program_options)
target_link_libraries(BVHParser PRIVATE Boost::program_options)