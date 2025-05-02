#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <vector>

// Transform helpers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../include/Engine/ProcessInput.h"

// Globals
extern GLuint shaderProgram;
extern float deltaTime, lastFrame;


void processGameInput(GLFWwindow* window) {
    // Tank 1 controls: WASD + Q/E to rotate turret + X to fire
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        player1.moveForward(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        player1.moveBackward(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        player1.rotateTurret(-90 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        player1.rotateTurret( 90 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        player1.rotateLeft(90 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        player1.rotateRight(90 * deltaTime);

    // Sound effects //
    // Play sound if moving
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        if (player1.moveChannel == -1) player1.startMoveSound();
    } else {
        if (player1.moveChannel != -1) player1.stopMoveSound();
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        if (player1.turretChannel == -1) player1.startTurretSound();
    } else {
        if (player1.turretChannel != -1) player1.stopTurretSound();
    }

    static bool fireReleased1 = true;
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS && fireReleased1) {
        bullets.push_back(player1.shoot());
        fireReleased1 = false;
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_RELEASE) fireReleased1 = true;

    // Tank 2 controls: IJKL + U/O + M to fire
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        player2.moveForward(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        player2.moveBackward(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        player2.rotateLeft(90 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        player2.rotateRight( 90 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
        player2.rotateTurret(90 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        player2.rotateTurret(-90 * deltaTime);
    
    // Sound effects //
    // Play sound if moving
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        if (player2.moveChannel == -1) player2.startMoveSound();
    } else {
        if (player2.moveChannel != -1) player2.stopMoveSound();
    }

    static bool fireReleased2 = true;
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS && fireReleased2) {
        bullets.push_back(player2.shoot());
        fireReleased2 = false;
    }
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_RELEASE) fireReleased2 = true;

    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
        if (player2.turretChannel == -1) player2.startTurretSound();
    } else {
        if (player2.turretChannel != -1) player2.stopTurretSound();
    }
}
