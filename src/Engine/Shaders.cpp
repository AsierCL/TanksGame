#include "../../include/Engine/Shaders.h"
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

/* void iluminacion() {
    unsigned int isNightModeLoc = glGetUniformLocation(shaderProgram, "isNightMode");
    glUniform1i(isNightModeLoc, isNightMode);

    if (isNightMode) {
        float radianes = glm::radians(base.angulo_trans); // Convertir el ángulo de la base a radianes
        float offset = 0.0f;
        // Configuración de la primera luz
        unsigned int light1ColorLoc = glGetUniformLocation(shaderProgram, "light1Color");
        glUniform3f(light1ColorLoc, 1.0f, 1.0f, 1.0f);  // Luz cálida
        
        unsigned int light1PosLoc = glGetUniformLocation(shaderProgram, "light1Pos");

        offset = 1.0f;
        glUniform3f(light1PosLoc,
            base.px + sin(radianes) - offset * cos(radianes),
            base.py + 0.75f,
            base.pz + cos(radianes) + offset * sin(radianes));
        unsigned int light1DirLoc = glGetUniformLocation(shaderProgram, "light1Dir");
        glUniform3f(light1DirLoc, sin(base.angulo_trans * GradosToRadianes), 0, cos(base.angulo_trans * GradosToRadianes));

        // Configuración de la segunda luz
        unsigned int light2ColorLoc = glGetUniformLocation(shaderProgram, "light2Color");
        glUniform3f(light2ColorLoc, 1.f, 0.8f, 1.0f);  // Luz fría
        offset = -1.0f;
        unsigned int light2PosLoc = glGetUniformLocation(shaderProgram, "light2Pos");
        glUniform3f(light2PosLoc,
            base.px + sin(radianes) - offset * cos(radianes),
            base.py + 0.75f,
            base.pz + cos(radianes) + offset * sin(radianes));
        
        unsigned int light2DirLoc = glGetUniformLocation(shaderProgram, "light2Dir");
        glUniform3f(light2DirLoc, sin(base.angulo_trans * GradosToRadianes), 0, cos(base.angulo_trans * GradosToRadianes));

        // Configuración común
        unsigned int viewPosLoc = glGetUniformLocation(shaderProgram, "viewPos");
        //glUniform3f(viewPosLoc, cameraPos.x, cameraPos.y, cameraPos.z);
        glUniform3f(viewPosLoc, base.px, base.py, base.pz);
    }
} */