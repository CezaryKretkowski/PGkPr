#ifndef EFFECTS_H
#define EFFECTS_H
#include "DirectionStrategy.h"
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
class SmokeEffect : public DirectionStrategy
{
public:
    ~SmokeEffect() {}
    glm::vec3 calculateDirection() override
    {

        float fi = 3.14f / 4;                         // 45 stopni w górę
        float psi = F_RAND(0.0f, 1.0f) * (3.14f * 2); // 0-360 stopni wokół osi Y
        float rr = F_RAND(0.0f, 1.0f);
        glm::vec3 direction(0.1f * cos(fi) * cos(psi), 1.0f, 0.1f * cos(fi) * sin(psi));
        // glm::vec3 direction(F_RAND(-0.1, 0.1), 1.0, F_RAND(-0.1, 0.1));
        return direction;
    }
};
class FogEffect : public DirectionStrategy
{
public:
    ~FogEffect() {}
    glm::vec3 calculateDirection() override
    {
        float fi = 3.14f / 4;                         // 45 stopni w górę
        float psi = F_RAND(0.0f, 1.0f) * (3.14f * 2); // 0-360 stopni wokół osi Y
        float rr = F_RAND(0.0f, 1.0f) * 12 + 16;
        glm::vec3 direction(rr * cos(fi) * cos(psi), 2.1f, rr * cos(fi) * sin(psi));
        return direction;
    }
};
class RainEffect : public DirectionStrategy
{
public:
    ~RainEffect() {}
    glm::vec3 calculateDirection() override
    {

        return glm::vec3(0.0f, 0.0f, 0.0f);
    }
};
#endif;