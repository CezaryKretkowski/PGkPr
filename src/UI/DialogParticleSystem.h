#ifndef DIALOGPARTICLESYSTEM_H
#define DIALOGPARTICLESYSTEM_H
#include "UI.h"
class DialogParticleSystem
{
private:
    bool v;
    std::string na = "Point";
    bool drop;
    bool cloude;

public:
    void setUpContent(Engine::Frame *super);
    void renderRain(Engine::Frame *super);
    void renderFog(Engine::Frame *super);
    void renderSmoke(Engine::Frame *super);
    void renderContent(Engine::Frame *super);
};

#endif;