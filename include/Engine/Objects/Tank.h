#ifndef TANK_H
#define TANK_H

#include "GameObject.h"

class Bullet;

class Tank : public GameObject {
public:
    float speed;
    int health;
    int score;
    float turretOffset;
    glm::vec3 turretDirection;

    Tank();
    ~Tank();

    void update(float dt) override;
    void draw(unsigned int shaderProgram) override;
    void draw(unsigned int shaderProgram, unsigned int textureID);

    glm::vec3 getForward() const;
    glm::vec3 getTurretDirection() const;
    void moveForward(float dt);
    void moveBackward(float dt);
    void rotateLeft(float angle);
    void rotateRight(float angle);
    void rotateTurret(float angle);
    Bullet* shoot();
    void onHit();
};

#endif // TANK_H