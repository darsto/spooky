//
// Created by dar on 1/27/16.
//

#include "GuiElementRender.h"

GuiElementRender::GuiElementRender(const std::string &textureFile, const std::string &shader)
    : texture(textureFile) {
    texture.load();
    texture.filtering(texture::Atlas::MagFilter::BILINEAR, texture::Atlas::MinFilter::BILINEAR_MIPMAP);

    atlasSize = (uint32_t) sqrt(texture.getElementsNum());

    int a = this->vertShader.load(shader + std::string(".vert"), GL_VERTEX_SHADER);
    int b = this->fragShader.load(shader + std::string(".frag"), GL_FRAGMENT_SHADER);

    this->shaderProgram.createProgram();
    this->shaderProgram.addShaderToProgram(&this->vertShader);
    this->shaderProgram.addShaderToProgram(&this->fragShader);

    /* initializing square's vertices */
    this->vertices[0] = -1.0f;
    this->vertices[1] = -1.0f;

    this->vertices[2] = -1.0f;
    this->vertices[3] = 0.0f;

    this->vertices[4] = 0.0f;
    this->vertices[5] = -1.0f;

    this->vertices[6] = 0.0f;
    this->vertices[7] = 0.0f;

    glGenVertexArrays(1, &this->vao);
    glGenBuffers(2, this->vbo);

    glBindVertexArray(this->vao);

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo[0]); /* vertices vbo */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindAttribLocation(this->shaderProgram.getProgramID(), 0, "inPosition");
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    float tWidth = 1.0f / atlasSize - 1.0f / texture.width();
    float tHeight = 1.0f / atlasSize - 1.0f / texture.height();
    float tCoords[] = {
        tWidth, tHeight,
        tWidth, 0.0f,
        0.0f, tHeight,
        0.0f, 0.0f,
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
    if (element.visible()) {
        this->texture.bindTexture();
        this->shaderProgram.useProgram();
        this->shaderProgram.setUniform("projectionMatrix", projectionMatrix);
        this->shaderProgram.setUniform("gSampler", texture.activeTex());

        int color = element.color();
        float ca = (color & 0x000000FF) / 255.0f;
        float cr = ((color & 0xFF000000) >> 24) / 255.0f * ca;
        float cg = ((color & 0x00FF0000) >> 16) / 255.0f * ca;
        float cb = ((color & 0x0000FF00) >> 8) / 255.0f * ca;

        shaderProgram.setUniform("colorMod", glm::vec4(cr, cg, cb, ca));

        this->tmpModelMatrix = glm::translate(this->modelMatrix, -glm::vec3(element.x() * scale, element.y() * scale, 0.0f));

        this->tmpModelMatrix = glm::translate(this->tmpModelMatrix, glm::vec3(0.5 * element.width() * scale, 0.5 * element.height() * scale, 0.0)); // Translate to the middle of the entity
        this->tmpModelMatrix = glm::rotate(this->tmpModelMatrix, (const float) element.angle(), glm::vec3(0.0f, 0.0f, 1.0f)); // Apply rotation
        this->tmpModelMatrix = glm::translate(this->tmpModelMatrix, glm::vec3(-0.5 * element.width() * scale, -0.5 * element.height() * scale, 0.0)); // Translate back to the origin

        this->tmpModelMatrix = glm::scale(this->tmpModelMatrix, glm::vec3(element.width() * scale, element.height() * scale, 1.0f));

        shaderProgram.setUniform("modelViewMatrix", viewMatrix * this->tmpModelMatrix);

        util::Rectangle tex = getTexPos(element);

        float x = (float) tex.x() / texture.width();
        float y = (float) tex.y() / texture.height();

        shaderProgram.setUniform("texPosX", x + 0.5f / texture.width());
        shaderProgram.setUniform("texPosY", y + 0.5f / texture.height());

        glBindVertexArray(this->vao);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
}

util::Rectangle GuiElementRender::getTexPos(const GuiElement &element) const {
    return texture.element(element.texPos());
}

GuiElementRender::~GuiElementRender() {
    glDeleteBuffers(2, this->vbo);
    glDeleteVertexArrays(1, &this->vao);
}
