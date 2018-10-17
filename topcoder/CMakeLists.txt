cmake_minimum_required (VERSION 2.6)

project ("TopCoder")

set(TOP_CODER_BASE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(TOP_CODER_RELEASE_DIRECTORY ${TOP_CODER_BASE_DIRECTORY}/release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

add_subdirectory(src)


