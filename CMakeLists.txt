cmake_minimum_required(VERSION 3.7)
project(Recipe_Manager)

#set(CMAKE_CXX_STANDARD 11)

#set(SOURCE_FILES main.cpp)
#add_executable(Recipe_Manager ${SOURCE_FILES})
add_custom_target(output COMMAND make -C ${mytest_SOURCE_DIR}
        CLION_EXE_DIR=${PROJECT_BINARY_DIR})
