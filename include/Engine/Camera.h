#ifndef CAMERA_H
#define CAMERA_H

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Engine/Shaders.h"
#include "../Engine/Objects/Object.h"

// SCREEN SIZE
const unsigned int SCR_WIDTH = 1900;
const unsigned int SCR_HEIGHT = 1000;

// CAMERA POSITION
extern glm::vec3 cameraPos;
extern glm::vec3 cameraTarget;
extern glm::vec3 cameraUp;

extern float cameraSpeed;
extern float VARIABLETEMPORAL;



void updateCamera();
void myCamara();
void updateCamaraPosition(GLFWwindow *window);

#endif // CAMERA_H