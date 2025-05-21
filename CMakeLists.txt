cmake_minimum_required(VERSION 3.10)

project(CHARMS)

#add_library(sinenomine SHARED
#    main.cpp)

file(GLOB_RECURSE src_files src/*.c)

set ( sources_list main.c ${src_files})
add_executable(Charms ${sources_list})
set_property(TARGET Charms PROPERTY CMAKE_CXX_STANDARD 99)
target_include_directories(Charms PUBLIC include)

target_compile_options(Charms PRIVATE -fdebug-prefix-map=${CMAKE_SOURCE_DIR}=.)
set(CMAKE_BUILD_TYPE Debug)
target_compile_options(Charms PRIVATE -ffile-prefix-map=${CMAKE_SOURCE_DIR}=..)