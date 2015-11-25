PROJECT(c003)
CMAKE_MINIMUM_REQUIRED(VERSION 3.3)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(SOURCE_FILES main.cpp render/Shader.cpp render/Shader.h render/ShaderProgram.cpp render/ShaderProgram.h render/Texture.cpp render/Texture.h render/Fbo.cpp render/Fbo.h core/map/block/Block.h render/block/BlockRender.h render/Render.h render/block/SimpleBlockRender.cpp render/block/SimpleBlockRender.h core/map/block/SimpleBlock.h core/Core.cpp core/Core.h core/map/Map.cpp core/map/Map.h core/map/StringMapLoader.h Game.cpp Game.h render/SDLRenderer.cpp render/SDLRenderer.h)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCE_FILES})

INCLUDE(FindPkgConfig)
INCLUDE(FindOpenGL REQUIRED)
INCLUDE(cmake/FindSDL2.cmake REQUIRED)
INCLUDE(cmake/FindSOIL.cmake REQUIRED)

FIND_PACKAGE(SDL2 REQUIRED)
FIND_PACKAGE(SOIL REQUIRED)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${SOIL_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARY} ${OPENGL_LIBRARIES} ${SOIL_LIBRARIES})