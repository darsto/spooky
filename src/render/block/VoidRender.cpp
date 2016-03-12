//
// Created by dar on 3/5/16.
//

#include "VoidRender.h"

#define GLM_FORCE_RADIANS

#include "../opengl.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

VoidRender::VoidRender() {
    this->vertShader.load("void.vert", GL_VERTEX_SHADER);
    this->fragShader.load("void.frag", GL_FRAGMENT_SHADER);

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
    glBindVertexArray(0);

    this->shaderProgram.linkProgram();
    this->shaderProgram.useProgram();
}

void VoidRender::render(double x, double y, double width, double height, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, double scale, float r, float g, float b, float a) {
    this->shaderProgram.useProgram();
    this->shaderProgram.setUniform("projectionMatrix", projectionMatrix);

    this->tmpModelMatrix = glm::translate(this->modelMatrix, glm::vec3((-(x + width - 1) * scale), (-(y + height - 1) * scale), 0.0f));
    this->tmpModelMatrix = glm::scale(this->tmpModelMatrix, glm::vec3(width * scale, height * scale, 1.0f));

    shaderProgram.setUniform("modelViewMatrix", viewMatrix * this->tmpModelMatrix);

    shaderProgram.setUniform("color", glm::vec3(r, g, b));
    shaderProgram.setUniform("alpha", a);

    glBindVertexArray(this->vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

VoidRender::~VoidRender() {
    glDeleteBuffers(2, this->vbo);
    glDeleteVertexArrays(1, &this->vao);
}