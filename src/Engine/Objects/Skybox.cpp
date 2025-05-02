#include "../../../include/Engine/Objects/Skybox.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include "../../../include/Utils/stb_image.h"

#define Point(a, b, c) a, b, c

Skybox::Skybox() {
}

void Skybox::set_shader(unsigned int _shader) {
    __shader = _shader;
}

void Skybox::draw() {
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_FALSE);
    glUseProgram(__shader);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
    glUniform1i(glGetUniformLocation(__shader, "skybox"), 0);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Skybox::add_cubemap_image(std::vector<std::string> faces) {
    stbi_set_flip_vertically_on_load(0);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
    unsigned char* data;
    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++) {
        data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);
        assert(data);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                     0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void Skybox::init() {
    float vertices[] = {
        Point(-1.0f, 1.0f, -1.0f),
        Point(-1.0f, -1.0f, -1.0f),
        Point(1.0f, -1.0f, -1.0f),
        Point(1.0f, -1.0f, -1.0f),
        Point(1.0f, 1.0f, -1.0f),
        Point(-1.0f, 1.0f, -1.0f),
        Point(-1.0f, -1.0f, 1.0f),
        Point(-1.0f, -1.0f, -1.0f),
        Point(-1.0f, 1.0f, -1.0f),
        Point(-1.0f, 1.0f, -1.0f),
        Point(-1.0f, 1.0f, 1.0f),
        Point(-1.0f, -1.0f, 1.0f),
        Point(1.0f, -1.0f, -1.0f),
        Point(1.0f, -1.0f, 1.0f),
        Point(1.0f, 1.0f, 1.0f),
        Point(1.0f, 1.0f, 1.0f),
        Point(1.0f, 1.0f, -1.0f),
        Point(1.0f, -1.0f, -1.0f),
        Point(-1.0f, -1.0f, 1.0f),
        Point(-1.0f, 1.0f, 1.0f),
        Point(1.0f, 1.0f, 1.0f),
        Point(1.0f, 1.0f, 1.0f),
        Point(1.0f, -1.0f, 1.0f),
        Point(-1.0f, -1.0f, 1.0f),
        Point(-1.0f, 1.0f, -1.0f),
        Point(1.0f, 1.0f, -1.0f),
        Point(1.0f, 1.0f, 1.0f),
        Point(1.0f, 1.0f, 1.0f),
        Point(-1.0f, 1.0f, 1.0f),
        Point(-1.0f, 1.0f, -1.0f),
        Point(-1.0f, -1.0f, -1.0f),
        Point(-1.0f, -1.0f, 1.0f),
        Point(1.0f, -1.0f, -1.0f),
        Point(1.0f, -1.0f, -1.0f),
        Point(-1.0f, -1.0f, 1.0f),
        Point(1.0f, -1.0f, 1.0f)
    };

    GLuint vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}
