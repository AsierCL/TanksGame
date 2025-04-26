#include "./Camera.h"

// CAMERA POSITION
glm::vec3 cameraPos = glm::vec3(200.0f, 200.0f, 200.0f); // Posición inicial de la cámara
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); // Punto al que mira la cámara
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); // Dirección "arriba" del mundo

float cameraSpeed = 0.1f; // Velocidad de movimiento de la cámara
float VARIABLETEMPORAL = 45.0f; // Variable temporal para la cámara

CameraMode cameraMode = EXTERIOR; // Modo de cámara actual

void updateCameraMode() {
    cameraPos = glm::vec3(25.0f, 25.0f, 25.0f);
    cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
}

// Configuracion de la camara
void  myCamara() {
    // Matriz de proyeccion (perspectiva)
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 1.0f, 100.0f);
    unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glm::mat4 view = glm::lookAt(cameraPos, cameraTarget, cameraUp);

    unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
}