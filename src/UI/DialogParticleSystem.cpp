#include "DialogParticleSystem.h"

void DialogParticleSystem::setUpContent(Engine::Frame *super)
{
}
void DialogParticleSystem::renderContent(Engine::Frame *super)
{
    if (ImGui::Checkbox("Particle System On", &v))
    {
        super->op.swich = v;
    }

    renderRain(super);
}

void DialogParticleSystem::renderRain(Engine::Frame *super)
{
    int maxpart = super->op.maxParticles;
    if (ImGui::SliderInt("MaxParticle", &maxpart, 100, 1000))
    {
        super->op.maxParticles = maxpart;
    }
    float fadT[] = {super->op.fadeTime[0], super->op.fadeTime[1]};
    if (ImGui::SliderFloat2("Fade Time", fadT, 1.0f, 10.f))
    {
        super->op.fadeTime = glm::vec2(fadT[0], fadT[1]);
    }
    float gravity[] = {super->op.garvity[0], super->op.garvity[1], super->op.garvity[2]};
    if (ImGui::InputFloat3("Gravity", gravity))
    {
        super->op.garvity = glm::vec3(gravity[0], gravity[1], gravity[2]);
    }

    float shape[] = {super->op.shapePos[0], super->op.shapePos[1], super->op.shapePos[2]};
    if (ImGui::InputFloat3("shape", shape))
    {
        super->op.shapePos = glm::vec3(shape[0], shape[1], shape[2]);
    }
    float emiterpos[] = {super->op.emiterPos[0], super->op.emiterPos[1], super->op.emiterPos[2]};
    if (ImGui::InputFloat3("EmiterPos", emiterpos))
    {
        super->op.emiterPos = glm::vec3(emiterpos[0], emiterpos[1], emiterpos[2]);
    }
    std::string name[] = {"Point", "Line", "Squere", "Cube"};

    int index;

    if (ImGui::BeginCombo("ShapePos", na.c_str()))
    {
        bool seletable;
        for (int i = 0; i < 4; i++)
        {
            if (ImGui::Selectable(name[i].c_str(), &seletable))
            {
                na = name[i];
                super->op.mode = i;
                printf("%d\n", super->op.mode);
            }
        }
        ImGui::EndCombo();
    }

    if (ImGui::Checkbox("Drop", &drop))
    {
        super->op.texture = 1;
    }
    ImGui::SameLine();
    if (ImGui::Checkbox("Cloud", &cloude))
    {
        super->op.texture = 0;
    }

    if (ImGui::Button("save"))
    {
        super->op.reset = true;
    }
}
