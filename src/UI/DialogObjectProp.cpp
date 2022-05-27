#include "DialogObjectProp.h"
void DialogObjectProp::setUpContent(Engine::Frame *super)
{
    this->objects = objects;
}
void DialogObjectProp::loadItems()
{
    size = objects.size();
    if (size > 300)
        size = 300;
    int j = 0;
    for (j; j < size; j++)
    {
        const char *name1 = objects[j]->getName().c_str();
        printf("%s \n", name1);
        item[j] = objects[j]->getName().c_str();
    }
}
void DialogObjectProp::renderContent(Engine::Frame *super)
{
    loadItems();
    int selectable;
    ImGui::ListBox("GameObjects On Scene", &selectable, item, size, 10);
}
void DialogObjectProp::addGameObject(GameObject *ObjectOnScenn)
{
    puts("Dodano Game Object");
    objects.push_back(ObjectOnScenn);
}
