#include "Skybox.h"

bool Skybox::initSkybox(GLuint skyShader)
{

    ambientStrenghtID = glGetUniformLocation(skyShader, "ambientStrength");
    lightColorID = glGetUniformLocation(skyShader, "lightColor");
    lightPosID = glGetUniformLocation(skyShader, "lightPos");
    lightSwichID = glGetUniformLocation(skyShader, "lightSwich");
    M = glGetUniformLocation(skyShader, "M");
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

    scale(glm::vec3(30.f, 30.f, 30.f));

    glUniformMatrix4fv(vp, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(M, 1, GL_FALSE, &modelMatrix[0][0]);
    glBindVertexArray(vao);

    MVP = projectionMatrix * viewMatrix * modelMatrix;
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}
void Skybox::setLightProp(LightProps l)
{
    glUniform1f(ambientStrenghtID, l.ambientStringht);
    glUniform3f(lightColorID, l.lightColor.x, l.lightColor.y, l.lightColor.z);
    glUniform3f(lightPosID, l.lightPos.x, l.lightPos.y, l.lightPos.z);
    if (l.lightSwich)
    {
        glUniform1i(lightSwichID, GL_TRUE);
    }
    else
    {
        glUniform1i(lightSwichID, GL_FALSE);
    }
}