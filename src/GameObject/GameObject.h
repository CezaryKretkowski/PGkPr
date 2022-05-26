#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "../RenderableObject/RenderableObject.h"
class GameObject : public RenderableObject
{
private:
    std::string path;
    bool isInPlacing;
    GLuint core;
    GLuint M;
    GLuint V;
    GLuint P;

public:
    glm::vec3 translate;
    glm::vec3 scale;
    glm::vec3 rotate;
    float angle = 0;

    GameObject(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals,
               std::vector<glm::vec2> uvs);
    ~GameObject();
    void draw();
};

#endif