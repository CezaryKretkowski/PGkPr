#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H
#include "Particle.h"

enum Mode
{
    POINTEMITER = 0,
    LINE = 1,
    SQUARE = 2,
    CUBE = 3
};
float F_RAND(float LO, float HI)
{
    if (LO > HI)
    {
        float tmp = HI;
        HI = LO;
        LO = tmp;
    }
    // srand (static_cast <unsigned> (time(0)));
    float out = LO + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (HI - LO)));
    return out;
}
class ParticleSystem
{
private:
    int mode;
    GLuint core;
    GLuint v;
    GLuint p;
    GLuint posId;
    GLuint size;
    GLuint alpha;
    std::vector<Particle *> particles;

public:
    int maxParticle = 1;
    bool mainSwich = true;

    glm::vec3 emiterPos;
    glm::vec3 emiterShape;
    glm::vec3 gravity;
    void generate(Engine::Frame *super, glm::mat4 pro, glm::mat4 view)
    {
        for (int i = 0; i < particles.size(); i++)
        {
            float tt = super->deltaTime * 1000;
            if (particles[i]->liveP(tt))
            {
                particles[i]->direction += gravity;
            }
            else
            {
                onActivate(i);
            }
        }
        glUseProgram(core);
        for (int i = 0; i < maxParticle; i++)
        {

            particles[i]->setProjectionMatrix(pro);
            particles[i]->setViewMatrix(view);
            particles[i]->draw(v, p, posId, size, alpha);
        }
        glUseProgram(0);
    }
    void setUp(Engine::Frame *super)
    {
        core = LoadShaders("../../shaders/ParticleVert.glsl", "../../shaders/ParticleFrag.glsl");
        p = glGetUniformLocation(core, "P");
        v = glGetUniformLocation(core, "V");
        posId = glGetUniformLocation(core, "ParticlePos");
        size = glGetUniformLocation(core, "size");
        alpha = glGetUniformLocation(core, "alpha");
        emiterPos = glm::vec3(0.0f, 0.0f, 0.0f);
        gravity = glm::vec3(0.0f, 0.0f, 0.0f);

        mode = POINTEMITER;
        for (int i = 0; i < maxParticle; i++)
        {
            Particle *p = new Particle();
            p->init(core);
            particles.push_back(p);
        }
        for (int i = 0; i < particles.size(); i++)
        {
            onActivate(i);
        }
    }
    void onActivate(int i)
    {

        glm::vec3 pos;
        switch (mode)
        {
        case POINTEMITER:
            pos = emiterPos;
            break;
        case LINE:
            pos = glm::vec3(F_RAND(emiterPos[0], emiterShape[0]), emiterPos[0], emiterPos[2]);
            break;
        case SQUARE:
            pos = glm::vec3(F_RAND(emiterPos[0], emiterShape[0]), emiterPos[0], F_RAND(emiterPos[2], emiterShape[2]));
        case CUBE:
            pos = glm::vec3(F_RAND(emiterPos[0], emiterShape[0]), F_RAND(emiterPos[1], emiterShape[1]), F_RAND(emiterPos[2], emiterShape[2]));
            break;
        }
        particles[i]->position = pos;
        particles[i]->live = 1.0f;
    }
    ParticleSystem(/* args */);
    ~ParticleSystem();
};

ParticleSystem::ParticleSystem(/* args */)
{
}

ParticleSystem::~ParticleSystem()
{
}

#endif;