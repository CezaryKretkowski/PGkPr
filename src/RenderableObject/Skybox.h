#ifndef SKYBOX_H
#define SKYBOX_H
#include "RenderableObject.h"
#include "../GameObject/GameObject.h"

class Skybox : public RenderableObject
{
private:
    /* data */
    // GLuint texCubicID[6];
    // char *texFileNames[6];
    GLuint ambientStrenghtID;
    GLuint lightColorID;
    GLuint lightPosID;
    GLuint lightSwichID;
    GLuint M;

public:
    bool initSkybox(GLuint skyShader);

    void draw(GLuint vp);
    void setLightProp(LightProps l);
    ~Skybox() {}
};

#endif;