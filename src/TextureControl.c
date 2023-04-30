#include "TextureControl.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const char *pngExtension = ".png";
const char *jpgExtension = ".jpg";


textureData *prepareTexture(GLuint textures[], const int size, char **texturesPath){
    
    textureData *datas = (textureData *)malloc(size * sizeof(textureData));
    glGenTextures(size, textures);

    for (int i = 0; i < size; i++){
        //printf("%s path \n", texturesPath[i]);

        const char *last_four = &texturesPath[i][strlen(texturesPath[i])-4];
        //printf("%s path \n", last_four);
        unsigned char *data;
        if ( strcmp(last_four, pngExtension)== 0){
            //printf("%s equals \n", last_four);
            data = stbi_load(texturesPath[i], &datas[i].x, &datas[i].y, &datas[i].n, STBI_rgb_alpha);
        }else {
            data = stbi_load(texturesPath[i], &datas[i].x, &datas[i].y, &datas[i].n, STBI_rgb);
        }
        if (data == NULL){
            fprintf(stdout, "ERROR texture non chargée\n");
            glfwTerminate();
            return NULL;
        }
        //fprintf(stdout, " texture chargé sur : %d \n", textures[i]);
        // bind texture object
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        if (datas[i].n == 3){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, datas[i].x, datas[i].y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }else if  (datas[i].n == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, datas[i].x, datas[i].y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        } else {
            fprintf(stdout, "ERROR : Unsupported number of color channels \n");
            glfwTerminate();
            return NULL;
        }
        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(data);
        datas[i].textureID = textures[i];
    }
    return datas;
};

void freeTextures(GLuint textures[],textureData *datas, const int size){
    glDeleteTextures(size, textures);
    free(datas);
};
