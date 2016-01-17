PROJECT(c003_game)
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(SOURCE_FILES render/Shader.cpp render/Shader.h render/ShaderProgram.cpp render/ShaderProgram.h render/Texture.cpp render/Texture.h render/Fbo.cpp render/Fbo.h core/map/block/Block.h render/block/BlockRender.h render/Render.h render/block/SimpleBlockRender.cpp render/block/SimpleBlockRender.h core/map/block/SimpleBlock.h core/Core.cpp core/Core.h core/map/Map.cpp core/map/Map.h core/map/StringMapLoader.h render/Renderer.cpp render/Renderer.h Game.cpp Game.h core/Timer.h core/entity/Entity.h core/entity/Player.cpp core/entity/Player.h render/entity/EntityRender.h render/entity/DefaultEntityRender.cpp render/entity/DefaultEntityRender.h core/entity/EntityMoving.cpp core/entity/EntityMoving.h core/entity/Entity.cpp core/map/block/Block.cpp core/entity/EntityProjectile.cpp core/entity/EntityProjectile.h core/IPositionable.h core/entity/EntityBullet.cpp core/entity/EntityBullet.h core/map/CollisionListener.h core/Ray.cpp core/Ray.h core/Utils.h core/entity/Toy.h core/map/TiledTxtMapLoader.h render/entity/PlayerRender.h core/map/ContactFilter.h core/entity/SimpleShape.h render/entity/SimpleShapeRender.h core/entity/ILighted.h render/opengl.h render/opengl.cpp android.h)
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../cmake)

INCLUDE(FindPkgConfig)
INCLUDE(${PROJECT_SOURCE_DIR}/../cmake/FindSOIL.cmake REQUIRED)
INCLUDE(${PROJECT_SOURCE_DIR}/../cmake/FindBox2d.cmake REQUIRED)

FIND_PACKAGE(SOIL REQUIRED)
FIND_PACKAGE(Box2d REQUIRED)

ADD_LIBRARY(${PROJECT_NAME} ${SOURCE_FILES})

INCLUDE_DIRECTORIES(${SOIL_INCLUDE_DIR} ${BOX2D_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SOIL_LIBRARIES} ${BOX2D_LIBRARIES})

if(ANDROID)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} GLESv2 log)
else()
    INCLUDE(${PROJECT_SOURCE_DIR}/../cmake/FindSDL2.cmake REQUIRED)
    INCLUDE(FindOpenGL REQUIRED)
    FIND_PACKAGE(SDL2 REQUIRED)
    FIND_PACKAGE(GLEW REQUIRED)
    FIND_PACKAGE(OpenGL REQUIRED)
    INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARY} ${GLEW_LIBRARY} ${OPENGL_LIBRARIES})
endif()

if(MINGW)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} m dinput8 dxguid dxerr8 gdi32 winmm imm32 ole32 oleaut32 shell32 version uuid)
endif(MINGW)
