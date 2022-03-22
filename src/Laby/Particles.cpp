#include "Particles.h"

void Particles::setEmiterPos(glm::vec3 emiterPos = glm::vec3(0.0f, 0.0f, 0.0f)) {
    this->emiterPos = emiterPos;
}

float Particles::F_RAND() {
    return static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
}
float Particles::F_RAND(float max) {
    return static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX/max);
}

Particles::Particles(int mode) {
    emiterPos = glm::vec3(0.0f, 0.0f, 0.0f);
    this->dimensions = glm::vec3(0.0f, 0.0f, 0.0f);
    color = glm::vec3(1.0f, F_RAND(), F_RAND());
    active = false;
    size = F_RAND() * 5.0f + 0.5f;
}

void Particles::activate() {

    active = true;
    life = 1.0f;
    fade = 0.05f + F_RAND() * 0.4f;

    pos = calculatePosition();
    float fi = 3.14f / 4.0f;
    float psi = F_RAND() * (3.14f / 2.0f);
    float rr = F_RAND() * 12.0f + 16.0f;
    direction = glm::vec3(rr * cos(fi) * cos(psi), rr * sin(fi), rr * cos(fi) * sin(psi));

    gravity = glm::vec3(0.0f, -10.0f, 0.0f);
}

void Particles::live(float tt) {
    pos += direction * (tt / speed);
    direction += gravity * (tt / offset);
    life -= fade * tt;
    // printf("%f\n", life);
    if (life < 0.05f) {
        activate();
    }
}

glm::vec3 Particles::calculatePosition() {
    glm::vec3 out = emiterPos;
    if(mode==POINT)
        out=emiterPos;
    if(mode==LINE)
        out=glm::vec3 (F_RAND(dimensions[0]),emiterPos[1],emiterPos[2]);
    if(mode==SQUARE)
        out=glm::vec3 (F_RAND(dimensions[0]),emiterPos[2],F_RAND(dimensions[1]));
    if(mode==CUBE)
        out=glm::vec3 (F_RAND(dimensions[0]),F_RAND(dimensions[1]),F_RAND(dimensions[2]));
    return out;
}

Particles::~Particles() {
}
