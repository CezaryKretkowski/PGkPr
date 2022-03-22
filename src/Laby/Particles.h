#ifndef PARTICLES_H
#define PARTICLES_H
#include <glm/glm.hpp>
#include "../RenderableObject/RenderableObject.h"
enum Mode{
    POINT= 0,
    LINE =1,
    SQUARE=2,
    CUBE=3
};
class Particles
{
private:
    /* data */
    bool active;
    float life, fade;
    float size;
    float speed;
    glm::vec3 color;
    glm::vec3 pos;
    glm::vec3 direction;
    glm::vec3 gravity;
    int mode;
    glm::vec3 emiterPos;
    glm::vec3 dimensions;
    RenderableObject obj;
    glm::vec3 calculatePosition();

public:
    Particles(int mode=0);
    ~Particles();
    void activate();
    void live(float tt);

    bool isActive() { return active; }
    float getLive() { return life; }
    float getFade() { return fade; }
    float getSize() { return size; }
    void setSpeed(float fs){speed=fs;}
    void setActive(bool active) { this->active = active; }

    RenderableObject *getObj() { return &obj; }
    glm::vec3 getColor() { return color; }
    glm::vec3 getPos() { return pos; }
    glm::vec3 getDirection() { return direction; }
    glm::vec3 getGravity() { return gravity; }
    void setGravity(glm::vec3 gravity){this->gravity=gravity;}
    void setDimension(glm::vec3 dimension){this->dimensions=dimension;}
    void setDirection(glm::vec3 dimension){this->direction=dimension;}
    void setEmiterPos(glm::vec3 emiterPos);
    void setMode(int mode){this->mode=mode;}

    float F_RAND();
    float F_RAND(float end);
};

#endif;
