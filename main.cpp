#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <random>

#include "./include/Engine/Camera.h"
#include "./include/Engine/Shaders.h"
#include "./include/Engine/AudioManager.h"
#include "./include/Engine/AudioInit.h"
#include "./include/Engine/Draw.h"
#include "./include/Engine/Objects/Bullet.h"
#include "./include/Engine/Objects/Skybox.h"
#include "./include/Engine/Objects/Tank.h"
#include "./include/Engine/Objects/Wall.h"

// Transform helpers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Globals
extern GLuint shaderProgram;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Scene objects
Tank player1, player2;
std::vector<Bullet*> bullets;
std::vector<Wall> walls;

// Textures
extern int sandText, arbolText, tankText, wallText, turretText, bulletText;

// Prototypes
double getTime() { return glfwGetTime(); }
void initScene();
void processGameInput(GLFWwindow* window);
void updateScene();
void renderScene();
extern GLuint setShaders(const char *nVertx, const char *nFrag);

Skybox skybox;


void openGlInit() {
    glClearDepth(1.0f); // Buffer de profundidad
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Color de fondo
    glEnable(GL_DEPTH_TEST); 
    glDisable(GL_CULL_FACE); // Ocultacion de caras
    glCullFace(GL_BACK); // Oculta las caras traseras (normal que no mira a la camara)
}

void initMuros() {
    const int numMuros = 20; // Número de muros aleatorios
    const float distanciaMinimaJugadores = 10.0f;
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
    skybox.init();
    skybox.set_shader(shaderSkybox);
    std::vector<std::string> faces = {
        "./assets/textures/skybox/desertft.png",
        "./assets/textures/skybox/desertbk.png",
        "./assets/textures/skybox/desertup.png",
        "./assets/textures/skybox/desertdn.png",
        "./assets/textures/skybox/desertrt.png",
        "./assets/textures/skybox/desertlf.png"
    };
    skybox.add_cubemap_image(faces);

    // Position players
    player1.position = glm::vec3(-20.0f, 0.5f, 0.0f);
    player1.rotation = glm::vec3(0.0f);
    player2.position = glm::vec3(20.0f, 0.5f, 0.0f);
    player2.rotation = glm::vec3(180.0f, 1.0f, 0.0f);

    // Create a perimeter wall
    walls.emplace_back(glm::vec3(0.0f, 0.0f, 50.0f), 100.0f, 10.0f, 0.0f);
    walls.emplace_back(glm::vec3(0.0f, 0.0f, -50.0f), 100.0f, 10.0f, 0.0f);
    walls.emplace_back(glm::vec3(50.0f, 0.0f, 0.0f), 100.0f, 10.0f, 90.0f);
    walls.emplace_back(glm::vec3(-50.0f, 0.0f, 0.0f), 100.0f, 10.0f, 90.0f);
    initMuros();
    dibujarCubo();
    dibujarEsfera();
    dibujarSuelo();
    dibujarArbusto();
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
                w.onHit();
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
    
    //skybox.draw();

    glBindVertexArray(0);
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
    shaderSkybox = setShaders("./shaders/shaderSkyBox.vert", "./shaders/shaderSkyBox.frag");

    // Initialize scene: VAOs, textures, tanks, walls...
    initScene();
    initAudio();
    initTextures();


    player1.tankTextureID = tankText;
    player2.tankTextureID = tankText;
    player1.turretTextureID = turretText;
    player2.turretTextureID = turretText;
    player1.bulletTextureID = bulletText;
    player2.bulletTextureID = bulletText;
    for(auto &w : walls) {
        w.textureID = wallText;
    }

    // Asignamos los VAOs a los objetos
    inicializarVAOs();
    updateCamera();

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
