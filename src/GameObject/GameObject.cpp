#include "GameObject.h"
#include "../shader.hpp"

GameObject::GameObject(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals,
                       std::vector<glm::vec2> uvs)
{
    core = LoadShaders("../../shaders/GameObjectVert.glsl", "../../shaders/GameObjectFrag.glsl");
    loadTexture(core, "../../resources/blank.png", "SamplerTexture");
    this->name = "BlankGameObject";
    initFromArrary(vertices, normals, uvs);
    initBuffers();
    M = glGetUniformLocation(core, "M");
    V = glGetUniformLocation(core, "V");
    P = glGetUniformLocation(core, "P");
    translate = glm::vec3(0.0f, 0.0f, 0.0f);
    rotate = glm::vec3(0.0f, 0.0f, 0.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
    modelMatrix = glm::mat4(1.0);
    angle = 0;
    isInPlacing = true;
}
void GameObject::draw()
{

    glUseProgram(core);
    glBindVertexArray(vao);

    glUniform1i(textureID, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    modelMatrix = glm::translate(glm::mat4(1.0), translate);
    if (isInPlacing)
        followCursor();
    modelMatrix = glm::scale(modelMatrix, scale);
    // modelMatrix = glm::rotate(glm::mat4(1), glm::radians(angle), rotate);

    glUniformMatrix4fv(M, 1, GL_FALSE, &modelMatrix[0][0]);
    glUniformMatrix4fv(V, 1, GL_FALSE, &viewMatrix[0][0]);
    glUniformMatrix4fv(P, 1, GL_FALSE, &projectionMatrix[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);

    // glUseProgram(0);
}
void GameObject::followCursor()
{
    float posX = (-((windowSize.x / 2.0f) - mousePos.x)) / (windowSize.x / 20.0f);
    float posY = -((windowSize.y / 2.0f) - mousePos.y) / (windowSize.y / 30.0f);
    glm::vec3 direction(posX, 0.0f, posY);

    translate = direction;
}
GameObject::~GameObject()
{
}
void GameObject::draw(GLuint MatrixID, GLuint ViewMatrixID, GLuint ModelMatrixID)
{
    glUniform1i(textureID, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
    glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &viewMatrix[0][0]);

    glBindVertexArray(vao);

    MVP = projectionMatrix * viewMatrix * modelMatrix;

    glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}