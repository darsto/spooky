#include <SDL.h>
#include <GLES3/gl3.h>
#include "ShaderProgram.h"
#include "Texture.h"
#include <glm/glm.hpp>

#define GLM_FORCE_RADIANS

#include <glm/gtc/matrix_transform.hpp>

//Screen dimension constants
const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 500;
//Main loop flag
bool quit = false;

//Starts up SDL, creates window, and initializes OpenGL
bool init();

//Initializes matrices and clear color
bool initGL();

//Input handler
void handleKeys(unsigned char key, int x, int y);

//Per frame update
void update();

//Renders quad to the screen
void render();

//Frees media and shuts down SDL
void close();

void initScene();

//The window we'll be rendering to
SDL_Window *gWindow = NULL;
//OpenGL context
SDL_GLContext gContext;
//Render flag
bool gRenderQuad = true;

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
Shader shFBOVertex, shFBOFragment;
ShaderProgram spFBO;

Texture tGold;

const int fboPasses = 1;

GLuint fbo[fboPasses], fbo_texture[fboPasses], rbo_depth[fboPasses];
GLuint vbo_fbo_vertices[fboPasses], fboVAO[fboPasses];
GLint attribute_v_coord_postproc, uniform_fbo_texture;

void initScene() {
    shFBOVertex.load("fboshader.vert", GL_VERTEX_SHADER);
    shFBOFragment.load("fboshader.frag", GL_FRAGMENT_SHADER);
    spFBO.createProgram();
    spFBO.addShaderToProgram(&shFBOVertex);
    spFBO.addShaderToProgram(&shFBOFragment);

    spFBO.linkProgram();
    spFBO.useProgram();

    attribute_v_coord_postproc = glGetAttribLocation(spFBO.getProgramID(), "v_coord");
    uniform_fbo_texture = glGetUniformLocation(spFBO.getProgramID(), "fbo_texture");


    for (int i = 0; i < fboPasses; i++) {
        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, &fbo_texture[i]);
        glBindTexture(GL_TEXTURE_2D, fbo_texture[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glBindTexture(GL_TEXTURE_2D, 0);

        /* Framebuffer to link everything together */
        glGenFramebuffers(1, &fbo[i]);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo_texture[i], 0);
        GLenum status;
        if ((status = glCheckFramebufferStatus(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE) {
            fprintf(stderr, "glCheckFramebufferStatus: error %p", status);
            close();
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glGenVertexArrays(1, &fboVAO[i]); // Generate two VAOs, one for triangle and one for quad
        glGenBuffers(1, &vbo_fbo_vertices[i]);

        GLfloat fbo_vertices[] = {
                -1.0f, 1.0f,
                -1.0f, -1.0f,
                1.0f, 1.0f,
                1.0f, -1.0f,
        };

        glBindVertexArray(fboVAO[i]);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_fbo_vertices[i]);
        glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), fbo_vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray((GLuint) attribute_v_coord_postproc);
        glVertexAttribPointer((GLuint) attribute_v_coord_postproc, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glBindVertexArray(0);
    }


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

    shVertex.load("shader.vert", GL_VERTEX_SHADER);
    shFragment.load("shader.frag", GL_FRAGMENT_SHADER);

    spMain.createProgram();
    spMain.addShaderToProgram(&shVertex);
    spMain.addShaderToProgram(&shFragment);

    spMain.linkProgram();
    spMain.useProgram();

    tGold.loadTexture2D("rgba.png", true);
    tGold.setFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_BILINEAR_MIPMAP);

    glEnable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

void close() {
    glDeleteBuffers(2, uiVBO);
    glDeleteVertexArrays(1, &uiVAO);
    for (int i = 0; i < fboPasses; i++) {
        glDeleteBuffers(1, &vbo_fbo_vertices[i]);
        glDeleteVertexArrays(1, &fboVAO[i]);
        glDeleteRenderbuffers(1, &rbo_depth[i]);
        glDeleteTextures(1, &fbo_texture[i]);
        glDeleteFramebuffers(1, &fbo[i]);
        spFBO.deleteProgram();
    }
    tGold.releaseTexture();
    spMain.deleteProgram();
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
}

int main(int argc, char *args[]) {
    //Start up SDL and create window
    if (!init()) {
        printf("Failed to initialize!\n");
    }
    else {

        //Event handler
        SDL_Event e;

        //Enable text input
        SDL_StartTextInput();

        //While application is running
        while (!quit) {
            //Handle events on queue
            while (SDL_PollEvent(&e) != 0) {
                //User requests quit
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
            }

            handleKeys();

            glBindFramebuffer(GL_FRAMEBUFFER, fbo[0]);

            //Render quad
            render();

            for (int i = 0; i < fboPasses; i++) {
                glBindFramebuffer(GL_FRAMEBUFFER, i == fboPasses - 1 ? 0 : fbo[i + 1]);
                //glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
                //glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
                glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                spFBO.useProgram();
                spFBO.setUniform("vertical", i == 1);
                spFBO.setUniform("uResolution", glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT));
                glActiveTexture(GL_TEXTURE0 + i);
                glBindTexture(GL_TEXTURE_2D, fbo_texture[i]);
                glUniform1i(uniform_fbo_texture, /*GL_TEXTURE*/i);
                glBindVertexArray(fboVAO[i]);
                glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindTexture(GL_TEXTURE_2D, 0);
            }




            //Update screen
            SDL_GL_SwapWindow(gWindow);
        }

        //Disable text input
        SDL_StopTextInput();
    }

    //Free resources and close SDL
    close();

    return 0;
}