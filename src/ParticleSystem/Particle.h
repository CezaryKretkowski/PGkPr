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
    float particleSize;
    float live;
    float fadeTime;
    bool active;
    glm::vec3 position;
    glm::vec3 direction;
    float speed;
    void init(GLuint shader)
    {
        initFromArrary(Vert, Normal, Uv);
        initBuffers();
        particleSize = 1.0;
        fadeTime = 10.0f;
        loadTexture(shader, "../../resources/ParticleCloudWhite.png", "text");
        position = glm::vec3(0.0f, 0.0f, 0.0f);
        direction = glm::vec3(0.0f, 0.0f, 0.0f);
        speed = 1.0f;
        live = 1.0f;
    }
    bool liveP(float deltaTime)
    {

        if (live > 0.0)
        {

            position += direction * speed;
            live -= deltaTime / fadeTime;
            printf("%f\n", live);
            return true;
        }
        else
            return false;
    }

    void draw(GLuint v, GLuint p, GLuint posID, GLuint size, GLuint alpha)
    {

        glUniform1i(textureID, 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(vao);

        glUniform1f(size, particleSize);
        glUniform1f(alpha, live);
        glUniformMatrix4fv(v, 1, GL_FALSE, &viewMatrix[0][0]);
        glUniformMatrix4fv(p, 1, GL_FALSE, &projectionMatrix[0][0]);
        glUniform3f(posID, position[0], position[1], position[2]);

        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    }

    // void live() {}
};
#endif;