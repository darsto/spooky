PROJECT(c003_src)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)

option(PROFILER "Link with -lprofiler to use with google-perftools" OFF)
option(BUILD_SHARED "Build as shared library" OFF)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -iquote ${CMAKE_CURRENT_SOURCE_DIR}")
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../cmake)

IF (BUILD_SHARED)
    SET(TYPE SHARED)
ELSE ()
    SET(TYPE STATIC)
ENDIF ()

SET(SOURCE_FILES
        Application.cpp
        Application.h
        ApplicationContext.cpp
        ApplicationContext.h
        util/os.h
        util/collection.h
        util/collection.cpp
        util/log.h
        util/file.h
        util/file.cpp
        util/string.h
        util/Packer.cpp
        util/Packer.h
        util/Rectangle.cpp
        util/Rectangle.h
        util/string.cpp
        util/prof.cpp
        util/prof.h
        core/Timer.cpp
        core/Timer.h
        core/input/InputManager.cpp
        core/input/InputManager.h
        core/input/TouchPoint.cpp
        core/input/TouchPoint.h
        core/input/Keypress.cpp
        core/input/Keypress.h
        window/Window.cpp
        window/Window.h
        window/MainMenu.cpp
        window/MainMenu.h
        window/Menu.cpp
        window/Menu.h
        window/LoadingScreen.cpp
        window/LoadingScreen.h
        gui/GuiElement.cpp
        gui/GuiElement.h
        gui/GuiText.cpp
        gui/GuiText.h
        Config.cpp
        Config.h
        util/exceptions.cpp util/exceptions.h)

IF (NOT SIMULATION)
    SET(SOURCE_RENDER_FILES
            render/opengl.h
            render/opengl.cpp
            render/Shader.cpp
            render/Shader.h
            render/ShaderProgram.cpp
            render/ShaderProgram.h
            render/RenderManager.cpp
            render/RenderManager.h
            render/RenderContext.cpp
            render/RenderContext.h
            render/window/WindowRender.cpp
            render/window/WindowRender.h
            render/window/MenuRender.cpp
            render/window/MenuRender.h
            render/gui/GuiElementRender.cpp
            render/gui/GuiElementRender.h
            render/font/TextRender.cpp
            render/font/TextRender.h
            render/texture/Atlas.cpp
            render/texture/Atlas.h
            render/texture/exceptions.cpp
            render/texture/exceptions.h
            render/texture/Data.cpp
            render/texture/Data.h
            render/texture/Resampler.cpp
            render/texture/Resampler.h
            render/texture/Texture.cpp
            render/texture/Texture.h
            render/exceptions.cpp render/exceptions.h)
ENDIF ()

IF (EDITOR)
    SET(PROJECT_NAME c003_editor_lib)
ELSE ()
    SET(PROJECT_NAME c003_game_lib)
ENDIF ()

ADD_LIBRARY(${PROJECT_NAME} ${TYPE} ${SOURCE_FILES} ${SOURCE_RENDER_FILES})

IF (EDITOR)
    TARGET_COMPILE_DEFINITIONS(${PROJECT_NAME} PRIVATE EDITOR=1)
ENDIF ()

IF (DEBUG)
    TARGET_COMPILE_DEFINITIONS(${PROJECT_NAME} PRIVATE DEBUG=1)
ENDIF ()

IF (SIMULATION)
    TARGET_COMPILE_DEFINITIONS(${PROJECT_NAME} PRIVATE SIMULATION=1)
ENDIF ()

INCLUDE(FindPkgConfig)

INCLUDE(FindLua REQUIRED)
FIND_PACKAGE(Lua REQUIRED)

INCLUDE_DIRECTORIES(${LUA_INCLUDE_DIR} ${LUA_INCLUDE_DIR}/lua5.1 ${LUA_INCLUDE_DIR}/lua5.2 ${LUA_INCLUDE_DIR}/lua5.3)
INCLUDE_DIRECTORIES(ext/kaguya/include)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LUA_LIBRARIES})

IF (NOT SIMULATION)

    IF (ANDROID)
        TARGET_LINK_LIBRARIES(${PROJECT_NAME} GLESv2 log)
    ELSE ()
        INCLUDE(FindSDL2 REQUIRED)
        INCLUDE(FindOpenGL REQUIRED)

        FIND_PACKAGE(SDL2 REQUIRED)
        FIND_PACKAGE(GLEW REQUIRED)
        FIND_PACKAGE(OpenGL REQUIRED)

        INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})

        TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARY} ${GLEW_LIBRARY} ${OPENGL_LIBRARIES})
    ENDIF ()

    INCLUDE(FindSOIL REQUIRED)
    INCLUDE(FindBox2d REQUIRED)

    FIND_PACKAGE(SOIL REQUIRED)
    FIND_PACKAGE(Box2d REQUIRED)

    INCLUDE_DIRECTORIES(${SOIL_INCLUDE_DIR} ${BOX2D_INCLUDE_DIRS})

    TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SOIL_LIBRARIES} ${BOX2D_LIBRARIES})
ENDIF ()

IF (MINGW)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} m dinput8 dxguid dxerr8 gdi32 winmm imm32 ole32 oleaut32 shell32 version uuid)
    IF (NOT DEBUG)
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
    ENDIF ()
ENDIF ()

IF (PROFILER)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} profiler)
ENDIF ()
