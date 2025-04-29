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
    int moveChannel = -1;    // canal SDL_mixer donde suena el “move”
    int turretChannel = -1;    // canal SDL_mixer donde suena el “move”
    glm::vec3 turretDirection;

    Tank();
    ~Tank();

    void startMoveSound();
    void stopMoveSound();
    void startTurretSound();
    void stopTurretSound();
    void update(float dt) override;
    void draw(unsigned int shaderProgram) override;
    void draw(unsigned int shaderProgram, unsigned int textureID);

    glm::vec3 getForward() const;
    glm::vec3 getTurretDirection() const;
    void moveForward(float dt);
    void moveBackward(float dt);
    void rotateLeft(float angle);
    void rotateRight(float angle);// Sound effects
    void rotateTurret(float angle);
    Bullet* shoot();
    void onHit();

    unsigned int tankTextureID = 0;
    unsigned int turretTextureID = 0;
    unsigned int bulletTextureID = 0;
};

#endif // TANK_H