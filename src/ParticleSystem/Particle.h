#ifndef PARTICLE_H
#define PARTICLE_H
#include <vector>
#include <glm/glm.hpp>

std::vector<glm::vec3> Vert = {
    glm::vec3(-0.5f, 0.5f, 0.f),
    glm::vec3(0.5f, 0.5f, 0.f),
    glm::vec3(0.5f, -0.5f, 0.f),
    glm::vec3(-0.5f, 0.5f, 0.f),
    glm::vec3(0.5f, -0.5f, 0.f),
    glm::vec3(-0.5f, -0.5f, 0.f)};
std::vector<glm::vec3> Normal = {
    glm::vec3(0.0f, 0.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 1.0f)};
std::vector<glm::vec2> Uv = {
    glm::vec2(0.0f, 1.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(0.0f, 1.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(0.0f, 0.0f)};
class Particle : public RenderableObject
{
public:
    float size;
    float live;
    bool active;
    GLuint posID;
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 velocity;

    void draw(GLuint v, GLuint p)
    {
        glUniform1i(textureID, 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(vao);

        glUniformMatrix4fv(v, 1, GL_FALSE, &viewMatrix[0][0]);
        glUniformMatrix4fv(p, 1, GL_FALSE, &projectionMatrix[0][0]);
        glUniform3f(posID, position[0], position[1], position[2]);

        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    }
    // void live() {}
};
#endif;