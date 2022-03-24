#include "Particles.h"
#include <math.h>
#include <cstdlib>
#include <ctime>
float F_RAND(float LO,float HI){
    if(LO>HI) {
        float tmp = HI;
        HI=LO;
        LO=tmp;
    }
    srand (static_cast <unsigned> (time(0)));
    float out=LO + static_cast <float> (std::rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
    return out;
}
void Particles::setEmitterPosition(glm::vec3 emitterPos) {
    this->emitterPosition =emitterPos;
}

Particles::Particles(int mode) {
    emitterPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    emitterDimensions = glm::vec3(0.0f, 0.0f, 0.0f);
    color = glm::vec4(1.0f, 0.0f, 1.0f,1.0f);
    active = false;
    speed=50.0f;
    gravity = glm::vec3(0.0f, -10.0f, 0.0f);
}

void Particles::activate() {

    active = true;
    life = 1.0f;
    fade = 0.05f + F_RAND(0.0f,1.0f) * 0.4f;
    pos = calculatePosition();
}

void Particles::live(float tt) {
    pos += direction * (tt/speed);
    direction += gravity*(tt/speed);
    direction += externals*(tt/speed);
    life -= fade * tt;
    // printf("%f\n", life);
    if (life <= 0.0f) {
        activate();
    }
}

glm::vec3 Particles::calculatePosition() {
    glm::vec3 out = emitterPosition;

    if(mode==POINT)
        out=emitterPosition;
    if(mode==LINE)
        out=glm::vec3 (F_RAND(emitterPosition[0],emitterDimensions[0]),emitterPosition[1],emitterPosition[2]);
    if(mode==SQUARE)
        out=glm::vec3 (F_RAND(emitterPosition[0],emitterDimensions[0]),emitterPosition[1],F_RAND(emitterPosition[2],emitterDimensions[2]));
    if(mode==CUBE)
        out=glm::vec3 (F_RAND(emitterPosition[0],emitterDimensions[0]),F_RAND(emitterPosition[1],emitterDimensions[1]),
                       F_RAND(emitterPosition[2],emitterDimensions[2]));
    return out;
}

Particles::~Particles() {

}
