#include "../../../include/Engine/Objects/GameObject.h"

GameObject::GameObject()
    : position(0.0f), rotation(0.0f), scale(1.0f), textureID(0) {}

GameObject::~GameObject() {}
bool GameObject::intersects(const GameObject& other) const {
    auto getHalfExtents = [](const GameObject& obj) {
        float angleY = glm::round(obj.rotation.y); // Asumimos rotación solo en Y

        float halfWidth, halfDepth;

        if (static_cast<int>(angleY) % 180 == 0) {
            // Sin rotación o 180°
            halfWidth = obj.scale.x * 0.5f;
            halfDepth = obj.scale.z * 0.5f;
        } else {
            // Rotado 90° o 270°: intercambiamos ancho y largo
            halfWidth = obj.scale.z * 0.5f;
            halfDepth = obj.scale.x * 0.5f;
        }

        glm::vec3 min = obj.position - glm::vec3(halfWidth, obj.scale.y * 0.5f, halfDepth);
        glm::vec3 max = obj.position + glm::vec3(halfWidth, obj.scale.y * 0.5f, halfDepth);
        return std::make_pair(min, max);
    };

    auto [aMin, aMax] = getHalfExtents(*this);
    auto [bMin, bMax] = getHalfExtents(other);

    return (aMin.x <= bMax.x && aMax.x >= bMin.x) &&
           (aMin.y <= bMax.y && aMax.y >= bMin.y) &&
           (aMin.z <= bMax.z && aMax.z >= bMin.z);
}
