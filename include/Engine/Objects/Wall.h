#ifndef WALL_H
#define WALL_H

#include "GameObject.h"

class Wall : public GameObject {
public:
    float width, height;

    Wall(const glm::vec3& pos, float w, float h, float angle = 0.0f);
    ~Wall();

    void update(float dt) override;
    void draw(unsigned int shaderProgram) override;
};

#endif // WALL_H