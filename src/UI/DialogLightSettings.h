#ifndef DIALOGLIGHTSETTING_H
#define DIALOGLIGHTSETTING_H
#include "UI.h"

class DialogLightSettings
{
private:
    bool lightSwich;
    bool lightSwichSkybox;
    bool drawSkybox;
    float clearColor[3];
    float lightColor[3];
    float lightPos[3];
    float ambient;
    float specular;
    int specularArea;
    float ambientSkybox;

public:
    DialogLightSettings(/* args */);
    ~DialogLightSettings();
    void setUpContent(Engine::Frame *super);
    void renderContent(Engine::Frame *super);
    void renderSkyboxTab(Engine::Frame *super);
    void renderObjectTab(Engine::Frame *super);
    void renderMainSettingsTab(Engine::Frame *super);
    void checkClearColor();
};

#endif