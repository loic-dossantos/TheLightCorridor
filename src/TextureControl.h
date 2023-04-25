#ifndef __OPENGL_H__
#define __OPENGL_H__

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#endif

#ifndef __TEXTURECONTROL_H__
#define __TEXTURECONTROL_H__

typedef struct
{
    int x, y;
    int n; // Number of channels
    GLuint textureID;
    char filepath[];

} textureData;

textureData *prepareTexture(const int size, char texturesPath[][50]);

void freeTextures(textureData datas[], const int size);

#endif