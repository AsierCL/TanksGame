#include "Bullet.h"
#include "Object.h"      // for VAO handles
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <vector>

extern unsigned int gVAO_Cubo;

Bullet::Bullet(Tank* shooter, const glm::vec3& pos, const glm::vec3& dir)
    : owner(shooter), velocity(dir * 20.0f), lifetime(3.0f) {
    position = pos;
    scale = glm::vec3(0.2f);
}

Bullet::~Bullet() {}

void Bullet::update(float dt) {
    position += velocity * dt;
    lifetime -= dt;
}

void Bullet::draw(unsigned int shaderProgram) {
    unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
    unsigned int colorLoc = glGetUniformLocation(shaderProgram, "Color");
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniform3f(colorLoc, 1.0f, 0.8f, 0.0f);
    glBindVertexArray(gVAO_Cubo);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

bool Bullet::isAlive() const { return lifetime > 0.0f; }
