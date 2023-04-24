#include "TextureControl.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

textureData *prepareTexture(GLuint texture_ids[], const int size)
{

    textureData datas[size];

    glGenTextures(size, texture_ids);
    for (int i = 0; i < size; i++)
    {
        datas[i].data = stbi_load("./ressources/playButton.jpg", &datas[i].x, &datas[i].y, &datas[i].n, 0);
        if (datas[i].data == NULL)
        {
            fprintf(stdout, "EROR texture non chargé\n");
            glfwTerminate();
            return NULL;
        }
        else
        {
            fprintf(stdout, " texture chargé\n");
        }

        // gen + bind texture object
        glBindTexture(GL_TEXTURE_2D, texture_ids[i]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, datas[i].x, datas[i].y, 0, GL_RGB, GL_UNSIGNED_BYTE, datas[i].data);
    }
    return datas;
};

void freeTextures(GLuint texture_ids[], textureData *datas, const int size)
{
    /*for (int i = 0; i < size; i++)
    {
        stbi_image_free(datas[i].data);
        // free(datas[i].data);
    }*/
    // SEG FAULT ICI dans la boucle
    free(datas);
    glDeleteTextures(size, texture_ids);
};