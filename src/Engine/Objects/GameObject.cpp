#include "../../../include/Engine/Objects/GameObject.h"

GameObject::GameObject()
    : position(0.0f), rotation(0.0f), scale(1.0f), textureID(0) {}

GameObject::~GameObject() {}
bool GameObject::intersects(const GameObject& other) const {
    glm::vec3 aMin = position - scale * 0.5f;
    glm::vec3 aMax = position + scale * 0.5f;
    glm::vec3 bMin = other.position - other.scale * 0.5f;
    glm::vec3 bMax = other.position + other.scale * 0.5f;
    return (aMin.x <= bMax.x && aMax.x >= bMin.x) &&
           (aMin.y <= bMax.y && aMax.y >= bMin.y) &&
           (aMin.z <= bMax.z && aMax.z >= bMin.z);
}