#ifndef SHADERS_H
#define SHADERS_H

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Engine/Objects/Object.h"
#include "../Utils/Const.h"

// Variable global para controlar el modo noche
extern objeto base;
extern bool isNightMode;
extern GLuint shaderProgram;
extern GLuint shaderSkybox;

extern int sandText, arbolText, tankText, wallText, turretText, bulletText;

void toggleNightMode();
void iluminacion();
int myCargaTexturas(const char* nome);
void initTextures();

#endif // SHADERS.H