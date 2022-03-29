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
    //srand (static_cast <unsigned> (time(0)));
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
    externals=glm::vec3(0.0f, 0.0f, 0.0f);
    gravity = glm::vec3(0.0f, -10.0f, 0.0f);
}

void Particles::activate() {

    active = true;
    life = 1.0f;
    if(strategy!=NULL)
        direction =strategy->calculateDirection();
    else
        direction=gravity;
    fade = 0.0005f + F_RAND(0.0f,1.0f) * 0.4f;
    pos = calculatePosition();
}

void Particles::live(float tt) {
    pos += direction * (tt/speed);
    direction += gravity*(tt/speed);
    direction += externals*(tt/speed);
    life -= fade * tt;
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
    delete this->strategy;
}
void Particles::drawParticles(GLuint CameraRight_worldspace_ID,GLuint CameraUp_worldspace_ID,GLuint  ViewProjMatrixID ) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    // Set our "myTextureSampler" sampler to user Texture Unit 0
    glUniform1i(textureID, 0);
    glm::mat4 ViewProjectionMatrix = projectionMatrix * viewMatrix;
    // Same as the billboards tutorial
    glUniform3f(CameraRight_worldspace_ID, viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]);
    glUniform3f(CameraUp_worldspace_ID   , viewMatrix[0][1], viewMatrix[1][1], viewMatrix[2][1]);

    glUniformMatrix4fv(ViewProjMatrixID, 1, GL_FALSE, &ViewProjectionMatrix[0][0]);
}
