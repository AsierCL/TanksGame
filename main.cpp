#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <vector>

#include "./include/Engine/Camera.h"
#include "./include/Engine/Shaders.h"
#include "./include/Engine/Objects/Tank.h"
#include "./include/Engine/Objects/Bullet.h"
#include "./include/Engine/Objects/Wall.h"
#include "./include/Utils/Vertices.h"
#include "./include/Utils/esfera.h"
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

//////////////// VAO //////////////////
unsigned int gVAO_Ejes = 0;
unsigned int gVAO_Cuadrado = 0;
unsigned int gVAO_Cubo = 0;
unsigned int gVAO_Esfera = 0;
unsigned int gVAO_Arbol = 0;

// Texturas
int hierba;
int arbolText;

// Objetos
objeto suelo = {0, 0, 0, 0, 0, 0, 100, 1, 100, {.282, .639, .329},36, gVAO_Cuadrado, 0};
objeto arbol1 = {10.0f, 0.5f, 10.0f, 0, 0, 0, 3.0f, 3.0f, 3.0f, {0, 0, 0}, 6, gVAO_Arbol, 0};
objeto arbol2 = {2.0f, 0.5f, 12.0f, 0, 0, 0, 3.0f, 3.0f, 3.0f, {0, 0, 0}, 6, gVAO_Arbol, 0};
objeto arbol3 = {-12.0f, 0.5f, 1.0f, 0, 0, 0, 3.0f, 3.0f, 3.0f, {0, 0, 0}, 6, gVAO_Arbol, 0};
objeto arbol4 = {-21.0f, 0.5f, 20.0f, 0, 0, 0, 3.0f, 3.0f, 3.0f, {0, 0, 0}, 6, gVAO_Arbol, 0};

void inicializarVAOs() {
    suelo.VAO = gVAO_Cuadrado;
    arbol1.VAO = gVAO_Arbol;
    arbol2.VAO = gVAO_Arbol;
    arbol3.VAO = gVAO_Arbol;
    arbol4.VAO = gVAO_Arbol;
}

void cuadradoXZ(){
    glGenVertexArrays(1, &gVAO_Cuadrado);
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindVertexArray(gVAO_Cuadrado);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_suelo), vertices_suelo, GL_STATIC_DRAW);
    // Posicion
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // Normales
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    // Texturas
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)(9*sizeof(float)));
    glEnableVertexAttribArray(3);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void dibujaCubo() {
    glGenVertexArrays(1, &gVAO_Cubo);
    unsigned int VBO, EBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(gVAO_Cubo);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_cubo), vertices_cubo, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_cubo), indices_cubo, GL_STATIC_DRAW);
    // Posicion
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // *Normal (texturas)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void dibujaEsfera(){
    glGenVertexArrays(1, &gVAO_Esfera);
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindVertexArray(gVAO_Esfera);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_esfera), vertices_esfera, GL_STATIC_DRAW);
    
    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    // *Normal (texturas)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(2);
    // Posicion
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(5*sizeof(float)));
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void dibuajrArbol(){
    unsigned int VBO, EBO;

    glGenVertexArrays(1, &gVAO_Arbol);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(gVAO_Arbol);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_arbol), vertices_arbol, GL_STATIC_DRAW);
    // Posicion
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // Normales
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    // Texturas
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)(9*sizeof(float)));
    glEnableVertexAttribArray(3);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void dibujarObjeto(glm::mat4& stack, unsigned int transformLoc, unsigned int colorLoc, objeto obj, bool dibujarRueda) {
    glm::mat4 transform;
    if(obj.sx != 10){
        transform = glm::mat4(1.0f);
        transform = glm::translate(stack, glm::vec3(obj.px, obj.py, obj.pz));
    }else{ transform = stack; }
    
    transform = glm::scale(transform, glm::vec3(obj.sx, obj.sy, obj.sz));
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
    glUniform3fv(colorLoc, 1, glm::value_ptr(glm::vec3(obj.colores[0], obj.colores[1], obj.colores[2])));
    glBindVertexArray(obj.VAO);
    if(obj.num_vertices == 36) {
        glDrawElements(GL_TRIANGLES, obj.num_vertices, GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, 1080);
    }

    glBindVertexArray(0);
}

void dibujarSinRef(unsigned int transformLoc, unsigned int colorLoc, objeto obj, int textura) {
    // 1) Transformación base (traslación + rotación dinámica + escalado)
    glm::mat4 baseTransform = glm::mat4(1.0f);
    baseTransform = glm::translate(baseTransform, glm::vec3(obj.px, obj.py, obj.pz));
    baseTransform = glm::scale(baseTransform, glm::vec3(obj.sx, obj.sy, obj.sz));

    // Enviamos color y textura una sola vez
    glUniform3fv(colorLoc, 1, glm::value_ptr(glm::vec3(obj.colores[0], obj.colores[1], obj.colores[2])));
    glBindTexture(GL_TEXTURE_2D, textura);
    glBindVertexArray(obj.VAO);

    // Dibujado “normal”
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(baseTransform));
    glDrawArrays(GL_TRIANGLES, 0, obj.num_vertices);

    // Dibujado “rotado +90°” encima
    glm::mat4 plus90 = glm::rotate(baseTransform, 90.0f * GradosToRadianes, glm::vec3(0,1,0));
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(plus90));
    glDrawArrays(GL_TRIANGLES, 0, obj.num_vertices);

    // Limpieza
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

int myCargaTexturas (const char* nome) {
    GLuint textura;
    glGenTextures (1, &textura);
    glBindTexture(GL_TEXTURE_2D, textura); 
    
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) ;
   
    int width, height, nrChannels;
    unsigned char* data = stbi_load(nome, &width, &height, &nrChannels, 0);
    if (data){
        if (nrChannels == 3){ glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);}
        if( nrChannels == 4){ glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);}
    }else{
        printf("Formato de textura no soportado: %d canales", nrChannels);
    }
    stbi_image_free(data);
    stbi_set_flip_vertically_on_load(1);
    return (textura);
}

void openGlInit() {
    glClearDepth(1.0f); // Buffer de profundidad
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Color de fondo
    glEnable(GL_DEPTH_TEST); 
    glDisable(GL_CULL_FACE); // Ocultacion de caras
    glCullFace(GL_BACK); // Oculta las caras traseras (normal que no mira a la camara)
}

/* void Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shaderProgram);
    myCamara();
    // Las buscamos en el shader
    unsigned int transformLoc = glGetUniformLocation(shaderProgram, "model");
    unsigned int colorLoc = glGetUniformLocation(shaderProgram, "Color");

    //iluminacion();
    dibujarSinRef(transformLoc, colorLoc, arbol1, arbolText);
    dibujarSinRef(transformLoc, colorLoc, arbol2, arbolText);
    dibujarSinRef(transformLoc, colorLoc, arbol3, arbolText);
    dibujarSinRef(transformLoc, colorLoc, arbol4, arbolText);
    dibujarSinRef(transformLoc, colorLoc, suelo, hierba);

    glBindVertexArray(0);
}*/

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Grua con OpenGL 3.3       :)", NULL, NULL);
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
    dibujaCubo();
    dibujaEsfera();
    cuadradoXZ();
    dibuajrArbol();

    hierba = myCargaTexturas("./assets/textures/baseGrass.jpeg");
    arbolText = myCargaTexturas("./assets/textures/a.png");

    
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
        /* Display(); */
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

void processGameInput(GLFWwindow* window) {
    // Tank 1 controls: WASD + Q/E to rotate turret + Space to fire
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        player1.moveForward(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        player1.moveBackward(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        player1.rotateTurret(-90 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        player1.rotateTurret( 90 * deltaTime);
    static bool fireReleased1 = true;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && fireReleased1) {
        bullets.push_back(player1.shoot());
        fireReleased1 = false;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) fireReleased1 = true;

    // Tank 2 controls: IJKL + U/O + RightShift to fire
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        player2.moveForward(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        player2.moveBackward(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        player2.rotateTurret(-90 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        player2.rotateTurret( 90 * deltaTime);
    static bool fireReleased2 = true;
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS && fireReleased2) {
        bullets.push_back(player2.shoot());
        fireReleased2 = false;
    }
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_RELEASE) fireReleased2 = true;
}

void initScene() {
    // Load generic VAOs (cube, sphere, etc.) and textures here
    dibujaCubo();    // fills gVAO_Cubo
    dibujaEsfera();  // if needed

    // Position players
    player1.position = glm::vec3(-10.0f, 0.5f, 0.0f);
    player1.rotation = glm::vec3(0.0f);
    player2.position = glm::vec3(10.0f, 0.5f, 0.0f);
    player2.rotation = glm::vec3(180.0f, 1.0f, 0.0f);

    // Create a perimeter wall
    walls.emplace_back(glm::vec3(0.0f, 0.0f, -20.0f), 40.0f, 1.0f);
    walls.emplace_back(glm::vec3(0.0f, 0.0f,  20.0f), 40.0f, 1.0f);
    walls.emplace_back(glm::vec3(-20.0f, 0.0f, 0.0f), 1.0f, 40.0f);
    walls.emplace_back(glm::vec3( 20.0f, 0.0f, 0.0f), 1.0f, 40.0f);
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
    dibujarSinRef(transformLoc, colorLoc, suelo, hierba);
    // -----------------------------------------------------------

    // Luego el resto de tu renderizado:
    for (auto& w : walls)    w.draw(shaderProgram);
    player1.draw(shaderProgram);
    player2.draw(shaderProgram);
    for (auto b : bullets)  b->draw(shaderProgram);

    glBindVertexArray(0);
}
