#include "../../../include/Engine/Objects/Wall.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Wall::Wall(const glm::vec3& pos, float w, float h) : width(w), height(h) {
    position = pos;
    scale = glm::vec3(width, height, 1.0f);
}

Wall::~Wall() {}

void Wall::update(float dt) {
    // static
}

void Wall::draw(unsigned int shaderProgram) {
    // draw textured quad
}