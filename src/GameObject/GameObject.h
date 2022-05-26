#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "../RenderableObject/RenderableObject.h"
class GameObject : public RenderableObject
{
private:
    std::string path;
    bool isInPlacing;

public:
    glm::vec3 translate;
    glm::vec3 scale;
    glm::vec3 rotate;

    GameObject(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals,
               std::vector<glm::vec2> uvs);
    ~GameObject();
};

#endif