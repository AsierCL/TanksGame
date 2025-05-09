#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"

class Tank;

class Bullet : public GameObject {
public:
    glm::vec3 velocity;
    float lifetime;
    Tank* owner;

    Bullet(Tank* shooter, const glm::vec3& pos, const glm::vec3& dir, unsigned int textureID);
    ~Bullet();;

    void update(float dt) override;
    void draw(unsigned int shaderProgram) override;
    bool isAlive() const;
private:
    unsigned int textureID;
};

#endif // BULLET_H