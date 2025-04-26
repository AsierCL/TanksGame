#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float vertices_ejes[] = {
    // Posicion             // Color
     0.0f, 0.0f, 0.0f,      1,1,1, // O
     0.5f, 0.0f, 0.0f,      1,0,0, // x
     0.0f, 0.5f, 0.0f,      0,1,0, // y
     0.0f, 0.0f, -0.5f,     0,0,1, // z
};

unsigned int indices_ejes[] = {
    0, 1,  // X eje
    0, 2,  // Y eje
    0, 3   // Z eje
};

float vertices_cubo[] = {
    // Posicion             // Color      // *Sin usar (texturas)
    -0.5f, -0.5f, -0.5f,    1, 0, 0,      0, 0,  // 0
     0.5f, -0.5f, -0.5f,    1, 0, 0,      1, 0,  // 1
     0.5f,  0.5f, -0.5f,    1, 0, 0,      1, 1,  // 2
    -0.5f,  0.5f, -0.5f,    1, 0, 0,      0, 1,  // 3
    -0.5f, -0.5f,  0.5f,    1, 0, 0,      0, 0,  // 4
     0.5f, -0.5f,  0.5f,    1, 0, 0,      1, 0,  // 5
     0.5f,  0.5f,  0.5f,    1, 0, 0,      1, 1,  // 6
    -0.5f,  0.5f,  0.5f,    1, 0, 0,      0, 1   // 7
};

unsigned int indices_cubo[] = {
    // F
    4, 5, 6,
    4, 6, 7,
    // B
    0, 3, 2,
    0, 2, 1,
    // L
    0, 4, 7,
    0, 7, 3,
    // R
    1, 2, 6,
    1, 6, 5,
    // U
    3, 7, 6,
    3, 6, 2,
    // D
    0, 1, 5,
    0, 5, 4
};

float vertices_suelo[] = {
    // Posicion             // Texturas     // *Sin usar
    -0.5f, 0.0f, 0.5f,      0.0, 1.0, 0.0,  0.0f, 1.0f, 0.0f,   0,0,  
    0.5f, 0.0f,  0.5f,      0.0, 1.0, 0.0,  0.0f, 1.0f, 0.0f,   10,0,
    0.5f, 0.0f,  -0.5f,     0.0, 1.0, 0.0,  0.0f, 1.0f, 0.0f,   10,10,

    -0.5f, 0.0f, 0.5f,      0.0, 1.0, 0.0,  0.0f, 1.0f, 0.0f,   10,10,  
    -0.5f, 0.0f,  -0.5f,    0.0, 1.0, 0.0,  0.0f, 1.0f, 0.0f,   0,10,
    0.5f, 0.0f, -0.5f,      0.0, 1.0, 0.0,  0.0f, 1.0f, 0.0f,   0,0
};

float vertices_arbol[]{
    -0.5f, -0.5f, 0.0f,     1.0, 1.0, 1.0,   0.0f, 0.0f, 1.0,     0, 0,
    0.5f, -0.5f,  0.0f,     1.0, 1.0, 1.0,   0.0f, 0.0f, 1.0,     1, 0,
    0.5f, 0.5f, 0.0f,       1.0, 1.0, 1.0,   0.0f, 0.0f, 1.0,     1, 1,

    0.5f, 0.5f, 0.0f,       1.0, 1.0, 1.0,   0.0f, 0.0f, 1.0,     1, 1,
    -0.5f, 0.5f,  0.0f,     1.0, 1.0, 1.0,   0.0f, 0.0f, 1.0,     0, 1,
    -0.5f, -0.5f,  0.0f,    1.0, 1.0, 1.0,   0.0f, 0.0f, 1.0,     0, 0,
};

#endif // FUNCIONES_H