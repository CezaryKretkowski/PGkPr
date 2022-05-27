// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

#include "shader.hpp"
#include "src/Engine/Frame.h"
#include "App.h"
#include "App2.h"
#include "src/Scene/Scene.h"
#include "src/Engine/Loader.h"
#include "src/UI/DialogModelSelection.h"
#include "src/UI/DialogObjectProp.h"
#include <math.h>
#include "dependeces/Common/dirent.h"
std::vector<std::string> names;
const char *items[100];
std::vector<RenderableObject *> objects;
void loadName()
{
    DIR *dir;
    struct dirent *ent;
    int i = 0;
    if ((dir = opendir("../../resources/Models/")) != NULL)
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
    int size = names.size();
    if (size > 100)
        size = 100;
    int j = 0;
    for (j; j < size; j++)
    {
        const char *name = names[j].c_str();
        // printf("%s \n", name);
        items[j] = name;
    }
}
void loadObjects()
{
}
int main(void)
{
    // printf("Wynik %f",  calculateDistance(glm::vec3(-4,0,1),glm::vec3(1,-3,2)));
    loadName();
    App *app = new App();
    std::string dirPath = "../../resources/Models/";
    Engine::Frame frame;
    for (int i = 0; i < names.size(); i++)
    {
        std::string path = dirPath + names[i];
        Engine::Mesh m;
        OBJLoad(path.c_str(), m.vert, m.normal, m.uvs);
        frame.objects.push_back(m);
    }
    DialogModelSelection *ui = new DialogModelSelection();
    DialogObjectProp *prop = new DialogObjectProp();
    frame.add(app);
    frame.add(ui);
    // frame.add(prop);
    ui->setVisiblity(true);
    if (!frame.init())
    {
        puts("Somthing wnet wrong");
    }

    return 0;
}
