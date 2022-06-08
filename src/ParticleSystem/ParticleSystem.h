#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H
#include "Particle.h"
#include "DirectionStrategy.h"
#include "Effects.h"
#include <algorithm>

enum Mode
{
    POINTEMITER = 0,
    LINE = 1,
    SQUARE = 2,
    CUBE = 3
};
struct Node
{
    int id;
    float distance;
};
bool operator<(const Node &v, const Node &w)
{
    return v.distance > w.distance;
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
    GLuint textures[2];
    std::vector<Node> particleList;
    DirectionStrategy *strategy[3];
    std::vector<Particle *> particles;

public:
    int maxParticle = 10;
    int strategyNumber = 1;
    bool mainSwich = true;

    glm::vec3 emiterPos;
    glm::vec3 emiterShape;
    glm::vec3 gravity;
    void generate(Engine::Frame *super, glm::mat4 pro, glm::mat4 view, Camera *c)
    {
        if (super->op.reset)
            restartParticle(super);
        else
        {
            for (int i = 0; i < particles.size(); i++)
            {
                float tt = super->deltaTime * 1000;
                if (particles[i]->liveP(tt, c->getPosytion()))
                {
                    particles[i]->direction += gravity;
                }
                else
                {
                    onActivate(i);
                }
            }
            glUseProgram(core);
            sortParticles();
            for (int i = 0; i < maxParticle; i++)
            {
                int index = particleList[i].id;
                particles[index]->setProjectionMatrix(pro);
                particles[index]->setViewMatrix(view);
                particles[index]->draw(v, p, posId, size, alpha);
            }
            glUseProgram(0);
        }
    }
    void setUp(Engine::Frame *super)
    {
        core = LoadShaders("../../shaders/ParticleVert.glsl", "../../shaders/ParticleFrag.glsl");
        p = glGetUniformLocation(core, "P");
        v = glGetUniformLocation(core, "V");
        posId = glGetUniformLocation(core, "ParticlePos");
        size = glGetUniformLocation(core, "size");
        alpha = glGetUniformLocation(core, "alpha");
        emiterPos = super->op.emiterPos;
        gravity = super->op.garvity;
        maxParticle = super->op.maxParticles;

        strategy[0] = new RainEffect();
        strategy[1] = new FogEffect();
        strategy[2] = new SmokeEffect();
        mode = POINTEMITER;
        restartParticle(super);
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
        particles[i]->direction = strategy[strategyNumber]->calculateDirection();
        particles[i]->position = pos;
        particles[i]->live = 1.0f;
    }
    ParticleSystem(/* args */);
    ~ParticleSystem();
    void sortParticles()
    {
        particleList.clear();
        for (int i = 0; i < maxParticle; i++)
        {
            Node p;

            p.id = i;
            p.distance = particles[i]->distance;
            particleList.push_back(p);
        }
        std::sort(particleList.begin(), particleList.end());
    }
    void restartParticle(Engine::Frame *super)
    {

        emiterPos = super->op.emiterPos;
        gravity = super->op.garvity;
        maxParticle = super->op.maxParticles;
        emiterShape = super->op.shapePos;
        mode = super->op.mode;

        for (int i = 0; i < maxParticle; i++)
        {
            Particle *p = new Particle();
            p->init(core);

            particles.push_back(p);
        }
        textures[0] = particles[0]->loadTexture("../../resources/ParticleCloudWhite.png");
        textures[1] = particles[0]->loadTexture("../../resources/drop.png");
        for (int i = 0; i < particles.size(); i++)
        {
            onActivate(i);
            particles[i]->fadeTime = F_RAND(super->op.fadeTime[0], super->op.fadeTime[1]);
            particles[i]->setTexture(textures[super->op.texture]);
        }

        super->op.reset = false;
    }
};

ParticleSystem::ParticleSystem(/* args */)
{
}

ParticleSystem::~ParticleSystem()
{
}

#endif;