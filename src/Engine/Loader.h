#ifndef LOADER_H
#define LOADER_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../../dependeces/Common/OBJ_Loader.h"
#include "../../dependeces/Common/stb_image.h"

// #define GLFW_INCLUDE_NONE
// #include <GLFW/glfw3.h>
// #include <GL/glew.h>

#include <glm/glm.hpp>

bool OBJLoad(std::string path, std::vector<glm::vec3> &vert, std::vector<glm::vec3> &normals, std::vector<glm::vec2> &uv)
{
    objl::Loader loader;

    if (!loader.LoadFile(path))
        return false;

    for (int i = 0; i < loader.LoadedMeshes.size(); i++)
    {
        objl::Mesh curMesh = loader.LoadedMeshes[i];
        for (int j = 0; j < curMesh.Vertices.size(); j++)
        {
            vert.push_back(glm::vec3(curMesh.Vertices[j].Position.X, curMesh.Vertices[j].Position.Y, curMesh.Vertices[j].Position.Z));
            normals.push_back(glm::vec3(curMesh.Vertices[j].Normal.X, curMesh.Vertices[j].Normal.Y, curMesh.Vertices[j].Normal.Z));
            uv.push_back(glm::vec2(curMesh.Vertices[j].TextureCoordinate.X, curMesh.Vertices[j].TextureCoordinate.Y));
        }
    }

    return true;
}
// bool loadTexture01(GLuint shederID, std::string texturePath, GLchar *name, GLint out[2])
// {
//     GLuint textureId, texture;
//     textureId = glGetUniformLocation(shederID, name);

//     glGenTextures(1, &texture);
//     glBindTexture(GL_TEXTURE_2D, texture);
//     int width, height, nchan;
//     unsigned char *dt = stbi_load(texturePath.c_str(), &width, &height, &nchan, 0);
//     if (!dt)
//     {
//         puts("Cannot load Texture");
//         return false;
//     }

//     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dt);
//     glGenerateMipmap(GL_TEXTURE_2D);
//     stbi_image_free(dt);
//     out[0] = textureId;
//     out[1] = texture;
//     return true;
// }

#endif