#ifndef PROCESSINPUT_H
#define PROCESSINPUT_H

#include <vector>
#include "../../include/Engine/Objects/Tank.h"
#include "../../include/Engine/Objects/Bullet.h"
#include "../../include/Engine/Objects/Wall.h"

extern Tank player1, player2;
extern std::vector<Bullet*> bullets;
extern std::vector<Wall> walls;

void processGameInput(GLFWwindow* window);

#endif // PROCESSINPUT_H