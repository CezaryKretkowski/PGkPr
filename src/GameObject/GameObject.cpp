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
    lightColorID = glGetUniformLocation(core, "lightColor");
    ambientStrenghtID = glGetUniformLocation(core, "ambientStrength");
    lightPosID = glGetUniformLocation(core, "lightPos");
    lightSwich = glGetUniformLocation(core, "lightSwich");
    viewPos = glGetUniformLocation(core, "viewPos");
    specStr = glGetUniformLocation(core, "specluarStreinght");
    specArea = glGetUniformLocation(core, "specluarArea");
    translate = glm::vec3(0.0f, 0.0f, 0.0f);
    rotate = glm::vec3(1.0f, 1.0f, 1.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
    modelMatrix = glm::mat4(1.0);
    angle = 1.0f;
    isInPlacing = true;
}
void GameObject::draw()
{

    glBindVertexArray(vao);

    glUniform1i(textureID, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    // glUniform3f(lightColorID, lightColor.x, lightColor.y, lightColor.z);
    // glUniform1f(ambientStrenghtID, ambientStringht);

    modelMatrix = glm::translate(glm::mat4(1.0), translate);
    if (isInPlacing)
        followCursor();
    else
    {
        modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), rotate);
        modelMatrix = glm::scale(modelMatrix, scale);
    }

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
void GameObject::setLightProp(LightProps l)
{
    glUseProgram(core);
    glUniform1f(ambientStrenghtID, l.ambientStringht);
    glUniform3f(lightColorID, l.lightColor.x, l.lightColor.y, l.lightColor.z);
    glUniform3f(lightPosID, l.lightPos.x, l.lightPos.y, l.lightPos.z);
    if (l.lightSwich)
    {
        glUniform1i(lightSwich, GL_TRUE);
    }
    else
    {
        glUniform1i(lightSwich, GL_FALSE);
    }
    glUniform3f(viewPos, l.cameraPos[0], l.cameraPos[1], l.cameraPos[2]);
    glUniform1f(specStr, l.specStright);
    glUniform1i(specArea, l.specluarArea);
}