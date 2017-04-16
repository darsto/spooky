PROJECT(spooky)
CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

OPTION(BUILD_SHARED "Build as shared library" OFF)
OPTION(SIMULATION "Build without rendering support" OFF)

SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -iquote ${CMAKE_CURRENT_SOURCE_DIR}")
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../cmake)
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pedantic -Wall -Wextra -Wcast-align -Wcast-qual \
    -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op \
    -Wmissing-declarations -Wnoexcept -Woverloaded-virtual -Wredundant-decls \
    -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 \
    -Wswitch-default -Wundef -Werror")

IF (BUILD_SHARED)
    SET(TYPE SHARED)
ELSE ()
    SET(TYPE STATIC)
ENDIF ()

IF (CMAKE_BUILD_TYPE MATCHES "Debug")
    SET(DEBUG 1)
ENDIF ()

SET(SOURCE_FILES
        Application.cpp
        Application.h
        ApplicationContext.cpp
        ApplicationContext.h
        util/os.h
        util/log.h
        util/file.h
        util/file.cpp
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
        window/WindowManager.cpp
        window/WindowManager.h
        )

IF (NOT SIMULATION)
    SET(SOURCE_RENDER_FILES
            render/opengl.h
            render/opengl.cpp
            render/RenderManager.cpp
            render/RenderManager.h
            render/RenderContext.cpp
            render/RenderContext.h
            render/window/WindowRender.cpp
            render/window/WindowRender.h
            )

    SET(SOURCE_FILES ${SOURCE_FILES} ${SOURCE_RENDER_FILES})
ENDIF ()

ADD_LIBRARY(${PROJECT_NAME} ${TYPE} ${SOURCE_FILES})

IF (DEBUG)
    TARGET_COMPILE_DEFINITIONS(${PROJECT_NAME} PRIVATE DEBUG=1)
ENDIF ()

IF (SIMULATION)
    TARGET_COMPILE_DEFINITIONS(${PROJECT_NAME} PRIVATE SIMULATION=1)
ENDIF ()

INCLUDE(FindPkgConfig)

INCLUDE(FindLua REQUIRED)
FIND_PACKAGE(Lua REQUIRED)

IF (ANDROID)
    INCLUDE_DIRECTORIES(SYSTEM ${ANDROID_NDK_INCLUDE_DIR})
ENDIF ()

IF (NOT SIMULATION)
    IF (ANDROID)
        TARGET_LINK_LIBRARIES(${PROJECT_NAME} GLESv2 log)
    ELSE ()
        INCLUDE(FindSDL2 REQUIRED)
        INCLUDE(FindOpenGL REQUIRED)

        FIND_PACKAGE(SDL2 REQUIRED)
        FIND_PACKAGE(GLEW REQUIRED)
        FIND_PACKAGE(OpenGL REQUIRED)

        INCLUDE_DIRECTORIES(SYSTEM ${SDL2_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})

        TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARY} ${GLEW_LIBRARY} ${OPENGL_LIBRARIES})
    ENDIF ()
ENDIF ()

IF (MINGW)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} m dinput8 dxguid dxerr8 gdi32 winmm imm32 ole32 oleaut32 shell32 version uuid)
    IF (NOT DEBUG)
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
    ENDIF ()
ENDIF ()

IF (DEBUG)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} profiler)
ENDIF ()
