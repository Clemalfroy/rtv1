project(rtv1 C)
cmake_minimum_required(VERSION 3.9)

add_subdirectory(libft)

file(GLOB_RECURSE SRCS src *.c)
add_executable(rtv1 ${SRCS})
target_include_directories(rtv1 PUBLIC includes)
target_link_libraries(rtv1 PUBLIC ft)
