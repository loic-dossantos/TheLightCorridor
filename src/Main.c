#include <stdio.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "Racket.h"
#include "Ball.h"
#include "3Dtools.h"
#include "Collision.h"
#include "Corridor.h"
#include "TextureControl.h"

#define NB_SEG_CIRCLE 64

#ifndef STBI_NO_STDIO
#include <stdio.h>
#endif // STBI_NO_STDIO

/* INTERRACTION */
typedef struct
{
    float xmin, ymin, xmax, ymax;
} CoordinatesQuads;

CoordinatesQuads playHitbox;
CoordinatesQuads quitHitbox;

/* TEXTURE Declaration */
#define nbTextures 2
GLuint texture_ids[nbTextures];
textureData *images_datas;
char texturesPath[nbTextures][50] = {
    "./ressources/playButton.jpg", // 28 chars
    "./ressources/quitButton.jpg"  // 28 chars
};

/* Game variable */

static int timeStep = 0;
static int clicked = 0;
static int interacted = 0;

/* INTERFACE */
typedef enum
{
    MENU,
    JEU,
    FIN
} Interface;

Interface currentScreen = MENU;

int right_clicked = 0;

/* Error handling function */
void onError(int error, const char *description)
{
    fprintf(stderr, "GLFW Error: %s\n", description);
}

void onWindowResized(GLFWwindow *window, int width, int height)
{
    aspectRatio = width / (float)height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, aspectRatio, Z_NEAR, Z_FAR);
    glMatrixMode(GL_MODELVIEW);
}

void onKey(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        switch (key)
        {
        case GLFW_KEY_A:
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            freeTextures(images_datas, nbTextures);
            glDisable(GL_TEXTURE_2D);
            break;
            break;
        case GLFW_KEY_L:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            break;
        case GLFW_KEY_P:
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            break;
        case GLFW_KEY_KP_9:
            if (dist_zoom < 100.0f)
                dist_zoom *= 1.1;
            printf("Zoom is %f\n", dist_zoom);
            break;
        case GLFW_KEY_KP_3:
            if (dist_zoom > 1.0f)
                dist_zoom *= 0.9;
            printf("Zoom is %f\n", dist_zoom);
            break;
        case GLFW_KEY_UP:
            if (phy > 2)
                phy -= 2;
            printf("Phy %f\n", phy);
            break;
        case GLFW_KEY_DOWN:
            if (phy <= 178.)
                phy += 2;
            printf("Phy %f\n", phy);
            break;
        case GLFW_KEY_LEFT:
            theta -= 5;
            break;
        case GLFW_KEY_RIGHT:
            theta += 5;
            break;
        default:
            fprintf(stdout, "Touche non gérée (%d)\n", key);
        }
    }
}

void drawSquareLine(double side)
{
    double side_length = side / 2;

    glBegin(GL_LINE_LOOP);
    glVertex3f(-side_length, -side_length, 0.0);
    glVertex3f(side_length, -side_length, 0.0);
    glVertex3f(side_length, side_length, 0.0);
    glVertex3f(-side_length, side_length, 0.0);
    glEnd();
}

void drawRacket(GLFWwindow *window, Racket racket)
{
    glPushMatrix();
    glRotatef(90., 0., 1., 0.);
    glScalef(1.0, 1.0, 1.0);
    glColor3f(1, 1, 1);
    glBegin(GL_LINE_LOOP);
    glVertex3f(racket.x - racket.side, racket.y - racket.side, racket.z);
    glVertex3f(racket.x + racket.side, racket.y - racket.side, racket.z);
    glVertex3f(racket.x + racket.side, racket.y + racket.side, racket.z);
    glVertex3f(racket.x - racket.side, racket.y + racket.side, racket.z);
    glEnd();
    glPopMatrix();
}

void drawCorridor()
{
    float z = -0.5;
    float z2 = -1.;
    for (int i = 0; i < 20; i++)
    {
        glColor3f((1. / 20.) * i, (1. / 20.) * i, (1. / 20.) * i);

        glPushMatrix();
        glTranslatef(-0.5 * i, 0.0, z);
        glScalef(0.5, 1., 0.5);
        drawRectangle();
        glPopMatrix();

        glPushMatrix();
        glRotatef(90., 1.0, 0., 0.);
        glTranslatef(-0.5 * i, 0.0, z2);
        glScalef(0.5, 1., 0.5);
        drawSquare();
        glPopMatrix();

        glPushMatrix();
        glRotatef(-90., 1.0, 0., 0.);
        glTranslatef(-0.5 * i, 0.0, z2);
        glScalef(0.5, 1., 0.5);
        drawSquare();
        glPopMatrix();

        glPushMatrix();
        glRotatef(180., 1.0, 0., 0.);
        glTranslatef(-0.5 * i, 0.0, z);
        glScalef(0.5, 1., 0.5);
        drawRectangle();
        glPopMatrix();
    }
}

void drawWalls(Corridor corridor)
{
    for(int i = 0; i < corridor.number_of_walls; i++) {
        Wall wall = corridor.walls[i];
        glPushMatrix();
            glRotatef(90., 0., 1., 0.);
            glTranslatef(wall.z, wall.y, wall.x);
            glScalef(wall.x_scale, wall.y_scale, 1.0);
            glColor3f(0, 0, 0.7);
            drawSquare();
        glPopMatrix();
    }
}

void drawRectangleButton(float x_length, float y_length, float x_offset, float y_offset, float scale, int textuID, CoordinatesQuads *coord)
{
    glBegin(GL_QUADS);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, images_datas[textuID].textureID);
    // glBindTexture(GL_TEXTURE_2D, 3);

    // fprintf(stdout, " %d texture getting -  %d \n", textuID, images_datas[textuID].textureID);

    coord->xmin = (-x_length / 2 * scale) + x_offset;
    coord->xmax = (x_length / 2 * scale) + x_offset;
    coord->ymax = (y_length / 2 * scale) + y_offset;
    coord->ymin = (-y_length / 2 * scale) + y_offset;

    glTexCoord2f(0, 0);
    glVertex2f(coord->xmin, coord->ymax);

    glTexCoord2f(1, 0);
    glVertex2f(coord->xmax, coord->ymax);

    glTexCoord2f(1, 1);
    glVertex2f(coord->xmax, coord->ymin);

    glTexCoord2f(0, 1);
    glVertex2f(coord->xmin, coord->ymin);
    glBindTexture(GL_TEXTURE_2D, 0);

    glEnd();
    return;
}

void update_screen(GLFWwindow *window, Corridor* corridor)
{
    double x, y, x_racket, y_racket;

    glfwGetCursorPos(window, &x, &y);
    x_racket = (y / WINDOW_HEIGHT) - 0.5;
    y_racket = (x / WINDOW_HEIGHT) - 1.;

    update_racket(&(corridor->racket), x_racket, y_racket);
    drawRacket(window, corridor->racket);
    drawCorridor();

    /* Ball Rendering with shadow */
    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(corridor->ball.x, corridor->ball.y, corridor->ball.z);
    glScalef(0.1, 0.1, 0.1);
    drawSphere();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0.0, 0.0, -4.9 - corridor->ball.z * 10);
    drawCircle();
    glPopMatrix();

    // drawWall(1.);
}

void mouse_click_callback(GLFWwindow *window, int key, int action, int mods)
{
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    /* CONVERT TO WINDOW COORDINATES */
    x = (x * GL_VIEW_SIZE / WINDOW_WIDTH) - GL_VIEW_SIZE / 2;
    y = -(y * GL_VIEW_SIZE / WINDOW_HEIGHT - GL_VIEW_SIZE / 2);
    switch (currentScreen)
    {
    case MENU:
        if (key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
        {
            //fprintf(stdout, " Clicked %f || %f \n", x, y);
            //fflush(stdout);
            if (x > playHitbox.xmin && x < playHitbox.xmax && y < playHitbox.ymax && y > playHitbox.ymin)
            {
                //fprintf(stdout, "Clicked on PLay");
                //fflush(stdout);
                currentScreen = JEU;
                glDisable(GL_TEXTURE_2D);
            }
        }
        break;
    case JEU:
        if (key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        {
            clicked = 1;
        }
        if (key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
        {
            clicked = 0;
        }
        if (key == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        {
            right_clicked = 1;
        }
        break;
    case FIN:
        break;
    }
}

int main(int argc, char const *argv[])
{
    GLFWwindow *window;

    srand(time(NULL));

    if (!glfwInit())
        return -1;

    /* Callback to a function if an error is rised by GLFW */
    glfwSetErrorCallback(onError);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);

    if (!window)
    {
        // If no context created : exit !
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSetWindowSizeCallback(window, onWindowResized);
    glfwSetKeyCallback(window, onKey);

    glfwSetMouseButtonCallback(window, mouse_click_callback);

    /* Texture */
    // Tells how texture is packed (fixed inclined textures problem)
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    images_datas = prepareTexture(nbTextures, texturesPath);
    glEnable(GL_TEXTURE_2D);

    /*  ----  */

    onWindowResized(window, WINDOW_WIDTH, WINDOW_HEIGHT);

    glPointSize(5.0);
    glEnable(GL_DEPTH_TEST);

    Corridor corridor = create_corridor();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Get time (in second) at loop beginning */
        double startTime = glfwGetTime();

        /* Cleaning buffers and setting Matrix Mode */
        glClearColor(0.2, 0.0, 0.0, 0.0);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        /* RENDER */
        switch (currentScreen)
        {
        case MENU:
            glClearColor(0.0, 0.0, 0.2, 0.0);
            glClear(GL_COLOR_BUFFER_BIT);
            drawRectangleButton(6., 2., 0, -2, 1, 0, &playHitbox);

            drawRectangleButton(6., 2., 0, -5, 1, 1, &quitHitbox);
            break;
        case JEU:
            setCamera();
            update_screen(window, &corridor);

            drawWalls(corridor);

            update_ball(&(corridor.ball));
            collision_racket(&corridor);
            collision_corridor(&corridor);
            if(corridor.pause && right_clicked) {
                unpause(&corridor);
            }
            if(clicked && !corridor.pause) {
                collision_racket_wall(&corridor);
            }

            collision_walls(&corridor);

            //fprintf(stdout, "Current timeStep (%d) | Clicked ? %s \n", timeStep, clicked == 1 ? "yes" : "no");
            if (!interacted) // Si la racket n'interragit pas avec la balle
            {
                timeStep++;
            }
            else
            {
            }
            // Reset richtclicked.
            if(right_clicked) {
                right_clicked = 0;
            }
            break;
        case FIN:
            break;
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        /* Elapsed time computation from loop begining */
        double elapsedTime = glfwGetTime() - startTime;
        /* If to few time is spend vs our wanted FPS, we wait */
        if (elapsedTime < FRAMERATE_IN_SECONDS)
        {
            glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS - elapsedTime);
        }
    }

    glfwTerminate();
    return 0;
}
