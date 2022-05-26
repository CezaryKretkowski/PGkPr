#include "GameObject.h"
#include "../shader.hpp"

GameObject::GameObject(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals,
                       std::vector<glm::vec2> uvs)
{
    core = LoadShaders("../../shaders/GameObjectVert.glsl", "../../shaders/GameObjectFrag.glsl");
    loadTexture(core, "../../resources/blank.png", "SamplerTexture");
    initFromArrary(vertices, normals, uvs);
    M = glGetUniformLocation(core, "M");
    V = glGetUniformLocation(core, "V");
    P = glGetUniformLocation(core, "P");
    translate = glm::vec3(0.0f, 0.0f, 0.0f);
    rotate = glm::vec3(0.0f, 0.0f, 0.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
    isInPlacing = true;
}
void GameObject::draw()
{
    // modelMatrix = glm::translate(glm::mat4(1), translate);
    // modelMatrix = glm::scale(glm::mat4(1), scale);
    // modelMatrix = glm::rotate(glm::mat4(1), glm::radians(angle), rotate);
    glUseProgram(core);
    glBindVertexArray(vao);

    glUniformMatrix4fv(M, 1, GL_FALSE, &modelMatrix[0][0]);
    glUniformMatrix4fv(V, 1, GL_FALSE, &viewMatrix[0][0]);
    glUniformMatrix4fv(P, 1, GL_FALSE, &projectionMatrix[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glUseProgram(0);
}
GameObject::~GameObject()
{
}