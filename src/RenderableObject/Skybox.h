#ifndef SKYBOX_H
#define SKYBOX_H
#include "RenderableObject.h"

class Skybox : public RenderableObject
{
private:
    /* data */
    // GLuint texCubicID[6];
    // char *texFileNames[6];

public:
    bool initSkybox(GLuint skyShader);
    void draw(GLuint vp);

    ~Skybox() {}
};

#endif;