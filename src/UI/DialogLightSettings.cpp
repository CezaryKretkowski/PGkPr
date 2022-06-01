#include "DialogLightSettings.h"
DialogLightSettings::DialogLightSettings(/* args */)
{
    clearColor[0] = 1.0;
    clearColor[1] = 1.0;
    clearColor[2] = 1.0;
}

DialogLightSettings::~DialogLightSettings()
{
}
void DialogLightSettings::setUpContent(Engine::Frame *super)
{
    clearColor[0] = super->getClearColor()[0];
    clearColor[1] = super->getClearColor()[0];
    clearColor[2] = super->getClearColor()[0];
}
void DialogLightSettings::renderContent(Engine::Frame *super)
{
    if (ImGui::BeginTabBar("Light Settings"))
    {
        if (ImGui::BeginTabItem("Main Settings"))
        {
            renderMainSettingsTab(super);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Skybox"))
        {
            renderSkyboxTab(super);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Objects"))
        {
            renderObjectTab(super);
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
}
void DialogLightSettings::renderSkyboxTab(Engine::Frame *super)
{
    ambientSkybox = super->lightPropsSkybox.ambientStringht;
    lightColor[0] = super->lightPropsSkybox.lightColor[0];
    lightColor[1] = super->lightPropsSkybox.lightColor[1];
    lightColor[2] = super->lightPropsSkybox.lightColor[2];
    lightPos[0] = super->lightPropsSkybox.lightPos[0];
    lightPos[1] = super->lightPropsSkybox.lightPos[1];
    lightPos[2] = super->lightPropsSkybox.lightPos[2];
    if (ImGui::Checkbox("Light On", &lightSwichSkybox))
    {
        super->lightPropsSkybox.lightSwich = lightSwichSkybox;
    }
    if (ImGui::SliderFloat("Ambient", &ambientSkybox, 0.0, 1.0))
    {
        super->lightPropsSkybox.ambientStringht = ambientSkybox;
    }
    if (ImGui::SliderFloat3("lightColor", lightColor, 0.0, 1.0))
    {
        super->lightPropsSkybox.lightColor = glm::vec3(lightColor[0], lightColor[1], lightColor[2]);
    }
    if (ImGui::InputFloat3("Light position", lightPos))
    {
        super->lightPropsSkybox.lightPos = glm::vec3(lightPos[0], lightPos[1], lightPos[2]);
    }
}
void DialogLightSettings::renderObjectTab(Engine::Frame *super)
{
    ambient = super->lightProps.ambientStringht;
    lightColor[0] = super->lightProps.lightColor[0];
    lightColor[1] = super->lightProps.lightColor[1];
    lightColor[2] = super->lightProps.lightColor[2];
    lightPos[0] = super->lightProps.lightPos[0];
    lightPos[1] = super->lightProps.lightPos[1];
    lightPos[2] = super->lightProps.lightPos[2];
    if (ImGui::Checkbox("Light On", &lightSwich))
    {
        super->lightProps.lightSwich = lightSwich;
    }
    if (ImGui::SliderFloat("Ambient", &ambient, 0.0, 1.0))
    {
        super->lightProps.ambientStringht = ambient;
    }
    if (ImGui::SliderFloat3("lightColor", lightColor, 0.0, 1.0))
    {
        super->lightProps.lightColor = glm::vec3(lightColor[0], lightColor[1], lightColor[2]);
    }
    if (ImGui::InputFloat3("Light position", lightPos))
    {
        super->lightProps.lightPos = glm::vec3(lightPos[0], lightPos[1], lightPos[2]);
    }
}
void DialogLightSettings::renderMainSettingsTab(Engine::Frame *super)
{
    if (ImGui::Checkbox("Draw SkyBox", &drawSkybox))
    {
        super->drawSkyBox = drawSkybox;
    }
    checkClearColor();
    if (ImGui::SliderFloat3("Clear Color", clearColor, 0.0, 1.0))
    {

        super->clearColor(glm::vec4(clearColor[0], clearColor[1], clearColor[2], 1.0));
    }
}
void DialogLightSettings::checkClearColor()
{
    if (clearColor[0] > 1.0)
        clearColor[0] = 1.0;
    if (clearColor[0] < 0.0)
        clearColor[0] = 0.0;
    if (clearColor[1] > 1.0)
        clearColor[1] = 1.0;
    if (clearColor[1] < 0.0)
        clearColor[1] = 0.0;
    if (clearColor[2] > 1.0)
        clearColor[2] = 1.0;
    if (clearColor[2] < 0.0)
        clearColor[2] = 0.0;
}