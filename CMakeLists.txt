cmake_minimum_required(VERSION 3.10)

project(CHARMS)

#add_library(sinenomine SHARED
#    main.cpp)

set ( sources_list main.c src/terminfo.c )
add_executable(Charms ${sources_list})
set_property(TARGET Charms PROPERTY CMAKE_CXX_STANDARD 99)
target_include_directories(Charms PUBLIC include)
