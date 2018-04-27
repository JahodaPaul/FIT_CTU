PROJECT( game )
CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_DOC "Build documentation" ON)

find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

LIST(APPEND CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules/")
LIST(APPEND CMAKE_MODULE_PATH "/usr/local/share/SFML/cmake/Modules/")

FIND_PACKAGE(SFML 2.4 REQUIRED system window graphics network audio)
find_package(OpenGL REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
INCLUDE_DIRECTORIES( ./include ./imgui ./imgui-sfml )

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -pedantic -fsanitize=address")

ADD_EXECUTABLE(game src/main.cpp src/Controller/GameController.cpp src/Controller/MenuStateHandler.cpp src/Controller/GameStateHandler.cpp src/View/View.cpp src/View/MenuScene.cpp src/View/Scene.cpp imgui/imgui.cpp imgui/imgui_draw.cpp imgui-sfml/imgui-SFML.cpp imgui/imgui_demo.cpp src/View/Console.cpp src/Controller/GameController.cpp src/View/GameScene.cpp src/View/Animation.cpp )

LINK_DIRECTORIES(/usr/local/lib)
INCLUDE_DIRECTORIES( ./include )

TARGET_LINK_LIBRARIES (game sfml-graphics sfml-system sfml-window ${OPENGL_LIBRARIES} )
