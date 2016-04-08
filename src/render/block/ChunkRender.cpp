//
// Created by dar on 11/25/15.
//

#define GLM_FORCE_RADIANS

#include "../opengl.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ChunkRender.h"
#include "../../core/map/block/SimpleBlock.h"

ChunkRender::ChunkRender() : texVbos(1) {
    texture.loadTexture2D("terrain.png", true);
    texture.setFiltering(TEXTURE_FILTER_MAG_NEAREST, TEXTURE_FILTER_MIN_NEAREST_MIPMAP);

    this->vertShader.load("chunk.vert", GL_VERTEX_SHADER);
    this->fragShader.load("chunk.frag", GL_FRAGMENT_SHADER);

    this->shaderProgram.createProgram();
    this->shaderProgram.addShaderToProgram(&this->vertShader);
    this->shaderProgram.addShaderToProgram(&this->fragShader);

    float *vertices = new float[8 * Chunk::size * Chunk::size];
    for (int i = 0; i < Chunk::size * Chunk::size; i++) {

        /* initializing square's vertices */

        int x = -(i % Chunk::size);
        int y = -(i / Chunk::size);
        vertices[8 * i + 0] = x + 0.0f;
        vertices[8 * i + 1] = y + 1.0f;

        vertices[8 * i + 2] = x + 0.0f;
        vertices[8 * i + 3] = y + 0.0f;

        vertices[8 * i + 4] = x + 1.0f;
        vertices[8 * i + 5] = y + 1.0f;

        vertices[8 * i + 6] = x + 1.0f;
        vertices[8 * i + 7] = y + 0.0f;
    }

    short *indices = new short[6 * Chunk::size * Chunk::size];
    int last = 0;
    for (int i = 0; i < Chunk::size * Chunk::size; i++) {
        indices[(i * 6) + 0] = (short) (last + 0);
        indices[(i * 6) + 1] = (short) (last + 1);
        indices[(i * 6) + 2] = (short) (last + 2);
        indices[(i * 6) + 3] = (short) (last + 1);
        indices[(i * 6) + 4] = (short) (last + 2);
        indices[(i * 6) + 5] = (short) (last + 3);
        // 0,1,2,0,2,3 ; 4,5,6,4,6,7 ; etc
        last = last + 4;
    }

    glGenVertexArrays(1, &this->vao);
    glGenBuffers(1, &this->vertVbo);
    glGenBuffers(1, &this->indexVbo);

    glBindVertexArray(this->vao);

    glBindBuffer(GL_ARRAY_BUFFER, this->vertVbo); /* vertices vbo */
    glBufferData(GL_ARRAY_BUFFER, Chunk::size * Chunk::size * 8 * sizeof(float), vertices, GL_STATIC_DRAW);
    glBindAttribLocation(this->shaderProgram.getProgramID(), 0, "inPosition");
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexVbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Chunk::size * Chunk::size * 6 * sizeof(short), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);

    delete[] vertices;

    this->shaderProgram.linkProgram();
    this->shaderProgram.useProgram();
}

void ChunkRender::render(const Chunk *const chunk, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, double scale) {
    texture.bindTexture(0);
    this->shaderProgram.useProgram();

    int texVboId = chunk->getId();
    bool toBeIncreased = texVboId >= this->texVbos.size();
    if (toBeIncreased || chunk->toBeRedrawn()) {
        this->shaderProgram.setUniform("projectionMatrix", projectionMatrix);
        this->shaderProgram.setUniform("gSampler", texture.getBoundId());

        if (toBeIncreased) {
            this->texVbos.resize(texVboId + 1);
            glGenBuffers(1, &this->texVbos[texVboId]);
        }


        float size = 1.0f / atlasSize;
        float bleedfix = 1.0f / texture.getWidth();

        float *tCoords = new float[8 * Chunk::size * Chunk::size];

        for (int i = 0; i < Chunk::size * Chunk::size; i++) {
            Block *b = chunk->getBlocks()[i];
            if (b != nullptr) {
                int texId = ((SimpleBlock *) b)->getTexPos(); //TODO
                int x = texId % atlasSize, y = texId / atlasSize;

                tCoords[8 * i + 0] = size * (x + 1 - bleedfix);
                tCoords[8 * i + 1] = size * y;

                tCoords[8 * i + 2] = size * (x + 1 - bleedfix);
                tCoords[8 * i + 3] = size * (y + 1 - bleedfix);

                tCoords[8 * i + 4] = size * x;
                tCoords[8 * i + 5] = size * y;

                tCoords[8 * i + 6] = size * x;
                tCoords[8 * i + 7] = size * (y + 1 - bleedfix);
            } else {
                for (int j = 0; j < 7; j++) {
                    tCoords[8 * i + j] = 0;
                }
            }
        }

        glBindVertexArray(this->vao);
        glBindBuffer(GL_ARRAY_BUFFER, this->texVbos[texVboId]); /* texture coords vbo */
        glBufferData(GL_ARRAY_BUFFER, Chunk::size * Chunk::size * 8 * sizeof(float), tCoords, GL_STATIC_DRAW);
        glBindAttribLocation(this->shaderProgram.getProgramID(), 1, "inCoord");
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glBindVertexArray(0);

    }
    this->tmpModelMatrix = glm::translate(this->modelMatrix, glm::vec3((-chunk->getX() * scale * Chunk::size), (-chunk->getY() * scale * Chunk::size), 0.0f));
    this->tmpModelMatrix = glm::scale(this->tmpModelMatrix, glm::vec3(scale, scale, 1.0f));
    shaderProgram.setUniform("modelViewMatrix", viewMatrix * this->tmpModelMatrix);

    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->texVbos[texVboId]); /* texture coords vbo */
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexVbo);
    glDrawElements(GL_TRIANGLES, 6 * Chunk::size * Chunk::size, GL_UNSIGNED_SHORT, 0);
}

ChunkRender::~ChunkRender() {
    glDeleteBuffers(1, &this->vertVbo);
    for(auto const& texVbo : this->texVbos) {
        glDeleteBuffers(1, &texVbo);
    }
    glDeleteVertexArrays(1, &this->vao);
}