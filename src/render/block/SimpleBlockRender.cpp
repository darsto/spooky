//
// Created by dar on 11/25/15.
//

#define GLM_FORCE_RADIANS

#include "../opengl.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "SimpleBlockRender.h"
#include "../../core/map/block/SimpleBlock.h"
#include "../Render.h"

SimpleBlockRender::SimpleBlockRender() {
    this->vertShader.load("shader.vert", GL_VERTEX_SHADER);
    this->fragShader.load("shader.frag", GL_FRAGMENT_SHADER);

    this->shaderProgram.createProgram();
    this->shaderProgram.addShaderToProgram(&this->vertShader);
    this->shaderProgram.addShaderToProgram(&this->fragShader);

    this->shaderProgram.linkProgram();
    this->shaderProgram.useProgram();

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

    float tCoords[] = {
            1.0f / atlasSize, 0.0f,
            1.0f / atlasSize, 1.0f / atlasSize,
            0.0f, 0.0f,
            0.0f, 1.0f / atlasSize,
    };

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo[1]); /* texture coords vbo */
    glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), tCoords, GL_STATIC_DRAW);
    glBindAttribLocation(this->shaderProgram.getProgramID(), 1, "inCoord");
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);
}

void SimpleBlockRender::render(const Block *const block, int texId, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, double scale) {
    this->shaderProgram.useProgram();
    this->shaderProgram.setUniform("projectionMatrix", projectionMatrix);
    this->shaderProgram.setUniform("gSampler", texId);


    this->tmpModelMatrix = glm::translate(this->modelMatrix, glm::vec3(0.0f - block->getX() * scale, 0.0f - block->getY() * scale, 0.0f));
    this->tmpModelMatrix = glm::scale(this->tmpModelMatrix, glm::vec3(scale, scale, 1.0f));
    this->tmpModelMatrix = glm::rotate(this->tmpModelMatrix, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f)); // Just a variation of first rotating

    shaderProgram.setUniform("modelViewMatrix", viewMatrix * this->tmpModelMatrix);
    shaderProgram.setUniform("texPosX", (float) (this->getTexPos(block) % atlasSize) / atlasSize);
    shaderProgram.setUniform("texPosY", (float) (this->getTexPos(block) / atlasSize) / atlasSize);

    glBindVertexArray(this->vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

int SimpleBlockRender::getTexPos(const Block *const block) {
    return ((SimpleBlock *) block)->getTexPos();
}

SimpleBlockRender::~SimpleBlockRender() {
    glDeleteBuffers(2, this->vbo);
    glDeleteVertexArrays(1, &this->vao);
}
