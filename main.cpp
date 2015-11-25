#include <SDL.h>
#include <GLES3/gl3.h>
#include "ShaderProgram.h"
#include "Texture.h"
#include "Fbo.h"
#include <glm/glm.hpp>

#define GLM_FORCE_RADIANS

#include <glm/gtc/matrix_transform.hpp>

const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 500;
//Main loop flag
bool quit = false;

//Starts up SDL, creates window, and initializes OpenGL
bool init();
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
bool init() {
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

float fQuad[12]; // Data to render quad using triangle strips (4 vertices, each has 3 floats)

GLuint uiVBO[2];
GLuint uiVAO;

Shader shVertex, shFragment;
ShaderProgram spMain;


Texture tGold;

void initScene() {
    // Setup quad vertices

    fQuad[0] = 0.0f;
    fQuad[1] = 1.0f;

    fQuad[3] = 0.0f;
    fQuad[4] = 0.0f;

    fQuad[6] = 1.0f;
    fQuad[7] = 1.0f;

    fQuad[9] = 1.0f;
    fQuad[10] = 0.0f;

    fQuad[2] = fQuad[5] = fQuad[8] = fQuad[11] = 0.0f;


    glGenVertexArrays(1, &uiVAO);
    glGenBuffers(2, uiVBO);

    // Setup whole quad
    glBindVertexArray(uiVAO);

    glBindBuffer(GL_ARRAY_BUFFER, uiVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), fQuad, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    float tCoords[] = {
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 0.0f,
            0.0f, 1.0f,
    };

    glBindBuffer(GL_ARRAY_BUFFER, uiVBO[1]);
    glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), tCoords, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);

    initBlockSp();

    tGold.loadTexture2D("rgba.png", true);
    tGold.setFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_BILINEAR_MIPMAP);

    glEnable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void initBlockSp() {
    shVertex.load("shader.vert", GL_VERTEX_SHADER);
    shFragment.load("shader.frag", GL_FRAGMENT_SHADER);

    spMain.createProgram();
    spMain.addShaderToProgram(&shVertex);
    spMain.addShaderToProgram(&shFragment);

    spMain.linkProgram();
    spMain.useProgram();
}

bool initGL() {
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

char map[] = {'X', 'X', ' ', ' ', 'X', 'X',
              'X', ' ', 'X', ' ', ' ', ' ',
              ' ', ' ', ' ', ' ', 'X', ' ',
              ' ', 'X', 'X', 'X', 'X', ' ',
              'X', ' ', ' ', ' ', ' ', ' '
};

int h = 5, w = 6;

void render() {
    //Clear color buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glm::mat4 mCurrent;
    glm::mat4 ProjectionMatrix = glm::ortho(0.0f, float(SCREEN_WIDTH), 0.0f, float(SCREEN_HEIGHT));
    glm::mat4 ModelMatrix = glm::mat4(1.0);

    float generalScale = 1;
    float blockSize = 50.0f;

    glm::mat4 ViewMatrix = glm::lookAt(glm::vec3(camX, camY, 0.0f), glm::vec3(camX, camY, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    spMain.useProgram();
    tGold.bindTexture(9);
    spMain.setUniform("gSampler", 9);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (map[y * w + x] == ' ') continue;


            spMain.setUniform("projectionMatrix", ProjectionMatrix);
            mCurrent = glm::translate(ModelMatrix, glm::vec3(0.0f - x * blockSize * generalScale, 0.0f - y * blockSize * generalScale, 0.0f));
            mCurrent = glm::scale(mCurrent, glm::vec3(blockSize * generalScale, blockSize * generalScale, 1.0f));
            mCurrent = glm::rotate(mCurrent, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f)); // Just a variation of first rotating

            spMain.setUniform("modelViewMatrix", ViewMatrix * mCurrent);

            glBindVertexArray(uiVAO);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        }
    }
}

Fbo *fbo;

void close() {
    glDeleteBuffers(2, uiVBO);
    glDeleteVertexArrays(1, &uiVAO);
    delete fbo;
    tGold.releaseTexture();
    spMain.deleteProgram();
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
}

//TODO move
static void staticInit() {
    initTexData();
}

int main(int argc, char *args[]) {
    if (!init()) {
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