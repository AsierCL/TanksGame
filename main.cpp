#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <random>

#include "./include/Engine/Camera.h"
#include "./include/Engine/Shaders.h"
#include "./include/Engine/AudioManager.h"
#include "./include/Engine/Draw.h"
#include "./include/Engine/Objects/Tank.h"
#include "./include/Engine/Objects/Bullet.h"
#include "./include/Engine/Objects/Wall.h"
#include "./include/Utils/stb_image.h"

// Transform helpers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "./Utils/stb_image.h"

// Globals
extern GLuint shaderProgram;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Scene objects
Tank player1;
Tank player2;
std::vector<Bullet*> bullets;
std::vector<Wall> walls;

// Prototypes
double getTime() { return glfwGetTime(); }
void initScene();
void processGameInput(GLFWwindow* window);
void updateScene();
void renderScene();
extern GLuint setShaders(const char *nVertx, const char *nFrag);

// Texturas
int sandText;
int arbolText;
int tankText;
int wallText;
int turretText;


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

void openGlInit() {
    glClearDepth(1.0f); // Buffer de profundidad
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Color de fondo
    glEnable(GL_DEPTH_TEST); 
    glDisable(GL_CULL_FACE); // Ocultacion de caras
    glCullFace(GL_BACK); // Oculta las caras traseras (normal que no mira a la camara)
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

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Tank Game OPENGL, Asier Cabo", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // OpenGL states
    glEnable(GL_DEPTH_TEST);

    openGlInit();
    shaderProgram = setShaders("./shaders/shader.vert", "./shaders/shader.frag");

    // Initialize scene: VAOs, textures, tanks, walls...
    initScene();
    dibujarCubo();
    dibujarEsfera();
    dibujarSuelo();
    dibujarArbusto();

    if (!AudioManager::get().init()) {
        std::cerr << "No se pudo inicializar audio\n";
        return -1;
    }
    
    AudioManager::get().loadSound("hit",   "./assets/audio/hit.wav");
    AudioManager::get().loadSound("shoot", "./assets/audio/shoot.wav");
    AudioManager::get().loadSound("tank", "./assets/audio/tank-moving.wav");
    AudioManager::get().loadMusic("bgm", "./assets/audio/bgSound.wav");
    AudioManager::get().loadMusic("turret", "./assets/audio/turret.wav");

    AudioManager::get().playMusic("bgm", -1);  // bucle infinito
    // opcional: ajustar volumen [0..MIX_MAX_VOLUME]
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);

    sandText = myCargaTexturas("./assets/textures/sandTexture.png");
    arbolText = myCargaTexturas("./assets/textures/a.png");
    tankText = myCargaTexturas("./assets/textures/tankTexture.png");
    wallText = myCargaTexturas("./assets/textures/wallTexture.png");
    printf("Tank texture %d\n", tankText);

    player1.textureID = tankText;
    walls[0].textureID = wallText;

    // Asignamos los VAOs a los objetos
    inicializarVAOs();
    if(cameraMode == EXTERIOR){
        updateCameraMode();
    }

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = (float)getTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processGameInput(window);
        updateCamaraPosition(window);
        iluminacion();
        updateScene();
        renderScene();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup bullets
    for (auto b : bullets) delete b;
    bullets.clear();

    glfwTerminate();
    return 0;
}

void initMuros() {
    const int numMuros = 20; // Número de muros aleatorios
    const float distanciaMinimaJugadores = 20.0f;
    const float areaMin = -40.0f;
    const float areaMax = 40.0f;
    const float largoMin = 2.0f;
    const float largoMax = 12.0f;
    const float heightMin = 2.0f;
    const float heightMax = 6.0f;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> posDist(areaMin, areaMax);
    std::uniform_real_distribution<float> sizeDist(largoMin, largoMax);
    std::uniform_real_distribution<float> heightDist(heightMin, heightMax);
    std::uniform_int_distribution<int> rotDist(0, 1); // 0 = horizontal, 1 = vertical

    for (int i = 0; i < numMuros; ++i) {
        glm::vec3 pos;
        float largo;
        float alto = 4.0f;
        float rot;

        do {
            pos.x = posDist(gen);
            pos.z = posDist(gen);
        } while (glm::distance(pos, player1.position) < distanciaMinimaJugadores || 
                 glm::distance(pos, player2.position) < distanciaMinimaJugadores);

        largo = sizeDist(gen);
        rot = rotDist(gen) == 0 ? 0.0f : 90.0f;

        walls.emplace_back(glm::vec3(pos.x, 0.0f, pos.z), largo, alto, rot);
    }
}

void initScene() {
    // Position players
    player1.position = glm::vec3(-10.0f, 0.5f, 0.0f);
    player1.rotation = glm::vec3(0.0f);
    player2.position = glm::vec3(10.0f, 0.5f, 0.0f);
    player2.rotation = glm::vec3(180.0f, 1.0f, 0.0f);

    // Create a perimeter wall
    walls.emplace_back(glm::vec3(0.0f, 0.0f, 50.0f), 100.0f, 10.0f, 0.0f);
    walls.emplace_back(glm::vec3(0.0f, 0.0f, -50.0f), 100.0f, 10.0f, 0.0f);
    walls.emplace_back(glm::vec3(50.0f, 0.0f, 0.0f), 100.0f, 10.0f, 90.0f);
    walls.emplace_back(glm::vec3(-50.0f, 0.0f, 0.0f), 100.0f, 10.0f, 90.0f);
    initMuros();
}

void updateScene() {
    // Update bullets
    for (auto it = bullets.begin(); it != bullets.end();) {
        Bullet* b = *it;
        b->update(deltaTime);
        bool remove = !b->isAlive();
        // Hit on walls
        for (auto &w : walls) {
            if (!remove && b->intersects(w)) {
                remove = true;
                break;
            }
        }
        // Check hit on other tank
        Tank& target = (b->owner == &player1) ? player2 : player1;
        if (!remove && b->intersects(target)) {
            target.onHit();
            remove = true;
        }
        if (remove) {
            delete b;
            it = bullets.erase(it);
        } else ++it;
    }
}

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shaderProgram);
    myCamara();

    // --- aquí va lo de Display() para suelo y arbustos ---
    unsigned int transformLoc = glGetUniformLocation(shaderProgram, "model");
    unsigned int colorLoc     = glGetUniformLocation(shaderProgram, "Color");
    dibujarSinRef(transformLoc, colorLoc, arbol1, arbolText);
    dibujarSinRef(transformLoc, colorLoc, arbol2, arbolText);
    dibujarSinRef(transformLoc, colorLoc, arbol3, arbolText);
    dibujarSinRef(transformLoc, colorLoc, arbol4, arbolText);
    dibujarSinRef(transformLoc, colorLoc, suelo, sandText);
    // -----------------------------------------------------------

    // Luego el resto de tu renderizado:
    for (auto& w : walls)    w.draw(shaderProgram);
    player1.draw(shaderProgram);
    player2.draw(shaderProgram);
    for (auto b : bullets)  b->draw(shaderProgram);

    glBindVertexArray(0);
}
