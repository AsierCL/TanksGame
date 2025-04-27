#include "../../../include/Engine/Objects/Wall.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <vector>

extern unsigned int gVAO_Cubo;

Wall::Wall(const glm::vec3& pos, float w, float h) : width(w), height(h) {
    position = pos;
    scale = glm::vec3(width, height, 1.0f);
}

Wall::~Wall() {}

void Wall::update(float dt) {
    // static
}

void Wall::draw(unsigned int shaderProgram) {
    // Obtener ubicaciones de los uniformes
    unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
    unsigned int colorLoc = glGetUniformLocation(shaderProgram, "Color");

    if (textureID != 0) {
        glBindTexture(GL_TEXTURE_2D, textureID);
    }

    // Construir matriz de modelo: traslación + escala
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    // Enviar matriz y color al shader
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniform3f(colorLoc, 0.6f, 0.6f, 0.6f);  // Gris claro para el muro

    // Dibujar muro como cubo escalado
    glBindVertexArray(gVAO_Cubo);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}