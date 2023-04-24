#include <stdio.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Racket.h"
#include "Geometry.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

/* Game variable */

static int timeStep = 0;
static int clicked = 0;
static int interacted = 0;

typedef enum
{
    MENU,
    JEU,
    FIN
} interface;

interface currentScreen = MENU;

/* TEXTURE Declaration */
unsigned char *texture_data1;
GLuint texture_id;

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

    if (aspectRatio > 1)
    {
        gluOrtho2D(
            -GL_VIEW_SIZE / 2. * aspectRatio, GL_VIEW_SIZE / 2. * aspectRatio,
            -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);
    }
    else
    {
        gluOrtho2D(
            -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
            -GL_VIEW_SIZE / 2. / aspectRatio, GL_VIEW_SIZE / 2. / aspectRatio);
    }
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
            stbi_image_free(texture_data1);
            glDeleteTextures(1, &texture_id);
            glDisable(GL_TEXTURE_2D);
            break;
        default:
            fprintf(stdout, "Touche non gérée\n");
        }
    }
}

void drawSquare(double side)
{
    double side_length = side / 2;

    glBegin(GL_LINE_LOOP);
    glVertex2f(-side_length, -side_length);
    glVertex2f(-side_length, side_length);
    glVertex2f(side_length, side_length);
    glVertex2f(side_length, -side_length);
    glEnd();
}

void drawRacket(GLFWwindow *window, Racket racket)
{
    glTranslatef(racket.x, racket.y, 0);
    glColor3f(1, 1, 1);
    drawSquare(racket.side);
    glLoadIdentity();
}

void update_screen(GLFWwindow *window, Racket *racket)
{
    double x, y, x_racket, y_racket;

    glfwGetCursorPos(window, &x, &y);
    x_racket = ((x * GL_VIEW_SIZE / WINDOW_WIDTH) - (GL_VIEW_SIZE / 2.)) * aspectRatio;
    y_racket = -((y * GL_VIEW_SIZE / WINDOW_HEIGHT) - (GL_VIEW_SIZE / 2.));

    update_racket(racket, x_racket, y_racket);

    drawRacket(window, *racket);
}

void mouse_click_callback(GLFWwindow *window, int key, int action, int mods)
{
    if (key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        clicked = 1;
    }
    if (key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        clicked = 0;
    }
}

int main(int argc, char const *argv[])
{
    GLFWwindow *window;

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

    // Tells how texture is packed
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    int x1, y1, n1;
    texture_data1 = stbi_load("./ressources/playButton.jpg", &x1, &y1, &n1, 0);
    if (texture_data1 == NULL)
    {
        fprintf(stdout, "EROR texture non chargé\n");
        glfwTerminate();
        return -1;
    }
    else
    {
        fprintf(stdout, " texture chargé\n");
    }

    // gen + bind texture object
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x1, y1, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data1);
    glEnable(GL_TEXTURE_2D);

    onWindowResized(window, WINDOW_WIDTH, WINDOW_HEIGHT);

    glPointSize(4.0);

    Racket racket = init_racket(4.);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Get time (in second) at loop beginning */
        double startTime = glfwGetTime();

        /* Cleaning buffers and setting Matrix Mode */
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        /* RENDER */
        switch (currentScreen)
        {
        case MENU:
            glClearColor(0.0, 0.0, 0.2, 0.0);
            glClear(GL_COLOR_BUFFER_BIT);

            glBegin(GL_QUADS);
            glEnable(GL_TEXTURE_2D);

            glBindTexture(GL_TEXTURE_2D, texture_id);

            glTexCoord2f(0, 0);
            glVertex2f(-3.f, -1.f);

            glTexCoord2f(1, 0);
            glVertex2f(3.f, -1.f);

            glTexCoord2f(1, 1);
            glVertex2f(3.f, -3.f);

            glTexCoord2f(0, 1);
            glVertex2f(-3.f, -3.f);

            glBindTexture(GL_TEXTURE_2D, 0);

            glEnd();
            break;
        case JEU:

            fprintf(stdout, "Current timeStep (%d) | Clicked ? %s \n", timeStep, clicked == 1 ? "yes" : "no");
            update_screen(window, &racket);
            if (!interacted) // Si la racket n'interragit pas avec la balle
            {
                timeStep++;
            }
            else
            {
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
