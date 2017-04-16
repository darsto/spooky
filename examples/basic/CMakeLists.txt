PROJECT(spooky_examples_basic)
CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -iquote ${CMAKE_CURRENT_SOURCE_DIR}/src")

SET(SOURCE_FILES
        src/main.cpp
        src/window/MainMenu.cpp
        src/window/MainMenu.h
        src/window/Menu.cpp
        src/window/Menu.h
        src/window/LoadingScreen.cpp
        src/window/LoadingScreen.h
        src/gui/GuiElement.cpp
        src/gui/GuiElement.h
        )

IF (NOT SIMULATION)
    SET(SOURCE_FILES
            ${SOURCE_FILES}
            src/render/window/MenuRender.cpp
            src/render/window/MenuRender.h
            src/render/gui/GuiElementRender.cpp
            src/render/gui/GuiElementRender.h
            src/render/texture/TexData.cpp
            src/render/texture/TexData.h
            src/render/texture/Texture.cpp
            src/render/texture/Texture.h
            src/render/Shader.cpp
            src/render/Shader.h
            src/render/ShaderProgram.cpp
            src/render/ShaderProgram.h
            )
ENDIF ()

ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} spooky)

OPTION(DISABLE_EGL "" ON)
ADD_SUBDIRECTORY(src/ext/SOIL2)

INCLUDE_DIRECTORIES(SYSTEM ${SOIL2_INCLUDE_DIR})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} SOIL2)