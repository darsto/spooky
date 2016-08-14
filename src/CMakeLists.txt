PROJECT(c003_game)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -iquote ${CMAKE_CURRENT_SOURCE_DIR}")
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../cmake)

if (ANDROID)
    SET(TYPE SHARED)
else ()
    SET(TYPE STATIC)
endif ()

SET(SOURCE_FILES
        core/Timer.h
        logging.h
        window/Window.h
        Application.cpp
        Application.h
        gui/GuiButton.h
        gui/GuiButton.cpp
        gui/GuiElement.h
        core/input/InputManager.cpp
        core/input/InputManager.h
        os.h
        gui/GuiText.h
        window/MainMenu.cpp
        window/MainMenu.h
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
        core/input/TouchPoint.cpp
        gui/GuiText.cpp
        util.cpp
        util.h
        util/Packer.cpp
        util/Packer.h
        util/Rectangle.cpp
        util/Rectangle.h
        )

if (NOT SIMULATION)
    SET(SOURCE_RENDER_FILES
            render/opengl.h
            render/opengl.cpp
            render/Shader.cpp
            render/Shader.h
            render/ShaderProgram.cpp
            render/ShaderProgram.h
            render/texture/Texture.cpp
            render/texture/Texture.h
            render/Fbo.cpp
            render/Fbo.h
            render/RenderManager.cpp
            render/RenderManager.h
            render/window/WindowRender.h
            render/font/TextRender.cpp
            render/font/TextRender.h
            render/gui/GuiElementRender.cpp
            render/gui/GuiElementRender.h
            render/window/MenuRender.cpp
            render/window/MenuRender.h
            render/RenderContext.cpp
            render/RenderContext.h
            render/texture/Resampler.cpp
            render/texture/Resampler.h
            render/texture/TextureAtlas.cpp
            render/texture/TextureAtlas.h
            )
endif ()

INCLUDE(FindPkgConfig)

if (EDITOR)
    SET(PROJECT_NAME ${PROJECT_NAME}_editor)
    ADD_LIBRARY(${PROJECT_NAME} ${TYPE} ${SOURCE_FILES} ${SOURCE_RENDER_FILES})
    TARGET_COMPILE_DEFINITIONS(${PROJECT_NAME} PRIVATE EDITOR=1)
else ()
    ADD_LIBRARY(${PROJECT_NAME} ${TYPE} ${SOURCE_FILES} ${SOURCE_RENDER_FILES})
endif ()

IF (NOT SIMULATION)
    INCLUDE(FindSOIL REQUIRED)
    INCLUDE(FindBox2d REQUIRED)

    FIND_PACKAGE(SOIL REQUIRED)
    FIND_PACKAGE(Box2d REQUIRED)

    INCLUDE_DIRECTORIES(${SOIL_INCLUDE_DIR} ${BOX2D_INCLUDE_DIRS})
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SOIL_LIBRARIES} ${BOX2D_LIBRARIES})
ENDIF ()

IF (DEBUG)
    TARGET_COMPILE_DEFINITIONS(${PROJECT_NAME} PRIVATE DEBUG=1)
endif ()

if (ANDROID)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} GLESv2 log)
else ()
    IF (SIMULATION)
        TARGET_COMPILE_DEFINITIONS(${PROJECT_NAME} PRIVATE SIMULATION=1)
    else ()
        INCLUDE(FindSDL2 REQUIRED)
        INCLUDE(FindOpenGL REQUIRED)
        FIND_PACKAGE(SDL2 REQUIRED)
        FIND_PACKAGE(GLEW REQUIRED)
        FIND_PACKAGE(OpenGL REQUIRED)
        INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})
        TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARY} ${GLEW_LIBRARY} ${OPENGL_LIBRARIES})
    endif ()
endif ()

INCLUDE(FindLua REQUIRED)
FIND_PACKAGE(Lua REQUIRED)

INCLUDE_DIRECTORIES(${LUA_INCLUDE_DIR} ${LUA_INCLUDE_DIR}/lua5.1 ${LUA_INCLUDE_DIR}/lua5.2 ${LUA_INCLUDE_DIR}/lua5.3)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LUA_LIBRARIES})

INCLUDE_DIRECTORIES(ext/kaguya/include)

if (MINGW)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} m dinput8 dxguid dxerr8 gdi32 winmm imm32 ole32 oleaut32 shell32 version uuid)
    IF (NOT DEBUG)
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
    ENDIF ()
elseif (NOT ANDROID AND DEBUG AND NOT SIMULATION)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} profiler)
endif ()
