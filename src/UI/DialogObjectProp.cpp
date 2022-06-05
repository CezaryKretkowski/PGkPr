#include "DialogObjectProp.h"
#include <string.h>
#include <string>
#include <cstring>
#include "../../dependeces/Common/dirent.h"
void DialogObjectProp::setUpContent(Engine::Frame *super)
{
    this->objects = objects;
    translation[0] = 0.0f;
    translation[1] = 0.0f;
    translation[2] = 0.0f;
    loadFileList();
}
void DialogObjectProp::loadItems(glm::vec3 translate, glm::vec3 sceale, glm::vec4 rotate)
{
    translation[0] = translate[0];
    translation[1] = translate[1];
    translation[2] = translate[2];
    scale[0] = sceale[0];
    scale[1] = sceale[1];
    scale[2] = sceale[2];
    roata[0] = rotate[0];
    roata[1] = rotate[1];
    roata[2] = rotate[2];
    roata[3] = rotate[3];
}
void DialogObjectProp::renderContent(Engine::Frame *super)
{

    int index = 0;
    int index1 = 0;
    if (ImGui::BeginListBox("GameObject", ImVec2(200, 40)))
    {
        for (int i = 0; i < super->gameObjects.size(); i++)
        {
            bool selected = false;
            std::string &item_name = std::to_string(i) + ". " + super->gameObjects[i]->getName();
            if (ImGui::Selectable(item_name.c_str(), &selected))
            {
                index = i;
                printf("%d\n", index);
                glm::vec3 translation = super->gameObjects[i]->translate;
                glm::vec4 roatation = glm::vec4(super->gameObjects[i]->rotate, super->gameObjects[i]->angle);
                glm::vec3 scele = super->gameObjects[i]->scale;
                loadItems(translation, scele, roatation);
            }
        }
        ImGui::EndListBox();
    }
    if (super->gameObjects.empty())
    {
        translation[0] = 0.0f;
        translation[1] = 0.0f;
        translation[2] = 0.0f;
        scale[0] = 1.0f;
        scale[1] = 1.0f;
        scale[2] = 1.0f;
        roata[0] = 1.0f;
        roata[1] = 1.0f;
        roata[2] = 1.0f;
        roata[3] = 0.0f;
    }
    char buffer[200] = "";
    if (!super->gameObjects.empty())
    {
        std::string name = super->gameObjects[index]->getName();
        strcpy(buffer, name.c_str());
    }

    ImGui::SetCursorPos(ImVec2(8, 70));
    if (ImGui::InputText("Name", buffer, sizeof(buffer)))
    {
        if (!super->gameObjects.empty())
        {
            super->gameObjects[index]->setName(std::string(buffer));
        }
    }

    if (ImGui::InputFloat3("Translation", translation))
    {
        if (!super->gameObjects.empty())
        {
            super->gameObjects[index]->translate = glm::vec3(translation[0], translation[1], translation[2]);
        }
    }
    if (ImGui::InputFloat3("Scale", scale))
    {
        if (!super->gameObjects.empty())
        {
            super->gameObjects[index]->scale = glm::vec3(scale[0], scale[1], scale[2]);
        }
    }
    if (ImGui::InputFloat4("Rotate", roata))
    {
        if (!super->gameObjects.empty())
        {
            if (roata[0] < 1.0f && roata[1] < 1.0f && roata[2] < 1.0f)
            {
                roata[0] = 1.0f;
                roata[1] = 1.0f;
                roata[2] = 1.0f;
            }

            super->gameObjects[index]->rotate = glm::vec3(roata[0], roata[1], roata[2]);
            super->gameObjects[index]->angle = roata[3];
            super->gameObjects[index]->rotateObject();
        }
    }
    if (ImGui::BeginListBox("GameObject Texture Selection", ImVec2(200, 40)))
    {

        for (int i = 0; i < names.size(); i++)
        {
            bool selected = false;
            std::string &item_name = std::to_string(i) + ". " + names[i];
            if (ImGui::Selectable(item_name.c_str(), &selected))
            {
                std::string path = "../../resources/Texture/" + names[i];
                super->gameObjects[index]->setTexture(super->gameObjects[index]->loadTexture(path));
            }
        }

        ImGui::EndListBox();
    }
}
void DialogObjectProp::loadFileList()
{
    DIR *dir;
    struct dirent *ent;
    int i = 0;
    if ((dir = opendir("../../resources/Texture")) != NULL)
    { /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL)
        {
            if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
            {
                std::string name(ent->d_name);

                names.push_back(name);
            }
        }
        i++;
        closedir(dir);
    }
    else
    {
        /* could not open directory */
        perror("");
    }
}
