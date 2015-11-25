#include <SDL.h>
#include <GLES3/gl3.h>
#include "ShaderProgram.h"
#include "Texture.h"
#include "Fbo.h"
#include "core/block/Block.h"
#include "render/Render.h"
#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 500;
//Main loop flag
bool quit = false;

//Starts up SDL, creates window, and initializes OpenGL
bool initW();
bool initGL();
//Input handler
void handleKeys(unsigned char key, int x, int y);

//Per frame update
void update();

void render();

void close();
void initScene();
void initBlockSp();
SDL_Window *gWindow = NULL;
SDL_GLContext gContext;
bool initW() {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else {
        //Use OpenGL 2.1
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

        //Create window
        gWindow = SDL_CreateWindow("C003", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else {
            //Create context
            gContext = SDL_GL_CreateContext(gWindow);
            if (gContext == NULL) {
                printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else {
                //Use Vsync
                if (SDL_GL_SetSwapInterval(1) < 0) {
                    printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
                }

                //Initialize OpenGL
                if (!initGL()) {
                    printf("Unable to initialize OpenGL!\n");
                    success = false;
                }

                initScene();
            }
        }
    }

    return success;
}

Texture tGold;

vector<Block *> blocks;

char map_bl[] = {'X', 'X', ' ', ' ', 'X', 'X',
                 'X', ' ', 'X', ' ', ' ', ' ',
                 ' ', ' ', ' ', ' ', 'X', ' ',
                 ' ', 'X', 'X', 'X', 'X', ' ',
                 'X', ' ', ' ', ' ', ' ', ' '
};

int h = 5, w = 6;


void initScene() {
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (map_bl[y * w + x] == ' ') continue;
            blocks.push_back(new SimpleBlock(x, y));
        }
    }
    tGold.loadTexture2D("rgba.png", true);
    tGold.setFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_BILINEAR_MIPMAP);

    glEnable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

bool initGL() {
    init();
    bool success = true;
    return success;
}

float camX = SCREEN_WIDTH / 2.0f, camY = -SCREEN_HEIGHT / 2.0f;

void handleKeys() {
    float SPEED = -2.5f;
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_W]) {
        camY -= SPEED;
    }
    if (keystate[SDL_SCANCODE_S]) {
        camY += SPEED;
    }
    if (keystate[SDL_SCANCODE_A]) {
        camX -= SPEED;
    }
    if (keystate[SDL_SCANCODE_D]) {
        camX += SPEED;
    }
    if (keystate[SDL_SCANCODE_Q]) {
        quit = true;
    }
}

void update() {
    //No per frame update needed
}


void render() {
    //Clear color buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glm::mat4 ProjectionMatrix = glm::ortho(0.0f, float(SCREEN_WIDTH), 0.0f, float(SCREEN_HEIGHT));

    glm::mat4 ViewMatrix = glm::lookAt(glm::vec3(camX, camY, 0.0f), glm::vec3(camX, camY, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    tGold.bindTexture(10);

    for (int i = 0; i < blocks.size(); i++) {
        getBlockRender(blocks.at(i))->render(blocks.at(i), ProjectionMatrix, ViewMatrix);
    }

}

Fbo *fbo;

void close() {
    for (int i = 0; i < blocks.size(); i++) {
        delete blocks.at(i);
    }
    blocks.clear();
    delete fbo;
    tGold.releaseTexture();
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
}

//TODO move
static void staticInit() {
    initTexData();
}

int main(int argc, char *args[]) {
    if (!initW()) {
        printf("Failed to initialize!\n");
    }
    else {
        staticInit();
        fbo = new Fbo();
        fbo->init(5, SCREEN_WIDTH, SCREEN_HEIGHT, new float[4] {0.8f, 0.8f, 0.8f, 1.0f}, "fboshader");
        SDL_Event e;

        SDL_StartTextInput();

        while (!quit) {
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
            }
            handleKeys();
            fbo->bind();
            render();
            fbo->unbind();
            fbo->render(0);
            SDL_GL_SwapWindow(gWindow);
        }

        SDL_StopTextInput();
    }

    close();

    return 0;
}