cmake_minimum_required(VERSION 3.7)
project(Recipe_Manager)

#set(CMAKE_CXX_STANDARD 11)

#set(SOURCE_FILES src/main.cpp src/Backend/Connection.cpp src/Backend/Data.cpp src/Backend/Recipe.cpp src/Backend/User.cpp src/Frontend/Frontend.cpp src/Frontend/Screen.cpp src/Frontend/ScreenLogin.cpp src/Frontend/ScreenIngredients.cpp)
#add_executable(Recipe_Manager ${SOURCE_FILES})
add_custom_target(jahodpa1 COMMAND make -C ${mytest_SOURCE_DIR}
       CLION_EXE_DIR=${PROJECT_BINARY_DIR})
