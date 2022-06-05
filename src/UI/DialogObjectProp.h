#ifndef DIALOG_OBJECT_PROP_H
#define DIALOG_OBJECT_PROP_H
#include "UI.h"
#include "../GameObject/GameObject.h"
class DialogObjectProp
{
private:
    std::vector<GameObject *> objects;
    const char *item[100];
    int size;
    float translation[3];
    float scale[3];
    float roata[4];
    std::vector<std::string> names;

public:
    void setUpContent(Engine::Frame *super);
    void renderContent(Engine::Frame *super);
    void loadItems(glm::vec3 translate, glm::vec3 sceale, glm::vec4 rotate);
    void loadFileList();
};

#endif