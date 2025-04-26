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
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

// CAMERA POSITION
extern glm::vec3 cameraPos;
extern glm::vec3 cameraTarget;
extern glm::vec3 cameraUp;

extern float cameraSpeed;
extern float VARIABLETEMPORAL;

// CAMERA MODES
enum CameraMode {
    FIRST_PERSON,
    THIRD_PERSON,
    EXTERIOR     
};

extern CameraMode cameraMode;


void updateCameraMode();
void myCamara();

#endif // CAMERA_H