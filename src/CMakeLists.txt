PROJECT(c003_game)
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
if (ANDROID)
    SET(TYPE SHARED)
else ()
    SET(TYPE STATIC)
endif ()

SET(SOURCE_FILES
        render/Shader.cpp
        render/Shader.h
        render/ShaderProgram.cpp
        render/ShaderProgram.h
        render/Texture.cpp
        render/Texture.h
        render/Fbo.cpp
        render/Fbo.h
        render/RenderManager.cpp
        render/RenderManager.h
        core/Timer.h
        render/opengl.h
        render/opengl.cpp
        logging.h
        window/Window.h
        Application.cpp
        Application.h
        render/window/WindowRender.h
        gui/GuiButton.h
        gui/GuiButton.cpp
        render/gui/GuiElementRender.cpp
        render/gui/GuiElementRender.h
        gui/GuiElement.h
        core/input/InputManager.cpp
        core/input/InputManager.h
        os.h
        render/font/TextRender.cpp
        render/font/TextRender.h
        gui/GuiText.h
        window/MainMenu.cpp
        window/MainMenu.h
        render/window/MenuRender.cpp
        render/window/MenuRender.h
        render/RenderContext.cpp
        render/RenderContext.h
        window/Menu.h
        window/Menu.cpp
        gui/GuiElement.cpp
        gui/GuiTextBubble.cpp
        gui/GuiTextBubble.h
        ApplicationContext.cpp
        ApplicationContext.h
        window/LoadingScreen.cpp
        window/LoadingScreen.h
        files.h
        files.cpp
        stringutils.h
        core/input/TouchPoint.h
        core/input/TouchPoint.cpp
        core/input/Keypress.cpp
        core/input/Keypress.h
        core/input/TouchPoint.cpp)
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../cmake)

INCLUDE(FindPkgConfig)
INCLUDE(${PROJECT_SOURCE_DIR}/../cmake/FindSOIL.cmake REQUIRED)
INCLUDE(${PROJECT_SOURCE_DIR}/../cmake/FindBox2d.cmake REQUIRED)

FIND_PACKAGE(SOIL REQUIRED)
FIND_PACKAGE(Box2d REQUIRED)

if (EDITOR)
    SET(PROJECT_NAME ${PROJECT_NAME}_editor)
    ADD_LIBRARY(${PROJECT_NAME} ${TYPE} ${SOURCE_FILES})
    TARGET_COMPILE_DEFINITIONS(${PROJECT_NAME} PRIVATE EDITOR=1)
else ()
    ADD_LIBRARY(${PROJECT_NAME} ${TYPE} ${SOURCE_FILES})
endif ()

INCLUDE_DIRECTORIES(${SOIL_INCLUDE_DIR} ${BOX2D_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SOIL_LIBRARIES} ${BOX2D_LIBRARIES})

IF (DEBUG)
    TARGET_COMPILE_DEFINITIONS(${PROJECT_NAME} PRIVATE __DEBUG__=1 DEBUG=1)
endif ()

if (ANDROID)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} GLESv2 log)
else ()
    INCLUDE(${PROJECT_SOURCE_DIR}/../cmake/FindSDL2.cmake REQUIRED)
    INCLUDE(FindOpenGL REQUIRED)
    FIND_PACKAGE(SDL2 REQUIRED)
    FIND_PACKAGE(GLEW REQUIRED)
    FIND_PACKAGE(OpenGL REQUIRED)
    INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARY} ${GLEW_LIBRARY} ${OPENGL_LIBRARIES})
endif ()

INCLUDE(FindLua REQUIRED)
FIND_PACKAGE(Lua REQUIRED)

INCLUDE_DIRECTORIES(${LUA_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LUA_LIBRARIES})

if (MINGW)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} m dinput8 dxguid dxerr8 gdi32 winmm imm32 ole32 oleaut32 shell32 version uuid)
    IF (NOT DEBUG)
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
    ENDIF ()
elseif (NOT ANDROID AND DEBUG)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} profiler)
endif ()
