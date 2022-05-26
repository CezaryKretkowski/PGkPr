#include "GameObject.h"
#include "../shader.hpp"

GameObject::GameObject(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals,
                       std::vector<glm::vec2> uvs)
{
    core = LoadShaders("../../shaders/GameObjectVert.glsl", "../../shaders/GameObjectFrag.glsl");
    initFromArrary(vertices, normals, uvs);
    M = glGetUniformLocation(core, "M");
    V = glGetUniformLocation(core, "V");
    P = glGetUniformLocation(core, "P");
    textureID = glGetUniformLocation(core, "SamplerTexture");
    translate = glm::vec3(0.0f, 0.0f, 0.0f);
    rotate = glm::vec3(0.0f, 0.0f, 0.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
    isInPlacing = true;
}
void GameObject::draw(GLuint MatrixID, GLuint ViewMatrixID, GLuint ModelMatrixID)
{
    modelMatrix = glm::translate(glm::mat4(1), translate);
    modelMatrix = glm::scale(glm::mat4(1), translate);
    modelMatrix = glm::rotate(glm::mat4(1), glm::radians(angle), translate);
    glUseProgram(core);
    glUseProgram(0);
}
GameObject::~GameObject()
{
}