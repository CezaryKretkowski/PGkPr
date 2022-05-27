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

public:
    void addGameObject(GameObject *ObjectOnScenn);
    void setUpContent(Engine::Frame *super);
    void renderContent(Engine::Frame *super);
    void loadItems();
};

#endif