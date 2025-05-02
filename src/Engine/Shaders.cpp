#include "../../include/Engine/Shaders.h"
#include "../../include/Engine/Camera.h"
#include "../../include/Engine/lecturaShader_0_9.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../../include/Utils/stb_image.h"

bool isNightMode = false;
extern objeto base;

GLuint shaderProgram = 0;
GLuint shaderSkybox = 0;
int sandText, arbolText, tankText, wallText, turretText, bulletText;

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

int myCargaTexturas(const char* nome) {
    GLuint textura;
    glGenTextures (1, &textura);
    glBindTexture(GL_TEXTURE_2D, textura); 
    
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) ;
   
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(1);
    unsigned char* data = stbi_load(nome, &width, &height, &nrChannels, 0);
    if (data){
        if (nrChannels == 3){ glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);}
        if( nrChannels == 4){ glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);}
    }else{
        printf("Formato de textura no soportado: %d canales", nrChannels);
    }
    stbi_image_free(data);
    return (textura);
}

void initTextures() {
    sandText = myCargaTexturas("./assets/textures/sandTexture.png");
    arbolText = myCargaTexturas("./assets/textures/a.png");
    tankText = myCargaTexturas("./assets/textures/tankTexture.png");
    wallText = myCargaTexturas("./assets/textures/wallTexture.png");
    turretText = myCargaTexturas("./assets/textures/turretTexture.png");
    bulletText = myCargaTexturas("./assets/textures/bulletTexture.png");
}