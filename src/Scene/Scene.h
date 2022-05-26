//
// Created by cezar on 16.04.2022.
//

#ifndef PGKPR_SCENE_H
#define PGKPR_SCENE_H

#include "../Engine/Component.h"
#include "../dependeces/Common/stb_image.h"
#include "../RenderableObject/RenderableObject.h"
#include "../Engine/Loader.h"
#include "../RenderableObject/Skybox.h"
#include "../Camera/Camera.h"
#include "../GameObject/GameObject.h"
namespace Engine
{
    class Scene : public Engine::Component
    {
        GLuint texCubicID[6];
        char *texFileNames[6];
        GLuint skyShaderID;
        Skybox skybox;
        GLuint vp;
        std::vector<GameObject *> objects;

    protected:
        Camera camera;
        void setUp(Engine::Frame *super)
        {
            //  initSkybox();
            glEnable(GL_DEPTH_TEST);

            skyShaderID = LoadShaders("../../shaders/skyboxVert.glsl", "../../shaders/skyboxFrag.glsl");
            std::vector<glm::vec3> normal, vector;
            std::vector<glm::vec2> uv;
            OBJLoad("../../resources/cube1.obj", vector, normal, uv);
            skybox.initSkybox(skyShaderID);
            vp = glGetUniformLocation(skyShaderID, "VP");
            skybox.initFromArrary(vector, normal, uv);
            skybox.scale(glm::vec3(30.0f, 30.f, 30.f));
            initScene(super);
        }

        void run(Engine::Frame *super)
        {

            glDepthMask(GL_FALSE);
            glUseProgram(skyShaderID);

            camera.upDateView();
            skybox.setModelMatrix(glm::translate(glm::mat4(1), camera.getPosytion()));
            skybox.setViewMatrix(camera.getViewMatrix());
            skybox.setProjectionMatrix(camera.getProjectionMatrix());
            skybox.draw(vp);
            glUseProgram(0);
            glDepthMask(GL_TRUE);
            for (int i = 0; i < objects.size(); i++)
            {
                puts("Rysuje");
                objects[i]->setProjectionMatrix(camera.getProjectionMatrix());
                objects[i]->setViewMatrix(camera.getViewMatrix());
                objects[i]->draw();
            }
            upDateScene(super);
        }

        void clean(Engine::Frame *super)
        {
            cleanScene(super);
        }

    public:
        Scene()
        {
        }

        ~Scene() {}
        void addGameObject(Engine::Mesh *o)
        {
            puts("Object was added!!!");
            GameObject obj(o->vert, o->normal, o->uvs);
            objects.push_back(&obj);
        }

        void virtual initScene(Engine::Frame *super) { puts("initScene"); }

        void virtual upDateScene(Engine::Frame *super) { puts("upDateScene"); }

        void virtual cleanScene(Engine::Frame *super) { puts("cleanScene"); }
    };
}
#endif // PGKPR_SCENE_H
