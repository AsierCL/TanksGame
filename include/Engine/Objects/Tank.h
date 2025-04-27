#ifndef TANK_H
#define TANK_H

#include "GameObject.h"

class Bullet;

class Tank : public GameObject {
public:
    float speed;
    int health;
    int score;
    glm::vec3 turretDirection;

    Tank();
    ~Tank();

    void update(float dt) override;
    void draw(unsigned int shaderProgram) override;
    void draw(unsigned int shaderProgram, unsigned int textureID);

    void moveForward(float dt);
    void moveBackward(float dt);
    void rotateTurret(float angle);
    Bullet* shoot();
    void onHit();
};

#endif // TANK_H