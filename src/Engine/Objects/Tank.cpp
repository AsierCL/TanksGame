#include "../../../include/Engine/Objects/Tank.h"
#include "../../../include/Engine/Objects/Bullet.h"
#include "../../../include/Engine/Objects/Object.h"      // for VAO handles
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <vector>

extern unsigned int gVAO_Cubo;

Tank::Tank() : speed(5.0f), health(3), score(0) {
    scale = glm::vec3(2.0f, 1.0f, 3.0f);
    turretDirection = glm::vec3(0,0,1);
}

Tank::~Tank() {}

void Tank::update(float dt) {
    // Movement and turret smoothing could go here
}

void Tank::draw(unsigned int shaderProgram) {
    unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
    unsigned int colorLoc = glGetUniformLocation(shaderProgram, "Color");

    // 1) Chassis
    glm::mat4 chassisM = glm::mat4(1.0f);
    chassisM = glm::translate(chassisM, position);
    chassisM = glm::rotate(chassisM, glm::radians(rotation.y), glm::vec3(0,1,0));
    chassisM = glm::scale(chassisM, scale);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(chassisM));
    glUniform3f(colorLoc, 0.1f, 0.5f, 0.1f);
    glBindVertexArray(gVAO_Cubo);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // 2) Turret: build from scratch to avoid compounded scaling
    glm::mat4 turretM = glm::mat4(1.0f);
    turretM = glm::translate(turretM, position);
    turretM = glm::rotate(turretM, glm::radians(rotation.y), glm::vec3(0,1,0));
    // Move up by half chassis height
    turretM = glm::translate(turretM, glm::vec3(0.0f, scale.y * 0.5f, 0.0f));
    // Rotate turret according to direction
    float angle = glm::atan(turretDirection.x, turretDirection.z);
    turretM = glm::rotate(turretM, angle, glm::vec3(0,1,0));
    // Scale turret relative to chassis
    glm::vec3 tScale = glm::vec3(scale.x * 0.6f, scale.y * 0.4f, scale.z * 0.6f);
    turretM = glm::scale(turretM, tScale);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(turretM));
    glUniform3f(colorLoc, 0.51f, 0.43f, 0.31f);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // 3) Barrel: base on turretM before scaling to get correct offset
    glm::mat4 barrelM = glm::mat4(1.0f);
    barrelM = glm::translate(barrelM, position);
    barrelM = glm::rotate(barrelM, glm::radians(rotation.y), glm::vec3(0,1,0));
    barrelM = glm::translate(barrelM, glm::vec3(0.0f, scale.y * 0.5f, 0.0f));
    barrelM = glm::rotate(barrelM, angle, glm::vec3(0,1,0));
    // Move forward from turret center
    barrelM = glm::translate(barrelM, glm::vec3(0.0f, 0.0f, scale.z * 0.8f));
    // Scale barrel
    barrelM = glm::scale(barrelM, glm::vec3(0.1f, 0.1f, scale.z * 0.5f));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(barrelM));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void Tank::moveForward(float dt)  { position += turretDirection * speed * dt; }
void Tank::moveBackward(float dt) { position -= turretDirection * speed * dt; }
void Tank::rotateTurret(float angle) {
    glm::mat4 R = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0,1,0));
    turretDirection = glm::vec3(R * glm::vec4(turretDirection, 0.0f));
}

Bullet* Tank::shoot() {
    return new Bullet(this, position + turretDirection * (scale.z + 0.5f), turretDirection);
}

void Tank::onHit() {
    health--;
}