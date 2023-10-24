cmake_minimum_required (VERSION 3.5)

project (FastShop)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++14")
set (source_dir "${PROJECT_SOURCE_DIR}/src")

file (GLOB_RECURSE source_files "${source_dir}/*.cpp")

message(STATUS "source_files=${source_files}")

add_executable (FastShop ${source_files})

# target_link_libraries(FastShop http)
# target_include_directories(FastShop PRIVATE ${FastShop_INCLUDE_DIRS})
