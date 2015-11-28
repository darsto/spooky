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
        fbo.init(3, windowWidth, windowHeight, new float[4]{0.8f, 0.8f, 0.8f, 1.0f}, "fboshader");
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
    glClear(GL_COLOR_BUFFER_BIT);
    textureAtlas.bindTexture(0);
    for (Block *block : core->getMap()->getBlocks()) {
        getBlockRender(block)->render(block, textureAtlas.getBoundId(), projectionMatrix, glm::translate(viewMatrix, glm::vec3(-(signed) windowWidth / 2.0f - this->core->getCamX(), (signed) windowHeight / 2.0f - this->core->getCamY(), 0.0f)));
    }
    getEntityRender(this->core->getPlayer())->render(this->core->getPlayer(), projectionMatrix, glm::translate(viewMatrix, glm::vec3(-(signed) windowWidth / 2.0f - this->core->getCamX(), (signed) windowHeight / 2.0f - this->core->getCamY(), 0.0f)));
    fbo.unbind();
    fbo.render(0);
}

void Renderer::run() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            this->core->stop();
        } else if (e.type == SDL_WINDOWEVENT) {
            if (e.window.event == SDL_WINDOWEVENT_RESIZED || e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                this->resize((unsigned int) e.window.data1, (unsigned int) e.window.data2);
            }
        }
    }
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
