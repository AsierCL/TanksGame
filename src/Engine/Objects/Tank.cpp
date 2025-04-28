#include "../../../include/Engine/Objects/Tank.h"
#include "../../../include/Engine/Objects/Wall.h"
#include "../../../include/Engine/Objects/Bullet.h"
#include "../../../include/Engine/Objects/Object.h"      // for VAO handles
#include "../../../include/Engine/AudioManager.h"      // for VAO handles
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <vector>

extern unsigned int gVAO_Cubo;
extern std::vector<Wall> walls;

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
    if (textureID != 0) {
        glBindTexture(GL_TEXTURE_2D, textureID);
    }
    glm::mat4 chassisM = glm::mat4(1.0f);
    chassisM = glm::translate(chassisM, position);
    chassisM = glm::rotate(chassisM, glm::radians(rotation.y), glm::vec3(0,1,0));
    chassisM = glm::scale(chassisM, scale);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(chassisM));
    glUniform3f(colorLoc, 0.3f, 0.3f, 0.3f);
    glBindVertexArray(gVAO_Cubo);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // Compute turret absolute yaw (base + offset)
    float totalYaw = rotation.y + turretOffset;
    float turretRad = glm::radians(totalYaw);

    // 2) Turret
    glm::mat4 turretM = glm::mat4(1.0f);
    turretM = glm::translate(turretM, position);
    turretM = glm::rotate(turretM, glm::radians(rotation.y), glm::vec3(0,1,0));
    turretM = glm::translate(turretM, glm::vec3(0.0f, scale.y * 0.5f, 0.0f));
    turretM = glm::rotate(turretM, turretRad - glm::radians(rotation.y), glm::vec3(0,1,0));
    glm::vec3 tScale = glm::vec3(scale.x * 0.6f, scale.y * 0.4f, scale.z * 0.6f);
    turretM = glm::scale(turretM, tScale);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(turretM));
    glUniform3f(colorLoc, 0.5f, 0.9f, 0.3f);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // 3) Barrel
    glm::mat4 barrelM = glm::mat4(1.0f);
    barrelM = glm::translate(barrelM, position);
    barrelM = glm::rotate(barrelM, glm::radians(rotation.y), glm::vec3(0,1,0));
    barrelM = glm::translate(barrelM, glm::vec3(0.0f, scale.y * 0.5f, 0.0f));
    barrelM = glm::rotate(barrelM, turretRad - glm::radians(rotation.y), glm::vec3(0,1,0));
    barrelM = glm::translate(barrelM, glm::vec3(0.0f, 0.0f, scale.z * 0.4f));
    barrelM = glm::scale(barrelM, glm::vec3(0.1f, 0.1f, scale.z * 0.5f));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(barrelM));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

// En Tank.h, añade dentro de la clase:
float turretOffset = 0.0f;  // ángulo relativo de la torreta respecto a la base

// Función auxiliar para obtener el vector “adelante” de la base
glm::vec3 Tank::getForward() const {
    float yawRad = glm::radians(rotation.y);
    return glm::normalize(glm::vec3(
        glm::sin(yawRad),
        0.0f,
        glm::cos(yawRad)
    ));
}

// Función auxiliar para obtener la dirección absoluta de la torreta
glm::vec3 Tank::getTurretDirection() const {
    float totalYaw = rotation.y + turretOffset;
    float yawRad   = glm::radians(totalYaw);
    return glm::normalize(glm::vec3(
        glm::sin(yawRad),
        0.0f,
        glm::cos(yawRad)
    ));
}

// Avanzar según la base
void Tank::moveForward(float dt) {
    glm::vec3 oldPos = position;
    position += getForward() * speed * dt;
    for (auto &w : walls) {
        if (this->intersects(w)) {
            position = oldPos;
            break;
        }
    }
}

// Retroceder según la base
void Tank::moveBackward(float dt) {
    glm::vec3 oldPos = position;
    position -= getForward() * speed * dt;
    for (auto &w : walls) {
        if (this->intersects(w)) {
            position = oldPos;
            break;
        }
    }
}

// Girar la base sin tocar el offset de la torreta
void Tank::rotateLeft(float angle) {
    rotation.y = fmod(rotation.y + angle + 360.0f, 360.0f);
    // la torreta no cambia su offset, sigue apuntando a rotation.y + turretOffset
}

// Girar la base hacia la derecha
void Tank::rotateRight(float angle) {
    rotation.y = fmod(rotation.y - angle + 360.0f, 360.0f);
}

// Girar la torreta de forma independiente
void Tank::rotateTurret(float angle) {
    turretOffset = fmod(turretOffset + angle, 360.0f);
}

// Disparo según la dirección absoluta de la torreta
Bullet* Tank::shoot() {
    AudioManager::get().playSound("shoot");
    glm::vec3 dir = getTurretDirection();
    return new Bullet(this, position + dir * (scale.z + 0.2f), dir);
}

void Tank::onHit() {
    AudioManager::get().playSound("hit");
    health--;
}


// Llama a esto cuando comience el movimiento
void Tank::startMoveSound() {
    if (moveChannel < 0 || !Mix_Playing(moveChannel)) {
        moveChannel = AudioManager::get().playLoop("tank");
    }
}

// Llama a esto cuando termine el movimiento
void Tank::stopMoveSound() {
    AudioManager::get().stopChannel(moveChannel);
    moveChannel = -1;
}

void Tank::startTurretSound() {
    if (moveChannel < 0 || !Mix_Playing(turretChannel)) {
        moveChannel = AudioManager::get().playLoop("turret");
    }
}

void Tank::stopTurretSound() {
    AudioManager::get().stopChannel(turretChannel);
    turretChannel = -1;
}