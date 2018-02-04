project(libft C)
cmake_minimum_required(VERSION 3.9)

file(GLOB_RECURSE SRCS srcs *.c)
add_library(ft ${SRCS})
target_include_directories(ft PUBLIC includes)
