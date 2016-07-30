//
// Created by dar on 1/27/16.
//

#include "GuiElementRender.h"

GuiElementRender::GuiElementRender(const string &textureFile, const string &shader) {
    texture.loadTexture2D(textureFile + string(".png"), true);
    texture.setFiltering(TEXTURE_FILTER_MAG_NEAREST, TEXTURE_FILTER_MIN_TRILINEAR_MIPMAP);

    int a = this->vertShader.load(shader + string(".vert"), GL_VERTEX_SHADER);
    int b = this->fragShader.load(shader + string(".frag"), GL_FRAGMENT_SHADER);

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

    float tWidth = 1.0f / atlasSize - 1.0f / texture.getWidth();
    float tHeight = 1.0f / atlasSize - 1.0f / texture.getHeight();
    float tCoords[] = {
        tWidth, 0.0f,
        tWidth, tHeight,
        0.0f, 0.0f,
        0.0f, tHeight,
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

void GuiElementRender::render(const GuiElement &element, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, double scale) {
    if (element.isVisible()) {
        this->texture.bindTexture(0);
        this->shaderProgram.useProgram();
        this->shaderProgram.setUniform("projectionMatrix", projectionMatrix);
        this->shaderProgram.setUniform("gSampler", texture.getBoundId());

        int color = element.getColor();
        float ca = (color & 0x000000FF) / 255.0f;
        float cr = ((color & 0xFF000000) >> 24) / 255.0f * ca;
        float cg = ((color & 0x00FF0000) >> 16) / 255.0f * ca;
        float cb = ((color & 0x0000FF00) >> 8) / 255.0f * ca;

        shaderProgram.setUniform("colorMod", glm::vec4(cr, cg, cb, ca));

        this->tmpModelMatrix = glm::translate(this->modelMatrix, glm::vec3(-(element.getX() + element.getWidth()) * scale, -(element.getY() + element.getHeight()) * scale, 0.0f));

        this->tmpModelMatrix = glm::translate(this->tmpModelMatrix, glm::vec3(0.5 * element.getWidth() * scale, 0.5 * element.getHeight() * scale, 0.0)); // Translate to the middle of the entity
        this->tmpModelMatrix = glm::rotate(this->tmpModelMatrix, (const float) element.getAngle(), glm::vec3(0.0f, 0.0f, 1.0f)); // Apply rotation
        this->tmpModelMatrix = glm::translate(this->tmpModelMatrix, glm::vec3(-0.5 * element.getWidth() * scale, -0.5 * element.getHeight() * scale, 0.0)); // Translate back to the origin

        this->tmpModelMatrix = glm::scale(this->tmpModelMatrix, glm::vec3(element.getWidth() * scale, element.getHeight() * scale, 1.0f));

        shaderProgram.setUniform("modelViewMatrix", viewMatrix * this->tmpModelMatrix);
        float x = (float) (this->getTexPos(element) % atlasSize);
        float y = (float) (this->getTexPos(element) / atlasSize);
        shaderProgram.setUniform("texPosX", x / atlasSize + 0.5f / texture.getWidth());
        shaderProgram.setUniform("texPosY", y / atlasSize + 0.5f / texture.getHeight());

        glBindVertexArray(this->vao);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
}

int GuiElementRender::getTexPos(const GuiElement &element) const {
    return element.getTexPos(0);
}

GuiElementRender::~GuiElementRender() {
    glDeleteBuffers(2, this->vbo);
    glDeleteVertexArrays(1, &this->vao);
}
