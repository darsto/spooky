//
// Created by dar on 11/25/15.
//

#define GLM_FORCE_RADIANS

#include <GLES3/gl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "SimpleBlockRender.h"

SimpleBlockRender::SimpleBlockRender() {
    /* initializing square's vertices */
    vertices[0] = 0.0f;
    vertices[1] = 1.0f;

    vertices[3] = 0.0f;
    vertices[4] = 0.0f;

    vertices[6] = 1.0f;
    vertices[7] = 1.0f;

    vertices[9] = 1.0f;
    vertices[10] = 0.0f;

    /* 3rd dimension vertices (unused) */
    vertices[2] = vertices[5] = vertices[8] = vertices[11] = 0.0f;

    glGenVertexArrays(1, &vao);
    glGenBuffers(2, vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); /* vertices vbo */
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    float tCoords[] = {
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 0.0f,
            0.0f, 1.0f,
    };

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); /* texture coords vbo */
    glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), tCoords, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);

    vertShader.load("shader.vert", GL_VERTEX_SHADER);
    fragShader.load("shader.frag", GL_FRAGMENT_SHADER);

    shaderProgram.createProgram();
    shaderProgram.addShaderToProgram(&vertShader);
    shaderProgram.addShaderToProgram(&fragShader);

    shaderProgram.linkProgram();
    shaderProgram.useProgram();
    shaderProgram.setUniform("gSampler", 10); //todo hardcoded variable
}

void SimpleBlockRender::render(const Block *const block, glm::mat4 projectionMatrix, glm::mat4 viewMatrix) {
    shaderProgram.useProgram();
    shaderProgram.setUniform("projectionMatrix", projectionMatrix);
    tmpModelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f - block->getX() * blockSize * generalScale, 0.0f - block->getY() * blockSize * generalScale, 0.0f));
    tmpModelMatrix = glm::scale(tmpModelMatrix, glm::vec3(blockSize * generalScale, blockSize * generalScale, 1.0f));
    tmpModelMatrix = glm::rotate(tmpModelMatrix, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f)); // Just a variation of first rotating

    shaderProgram.setUniform("modelViewMatrix", viewMatrix * tmpModelMatrix);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

SimpleBlockRender::~SimpleBlockRender() {
    glDeleteBuffers(2, vbo);
    glDeleteVertexArrays(1, &vao);
    shaderProgram.deleteProgram();
}
