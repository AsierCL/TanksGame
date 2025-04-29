#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <vector>

// Transform helpers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../include/Engine/Draw.h"
#include "../../include/Utils/esfera.h"
#include "../../include/Utils/Vertices.h"
#include "../../include/Utils/Const.h"

//////////////// VAO //////////////////
unsigned int gVAO_Ejes = 0;
unsigned int gVAO_Cuadrado = 0;
unsigned int gVAO_Cubo = 0;
unsigned int gVAO_Esfera = 0;
unsigned int gVAO_Arbol = 0;

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

void dibujarSuelo() {
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

void dibujarCubo() {
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

void dibujarEsfera() {
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

void dibujarArbusto() {
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
