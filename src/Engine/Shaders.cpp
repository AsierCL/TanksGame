#include "../../include/Engine/Shaders.h"
#include "../../include/Engine/Camera.h"
#include "../../include/Engine/lecturaShader_0_9.h"

bool isNightMode = false;
extern objeto base;

GLuint shaderProgram = 0;
GLuint shaderSkybox = 0;

// Función para alternar el modo noche
void toggleNightMode() {
    isNightMode = !isNightMode;
    std::cout << "Modo noche: " << (isNightMode ? "Activado" : "Desactivado") << std::endl;
}


void iluminacion() {
    // 1) Ambiente
    int ambColLoc = glGetUniformLocation(shaderProgram, "ambientColor");
    glUniform3f(ambColLoc, 0.2f, 0.2f, 0.2f); // luz azulada suave
    int ambStrLoc = glGetUniformLocation(shaderProgram, "ambientStrength");
    glUniform1f(ambStrLoc, 0.3f);

    // 2) Sol direccional (p. ej. desde arriba y atrás)
    glm::vec3 sunDir = glm::normalize(glm::vec3(-0.3f, -1.0f, -0.3f));
    int sunDirLoc = glGetUniformLocation(shaderProgram, "sunDirection");
    glUniform3fv(sunDirLoc, 1, glm::value_ptr(sunDir));
    int sunColLoc = glGetUniformLocation(shaderProgram, "sunColor");
    glUniform3f(sunColLoc, 1.0f, 1.0f, 0.9f); // algo cálido

    // 3) Posición de la cámara (para especular)
    int viewPosLoc = glGetUniformLocation(shaderProgram, "viewPos");
    glUniform3fv(viewPosLoc, 1, glm::value_ptr(cameraPos));

    // 4) Color del objeto o usar uniform “objectColor”
    // Lo puedes dejar en (1,1,1) y confiar en la textura.
    int objColLoc = glGetUniformLocation(shaderProgram, "objectColor");
    glUniform3f(objColLoc, 1.0f, 1.0f, 1.0f);
}