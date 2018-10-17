cmake_minimum_required (VERSION 2.6)

project ("ProjectEuler")

set(PROJECT_EULER_BASE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(PROJECT_EULER_RELEASE_DIRECTORY ${PROJECT_EULER_BASE_DIRECTORY}/release)

add_subdirectory(src)


