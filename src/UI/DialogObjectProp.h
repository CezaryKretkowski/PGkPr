#ifndef DIALOG_OBJECT_PROP_H
#define DIALOG_OBJECT_PROP_H
#include "UI.h"
#include "../GameObject/GameObject.h"
class DialogObjectProp : public UI
{
private:
    std::vector<GameObject *> objects;
    void run(Engine::Frame *super) override;
    void setUp(Engine::Frame *super) override;
    void clean(Engine::Frame *super) override;

public:
    void setUpContent(Engine::Frame *super);
    void renderContent(Engine::Frame *super);
    void addGameObject(Engine::Mesh *o)
    {
        puts("Object was added!!!");
        GameObject *obj = new GameObject(o->vert, o->normal, o->uvs);
        objects.push_back(obj);
    }
};

#endif