#include "Skybox.h"

bool Skybox::initSkybox(GLuint skyShader)
{
    GLuint TexCubicID[] = {
        GL_TEXTURE_CUBE_MAP_POSITIVE_X, // Prawo
        GL_TEXTURE_CUBE_MAP_NEGATIVE_X, // Lewo
        GL_TEXTURE_CUBE_MAP_POSITIVE_Y, // Góra
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, // Dół
        GL_TEXTURE_CUBE_MAP_POSITIVE_Z, // Przód
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Z  // Tył
    };
    const char *TexFileNames[] = {
        "../../resources/skyBoxTexture/stormydays_rt.png",
        "../../resources/skyBoxTexture/stormydays_lf.png",
        "../../resources/skyBoxTexture/stormydays_up.png",
        "../../resources/skyBoxTexture/stormydays_dn.png",
        "../../resources/skyBoxTexture/stormydays_bk.png",
        "../../resources/skyBoxTexture/stormydays_ft.png",

    };

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    for (int i = 0; i < 6; i++)
    {
        int width, height, nchan;
        unsigned char *dt = stbi_load(TexFileNames[i], &width, &height, &nchan, 0);
        if (!dt)
        {
            puts("error!!!");
            return false;
        }
        puts("Succes");
        glTexImage2D(TexCubicID[i], 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, dt);
        stbi_image_free(dt);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return true;
}
void Skybox::draw(GLuint vp)
{
    // glUniform1i(textureID, 0);
    // glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
    glm::mat4 M2 = glm::scale(modelMatrix, glm::vec3(30, 30, 30));
    M2 = glm::mat4(glm::mat3(M2));
    glm::mat4 MatMVP = modelMatrix * M2;

    glUniformMatrix4fv(vp, 1, GL_FALSE, &MVP[0][0]);
    glBindVertexArray(vao);

    MVP = projectionMatrix * viewMatrix * modelMatrix;
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}