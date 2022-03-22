#ifndef PARTICLES_H
#define PARTICLES_H
#include <glm/glm.hpp>

class Particles
{
private:
    /* data */
    bool active;
    float life, fade;
    float size;
    glm::vec3 color;
    glm::vec3 pos;
    glm::vec3 direction;
    glm::vec3 gravity;

    glm::vec3 emiterPos;

public:
    Particles(/* args */);
    ~Particles();
    void activate();
    void live(float tt);

    bool isActive() { return active; }
    float getLive() { return life; }
    float getFade() { return fade; }
    float getSize() { return size; }
    void setActive(bool active) { this->active = active; }
    void zeroPos() { pos = glm::vec3(0.0f, 0.0f, 0.0f); }
    glm::vec3 getColor() { return color; }
    glm::vec3 getPos() { return pos; }
    glm::vec3 getDirection() { return direction; }
    glm::vec3 getGravity() { return gravity; }
    void setEmiterPos(glm::vec3 emiterPos);

    float F_RAND();
    float F_RAND(float end);
};

#endif;