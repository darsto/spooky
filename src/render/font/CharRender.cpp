//
// Created by dar on 2/11/16.
//

#include "CharRender.h"
#include <glm/gtc/matrix_transform.hpp>
#include <logging.h>

CharRender::CharRender() {
    texture.loadTexture2D("font.png", true);
    texture.setFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_BILINEAR_MIPMAP);

    this->vertShader.load("font.vert", GL_VERTEX_SHADER);
    this->fragShader.load("font.frag", GL_FRAGMENT_SHADER);
    this->shaderProgram.createProgram();
    this->shaderProgram.addShaderToProgram(&this->vertShader);
    this->shaderProgram.addShaderToProgram(&this->fragShader);

    /* initializing square's vertices */
    this->vertices[0] = 0.0f;
    this->vertices[1] = 1.0f;

    this->vertices[3] = 0.0f;
    this->vertices[4] = 0.0f;

    this->vertices[6] = 1.0f;
    this->vertices[7] = 1.0f;

    this->vertices[9] = 1.0f;
    this->vertices[10] = 0.0f;

    /* 3rd dimension vertices (unused) */
    this->vertices[2] = this->vertices[5] = this->vertices[8] = this->vertices[11] = 0.0f;

    glGenVertexArrays(1, &this->vao);
    glGenBuffers(2, this->vbo);

    glBindVertexArray(this->vao);

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo[0]); /* vertices vbo */
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), this->vertices, GL_STATIC_DRAW);
    glBindAttribLocation(this->shaderProgram.getProgramID(), 0, "inPosition");
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    float size = 1.0f / atlasSize - 1.0f / texture.getWidth();
    float tCoords[] = {
        size, 0.0f,
        size, size,
        0.0f, 0.0f,
        0.0f, size,
    };

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo[1]); /* texture coords vbo */
    glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), tCoords, GL_STATIC_DRAW);
    glBindAttribLocation(this->shaderProgram.getProgramID(), 1, "inCoord");
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);

    this->shaderProgram.linkProgram();
    this->shaderProgram.useProgram();
}

void CharRender::render(char character, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, int x, int y, float scale, int color /* TODO, unused yet */, char flags) {
    texture.bindTexture(0);
    this->shaderProgram.useProgram();
    this->shaderProgram.setUniform("projectionMatrix", projectionMatrix);
    this->shaderProgram.setUniform("gSampler", texture.getBoundId());


    this->tmpModelMatrix = glm::translate(this->modelMatrix, glm::vec3(-(x + scale), -y, 0.0f));
    this->tmpModelMatrix = glm::scale(this->tmpModelMatrix, glm::vec3(scale, scale, 1.0f));

    shaderProgram.setUniform("modelViewMatrix", viewMatrix * this->tmpModelMatrix);

    int texId = this->getGlyphPos(character);
    int texX = texId % atlasSize,  texY = texId / atlasSize;
    shaderProgram.setUniform("texPosX", 0.5f / texture.getWidth() + (float) texX / atlasSize);
    shaderProgram.setUniform("texPosY", 0.5f / texture.getHeight() + (float) texY / atlasSize);

    glBindVertexArray(this->vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

CharRender::~CharRender() {
    glDeleteBuffers(2, this->vbo);
    glDeleteVertexArrays(1, &this->vao);
}

float CharRender::getGlyphSize(char character) {
    if (character > 0 && character < atlasSize * atlasSize) return (float)(GLYPH_SIZE[character] % 64) / 64;
    return -1;
}