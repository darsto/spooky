//
// Created by dar on 11/25/15.
//

#include "Renderer.h"

Renderer::Renderer(Core *core) : core(core) { }

bool Renderer::init() {
    if (!this->initWindow()) {
        printf("Failed to initialize window!\n");
    } else if (!this->initGL()) {
        printf("Unable to initialize OpenGL!\n");
    } else if (!this->initTextures()) {
        printf("Unable to initialize textures!\n");
    } else {
        initRenderers();
        initTexData();
        fbo.init(3, windowWidth, windowHeight, new float[4]{0.9, 0.9, 0.9, 1.0}, "fboshader");
        return true;
    }
    return false;
}

bool Renderer::initWindow() {
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) { //Initialize SDL
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else {
        //Use OpenGL 3.3
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

        //Create window
        gWindow = SDL_CreateWindow("C003", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else {
            gContext = SDL_GL_CreateContext(gWindow); //Create context
            if (gContext == NULL) {
                printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            } else {
                //Use Vsync
                if (SDL_GL_SetSwapInterval(1) < 0) {
                    printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
                }
            }
        }
    }

    return success;
}

bool Renderer::initGL() {
    viewMatrix = glm::lookAt(glm::vec3(0, 0, 0.0f), glm::vec3(0, 0, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    projectionMatrix = glm::ortho(0.0f, float(windowWidth), 0.0f, float(windowHeight));
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    return true;
}

bool Renderer::initTextures() {
    bool ret = true;
    if (!textureAtlas.loadTexture2D("terrain.png", true)) ret = false;
    textureAtlas.setFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_BILINEAR_MIPMAP);
    return ret;
}

void Renderer::tick() {
    fbo.bind();
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    textureAtlas.bindTexture(0);
    for (Block *block : core->getMap()->getBlocks()) {
        if (block->getX() * this->core->getGeneralScale() * this->core->getBlockSize() > -(signed) windowWidth / 2.0f - this->core->getCamX() &&
            (block->getX() - 1) * this->core->getGeneralScale() * this->core->getBlockSize() < -(signed) windowWidth / 2.0f - this->core->getCamX() + (signed) windowWidth &&
            block->getY() * this->core->getGeneralScale() * this->core->getBlockSize() > -(signed) windowHeight / 2.0f - this->core->getCamY() &&
            (block->getY() - 1) * this->core->getGeneralScale() * this->core->getBlockSize() < -(signed) windowHeight / 2.0f - this->core->getCamY() + (signed) windowHeight)
            getBlockRender(block)->render(block, textureAtlas.getBoundId(), projectionMatrix, glm::translate(viewMatrix, glm::vec3(
                (int) (-(signed) windowWidth / 2.0f - this->core->getCamX()),
                (int) ((signed) windowHeight / 2.0f - this->core->getCamY()), 0.0f
            )), this->core->getBlockSize() * this->core->getGeneralScale());
    }
    int entitiesNum = 0;
    for (int i = core->getMap()->getEntities().size() - 1; i >= 0; i--) {
        Entity *entity = core->getMap()->getEntities().at(i);
        if (entity->getX() * this->core->getGeneralScale() * this->core->getBlockSize() > -(signed) windowWidth / 2.0f - this->core->getCamX() &&
            (entity->getX() - 1) * this->core->getGeneralScale() * this->core->getBlockSize() < -(signed) windowWidth / 2.0f - this->core->getCamX() + (signed) windowWidth &&
            entity->getY() * this->core->getGeneralScale() * this->core->getBlockSize() > -(signed) windowHeight / 2.0f - this->core->getCamY() &&
            (entity->getY() - 1) * this->core->getGeneralScale() * this->core->getBlockSize() < -(signed) windowHeight / 2.0f - this->core->getCamY() + (signed) windowHeight) {
            getEntityRender(entity)->render(entity, projectionMatrix, glm::translate(viewMatrix, glm::vec3(
                (int) (-(signed) windowWidth / 2.0f - this->core->getCamX()),
                (int) ((signed) windowHeight / 2.0f - this->core->getCamY()),
                0.0f)), this->core->getBlockSize() * this->core->getGeneralScale());
            fbo.getShaderProgram()->useProgram();
            if (entity != this->core->getPlayer() && entitiesNum < fbo.MAX_LIGHT_SRCS) {
                fbo.getShaderProgram()->setUniform("lightPoints[" + to_string(entitiesNum) + "]",
                                                   glm::vec2(this->core->getCamX() + (entity->getX() - 0.5 + entity->getWidth() / 2) * this->core->getBlockSize() * this->core->getGeneralScale() + (double) this->windowWidth / 2,
                                                             -this->core->getCamY() - (entity->getY() - 0.5 + entity->getHeight() / 2) * this->core->getBlockSize() * this->core->getGeneralScale() + (double) this->windowHeight / 2));
                entitiesNum++;
            }
        }
    }
    fbo.unbind();
    fbo.getShaderProgram()->useProgram();
    fbo.getShaderProgram()->setUniform("lightPointsNum", entitiesNum);
    fbo.getShaderProgram()->setUniform("scale", (float)(this->core->getBlockSize() * this->core->getGeneralScale()));
    fbo.render(0);
}

void Renderer::run() {
    this->tick();
    SDL_GL_SwapWindow(gWindow);
}

void Renderer::resize(unsigned int width, unsigned int height) {
    if (width != this->windowWidth || height != this->windowHeight) {
        this->windowWidth = width;
        this->windowHeight = height;
        glViewport(0, 0, windowWidth, windowHeight);
        viewMatrix = glm::lookAt(glm::vec3(0, 0, 0.0f), glm::vec3(0, 0, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        this->projectionMatrix = glm::ortho(0.0f, float(windowWidth), 0.0f, float(windowHeight));
        this->fbo.resize(this->windowWidth, this->windowHeight);
    }
}

Renderer::~Renderer() {
    SDL_DestroyWindow(this->gWindow);
    SDL_Quit();
}
