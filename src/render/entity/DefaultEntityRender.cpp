#include "DefaultEntityRender.h"//
// Created by dar on 11/28/15.
//

#include "DefaultEntityRender.h"
#include "../../core/map/block/Block.h"
#include <string>

DefaultEntityRender::DefaultEntityRender(const string &textureFile, const string &shader, int texId) : texId(texId) {
    texture.loadTexture2D(textureFile + string(".png"), true);
    texture.setFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_BILINEAR_MIPMAP);

    int a = this->vertShader.load(shader + string(".vert"), GL_VERTEX_SHADER);
    int b = this->fragShader.load(shader + string(".frag"), GL_FRAGMENT_SHADER);

    this->shaderProgram.createProgram();
    this->shaderProgram.addShaderToProgram(&this->vertShader);
    this->shaderProgram.addShaderToProgram(&this->fragShader);

    /* initializing square's vertices */
    this->vertices[0] = 0.0f;
    this->vertices[1] = 1.0f;

    this->vertices[2] = 0.0f;
    this->vertices[3] = 0.0f;

    this->vertices[4] = 1.0f;
    this->vertices[5] = 1.0f;

    this->vertices[6] = 1.0f;
    this->vertices[7] = 0.0f;

    glGenVertexArrays(1, &this->vao);
    glGenBuffers(2, this->vbo);

    glBindVertexArray(this->vao);

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo[0]); /* vertices vbo */
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), this->vertices, GL_STATIC_DRAW);
    glBindAttribLocation(this->shaderProgram.getProgramID(), 0, "inPosition");
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    float size = (float) (1.0 - (atlasSize + 1.5) / texture.getWidth()) / atlasSize;
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

void DefaultEntityRender::render(const Entity *const entity, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, double scale) {
    this->texture.bindTexture(0);
    this->shaderProgram.useProgram();

    Cache *cache = nullptr;

    if (entity->getId() < tmpCacheSize) {
        cache = matrixCache[entity->getId()];
        if (cache == nullptr) {
            cache = addToCache(new Cache(), entity);
        }
    } else {
        cache = addToCache(new Cache(), entity);
    }

    if (matrixCache[entity->getId()] == nullptr || entity->toBeRedrawn()) {
        this->shaderProgram.setUniform("projectionMatrix", projectionMatrix);
        this->shaderProgram.setUniform("gSampler", texture.getBoundId());

        glm::mat4x4 tmpModelMatrixVal;
        tmpModelMatrixVal = glm::translate(this->modelMatrix, glm::vec3(0.0f - (entity->getX() - entity->getWidth() / 2) * scale, 0.0f - (entity->getY() - entity->getHeight() / 2) * scale, 0.0f));

        tmpModelMatrixVal = glm::translate(tmpModelMatrixVal, glm::vec3(0.5 * scale, 0.5 * scale, 0.0)); // Translate to the middle of the entity
        tmpModelMatrixVal = glm::rotate(tmpModelMatrixVal, (const float) entity->getAngle(), glm::vec3(0.0f, 0.0f, 1.0f)); // Apply rotation
        tmpModelMatrixVal = glm::translate(tmpModelMatrixVal, glm::vec3(-0.5 * scale, -0.5 * scale, 0.0)); // Translate back to the origin

        tmpModelMatrixVal = glm::scale(tmpModelMatrixVal, glm::vec3(scale, scale, 1.0f));
        this->tmpModelMatrix = &tmpModelMatrixVal;

        cache->readyModelMatrix = *this->tmpModelMatrix;
    } else {
        this->tmpModelMatrix = &cache->readyModelMatrix;
    }

    shaderProgram.setUniform("modelViewMatrix", viewMatrix * *this->tmpModelMatrix);
    shaderProgram.setUniform("texPosX", 1.0f / this->texture.getWidth() + (float) (this->getTexPos(entity) % atlasSize) / atlasSize);
    shaderProgram.setUniform("texPosY", 1.0f / this->texture.getWidth() + (float) (this->getTexPos(entity) / atlasSize) / atlasSize);

    glBindVertexArray(this->vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

int DefaultEntityRender::getTexPos(const Entity *const entity) {
    return this->texId;
}

DefaultEntityRender::~DefaultEntityRender() {
    glDeleteBuffers(2, this->vbo);
    glDeleteVertexArrays(1, &this->vao);
}

int DefaultEntityRender::cacheLevel = 0;
DefaultEntityRender::Cache **DefaultEntityRender::matrixCache = nullptr;

DefaultEntityRender::Cache *DefaultEntityRender::addToCache(DefaultEntityRender::Cache *cache, const Entity *const entity) {
    if (entity->getId() > tmpCacheSize) {
        int prevSize = DefaultEntityRender::tmpCacheSize;
        while (entity->getId() > DefaultEntityRender::tmpCacheSize) {
            DefaultEntityRender::cacheLevel++;
            DefaultEntityRender::tmpCacheSize = DefaultEntityRender::calculateCacheSize();
        }
        DefaultEntityRender::Cache **newMatrixCache = new DefaultEntityRender::Cache *[DefaultEntityRender::tmpCacheSize];
        for (int i = 0; i < DefaultEntityRender::tmpCacheSize; i++) {
            newMatrixCache[i] = i < prevSize ? DefaultEntityRender::matrixCache[i] : nullptr;
        }
        delete[] DefaultEntityRender::matrixCache;
        DefaultEntityRender::matrixCache = newMatrixCache;
    }
    DefaultEntityRender::matrixCache[entity->getId()] = cache;
    return cache;
}

int DefaultEntityRender::calculateCacheSize() {
    return 2 * (DefaultEntityRender::cacheLevel + 6) * (DefaultEntityRender::cacheLevel + 6);
}

int DefaultEntityRender::tmpCacheSize = 0;
