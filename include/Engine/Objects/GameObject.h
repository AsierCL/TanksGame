#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm/glm.hpp>

class GameObject {
public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    unsigned int textureID;  // ID de la textura (puede ser 0 si no hay textura)

    GameObject();
    virtual ~GameObject();

    virtual void update(float dt) = 0;
    virtual void draw(unsigned int shaderProgram) = 0;

    // Simple AABB collision
    virtual bool intersects(const GameObject& other) const;
};

#endif // GAMEOBJECT_H