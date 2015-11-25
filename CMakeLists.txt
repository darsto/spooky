PROJECT(c003)
CMAKE_MINIMUM_REQUIRED(VERSION 3.3)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(SOURCE_FILES main.cpp Shader.cpp Shader.h ShaderProgram.cpp ShaderProgram.h Texture.cpp Texture.h Fbo.cpp Fbo.h core/block/Block.h render/block/BlockRender.h render/Render.h render/block/SimpleBlockRender.cpp render/block/SimpleBlockRender.h core/block/SimpleBlock.h Core.cpp Core.h core/map/Map.cpp core/map/Map.h core/map/StringMapLoader.h)

ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCE_FILES})

INCLUDE(FindPkgConfig)
INCLUDE(FindOpenGL REQUIRED)
INCLUDE(FindSOIL.cmake REQUIRED)

PKG_SEARCH_MODULE(SDL2 REQUIRED SOIL)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${SOIL_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${SOIL_LIBRARIES})