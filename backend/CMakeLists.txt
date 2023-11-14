cmake_minimum_required (VERSION 3.5)

project (FastShop)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++14")
set (source_dir "${PROJECT_SOURCE_DIR}/src")
set (json_source_dir "${PROJECT_SOURCE_DIR}/lib/json")

file (GLOB_RECURSE source_files "${source_dir}/*.cpp")

message(STATUS "source_files=${source_files}")

set(JSON_SOURCE_FILES "${json_source_dir}/src/json_node.cpp" "${json_source_dir}/src/tokenizer.cpp" "${json_source_dir}/src/parser.cpp")
set(JSON_HEADER_FILES "${json_source_dir}/include/json_node.h" "${json_source_dir}/include/tokenizer.h" "${json_source_dir}/include/parser.h" "${json_source_dir}/include/serializable.h")

add_library(JSONParser STATIC ${JSON_HEADER_FILES} ${JSON_SOURCE_FILES})

add_executable (FastShop ${source_files})

target_link_libraries(FastShop JSONParser)
# target_include_directories(FastShop PRIVATE ${FastShop_INCLUDE_DIRS})
