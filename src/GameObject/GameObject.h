#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "../RenderableObject/RenderableObject.h"
class GameObject : public RenderableObject
{
private:
    std::string path;

    GLuint core;
    GLuint M;
    GLuint V;
    GLuint P;
    glm::vec2 mousePos;
    glm::vec2 windowSize;
    std::string name;

public:
    bool isInPlacing;
    glm::vec3 translate;
    glm::vec3 scale;
    glm::vec3 rotate;
    float angle = 0;

    GameObject(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals,
               std::vector<glm::vec2> uvs);
    ~GameObject();
    void draw();
    void GameObject::draw(GLuint MatrixID, GLuint ViewMatrixID, GLuint ModelMatrixID);
    void GameObject::followCursor();
    void GameObject::setMousePos(glm::vec2 mousePos) { this->mousePos = mousePos; }
    void GameObject::setWindoSize(glm::vec2 widowSize) { this->windowSize = widowSize; }
    void GameObject::setName(std::string name) { this->name = name; }
};

#endif