//
// Created by dar on 11/24/15.
//

#include <GLES3/gl3.h>
#include "Fbo.h"

Fbo::~Fbo() {
    glDeleteTextures(1, &this->fbo_texture);
    glDeleteBuffers(1, &texture_vertices);
    glDeleteVertexArrays(1, &vaoId);
    glDeleteFramebuffers(1, &this->id);
    this->shader_program.deleteProgram();
}

unsigned char Fbo::initShader() {
    unsigned char errCode = 0;
    if (!vert_shader.load(this->shaderName + ".vert", GL_VERTEX_SHADER)) errCode |= 1 << 0;
    if (!frag_shader.load(this->shaderName + ".frag", GL_FRAGMENT_SHADER)) errCode |= 1 << 1;
    this->shader_program.createProgram();
    if (!this->shader_program.addShaderToProgram(&vert_shader)) errCode |= 1 << 2;
    if (!this->shader_program.addShaderToProgram(&frag_shader)) errCode |= 1 << 3;

    if (!this->shader_program.linkProgram()) errCode |= 1 << 4;
    this->shader_program.useProgram();

    GLint tmp_uniform_location = glGetUniformLocation(shader_program.getProgramID(), "fbo_texture");
    if (tmp_uniform_location < 0) errCode |= 1 << 5;
    this->shader_tex_uniform = (GLuint) glGetUniformLocation(shader_program.getProgramID(), "fbo_texture");
    return errCode;
}

int Fbo::init(int texId, unsigned int width, unsigned int height, float bgColor[], string shaderName) {
    this->texId = texId;
    this->width = width;
    this->height = height;
    this->bgColor = bgColor;
    this->shaderName = shaderName;

    unsigned char shaderRet = this->initShader();
    if (shaderRet != 0) {
        return shaderRet;
    }

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &this->fbo_texture);
    glBindTexture(GL_TEXTURE_2D, this->fbo_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenFramebuffers(1, &this->id);
    glBindFramebuffer(GL_FRAMEBUFFER, this->id);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->fbo_texture, 0);
    GLenum status = (GLenum) (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return status;
}


void Fbo::resize(unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;
    glBindTexture(GL_TEXTURE_2D, this->fbo_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);
}


void Fbo::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, this->id);
}

void Fbo::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Fbo::render(GLuint renderTo) {
    glBindFramebuffer(GL_FRAMEBUFFER, renderTo);
    glClearColor(this->bgColor[0], this->bgColor[1], this->bgColor[2], this->bgColor[3]);
    glClear(GL_COLOR_BUFFER_BIT);

    shader_program.useProgram();
    shader_program.setUniform("uResolution", glm::vec2(this->width, this->height));
    glActiveTexture(GL_TEXTURE0 + this->texId);
    glBindTexture(GL_TEXTURE_2D, this->fbo_texture);
    glUniform1i(this->shader_tex_uniform, /*GL_TEXTURE*/ this->texId);
    glBindVertexArray(vaoId);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

void initTexData() {
    glGenVertexArrays(1, &vaoId);
    glGenBuffers(1, &texture_vertices);

    GLfloat fbo_vertices[] = {
            -1.0f, 1.0f,
            -1.0f, -1.0f,
            1.0f, 1.0f,
            1.0f, -1.0f,
    };

    glBindVertexArray(vaoId);
    glBindBuffer(GL_ARRAY_BUFFER, texture_vertices);
    glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), fbo_vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray((GLuint) 0);
    glVertexAttribPointer((GLuint) 0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glBindVertexArray(0);
}