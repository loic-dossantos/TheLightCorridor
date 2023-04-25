#include "TextureControl.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

textureData *prepareTexture(const int size, char texturesPath[][50])
{

    textureData *datas = (textureData *)malloc(size * sizeof(textureData));

    for (int i = 0; i < size; i++)
    {
        GLuint textureID;
        glGenTextures(1, &textureID);
        printf("%s path \n", texturesPath[i]);
        unsigned char *data = stbi_load(texturesPath[i], &datas[i].x, &datas[i].y, &datas[i].n, 0);
        if (data == NULL)
        {
            fprintf(stdout, "EROR texture non chargé\n");
            glfwTerminate();
            data = NULL;
            return NULL;
        }
        else
        {
            fprintf(stdout, " texture chargé sur : %d \n", textureID);
        }

        // bind texture object
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, datas[i].x, datas[i].y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
        datas[i].textureID = textureID;
    }
    return datas;
};

void freeTextures(textureData *datas, const int size)
{
    for (int i = 0; i < size; i++)
    {
        glDeleteTextures(1, &datas[i].textureID);
    }
    free(datas);
};
