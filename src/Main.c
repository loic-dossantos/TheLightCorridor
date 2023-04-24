#include <stdio.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#include "Racket.h"
#include "3Dtools.h"

#define NB_SEG_CIRCLE 64

double ball_x = 0.;
double ball_y = 0.;
// 1 = avance, 0 = recule
int ball_forward = 1;

/* Error handling function */
void onError(int error, const char* description) {
    fprintf(stderr, "GLFW Error: %s\n", description);
}

void onWindowResized(GLFWwindow* window, int width, int height) {
    aspectRatio = width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0,aspectRatio,Z_NEAR,Z_FAR);
    glMatrixMode(GL_MODELVIEW);

}

void onKey(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch(key) {
            case GLFW_KEY_A :
            case GLFW_KEY_ESCAPE :
                glfwSetWindowShouldClose(window, GLFW_TRUE);
                break;
            case GLFW_KEY_L :
                glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
                break;
            case GLFW_KEY_P :
                glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                break;
            case GLFW_KEY_KP_9 :
                if(dist_zoom<100.0f) dist_zoom*=1.1;
                printf("Zoom is %f\n",dist_zoom);
                break;
            case GLFW_KEY_KP_3 :
                if(dist_zoom>1.0f) dist_zoom*=0.9;
                printf("Zoom is %f\n",dist_zoom);
                break;
            case GLFW_KEY_UP :
                if (phy>2) phy -= 2;
                printf("Phy %f\n",phy);
                break;
            case GLFW_KEY_DOWN :
                if (phy<=178.) phy += 2;
                printf("Phy %f\n",phy);
                break;
            case GLFW_KEY_LEFT :
                theta -= 5;
                break;
            case GLFW_KEY_RIGHT :
                theta += 5;
                break;
            default: fprintf(stdout,"Touche non gérée (%d)\n",key);
        }
    }
}

void drawSquareLine(double side) {
    double side_length = side / 2;

    glBegin(GL_LINE_LOOP);
        glVertex3f(-side_length,-side_length,0.0);
        glVertex3f(side_length,-side_length,0.0);
        glVertex3f(side_length,side_length,0.0);
        glVertex3f(-side_length,side_length,0.0);
    glEnd();
}

void drawRacket(GLFWwindow* window, Racket racket) {
    double side = racket.side / 32.;

    float z = 0.129;

    glPushMatrix();
        glRotatef(90.,0.,1.,0.);
        glScalef(1.0,1.0,1.0);
        glColor3f(1,1,1);
        glBegin(GL_LINE_LOOP);
            glVertex3f(racket.x-side,racket.y-side,z);
            glVertex3f(racket.x+side,racket.y-side,z);
            glVertex3f(racket.x+side,racket.y+side,z);
            glVertex3f(racket.x-side,racket.y+side,z);
        glEnd();
    glPopMatrix();
}

void drawCorridor() {
    float z = -0.5;
    float z2 = -1.;
    for(int i = 0; i < 20; i++) {
        glColor3f((1./20.)*i,(1./20.)*i,(1./20.)*i);

        glPushMatrix();
            glTranslatef(-0.5*i,0.0,z);
            glScalef(0.5,1.,0.5);
            drawRectangle();
        glPopMatrix();

        glPushMatrix();
            glRotatef(90.,1.0,0.,0.);
            glTranslatef(-0.5*i,0.0,z2);
            glScalef(0.5,1.,0.5);
            drawSquare();
        glPopMatrix();

        glPushMatrix();
            glRotatef(-90.,1.0,0.,0.);
            glTranslatef(-0.5*i,0.0,z2);
            glScalef(0.5,1.,0.5);
            drawSquare();
        glPopMatrix();

        glPushMatrix();
            glRotatef(180.,1.0,0.,0.);
            glTranslatef(-0.5*i,0.0,z);
            glScalef(0.5,1.,0.5);
            drawRectangle();
        glPopMatrix();
    }
}

void drawWall(double depth) {
    glPushMatrix();
        glRotatef(90.,0.,1.,0.);
        glTranslatef(0.0,-7.5,-10.0 * depth);
        glScalef(10.0,10.0,1.0);
        glColor3f(0,0,0.7);
        drawSquare();
    glPopMatrix();
}

void update_screen(GLFWwindow* window, Racket* racket) {
    double x, y, x_racket, y_racket;

    glfwGetCursorPos(window, &x, &y);
    x_racket = (y / WINDOW_HEIGHT) - 0.5;
    y_racket = (x / WINDOW_HEIGHT) - 1.;
    printf("x: %f, y: %f\n", x_racket, y_racket);

    update_racket(racket, x_racket, y_racket);
    drawRacket(window, *racket);
    drawCorridor();

    /* Scene rendering */
    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
        glTranslatef(ball_x,ball_y,0.0);
        glScalef(0.1,0.1,0.1);
        drawSphere();
        glColor3f(1.0, 1.0, 1.0);
        glTranslatef(0.0,0.0,-4.9);
        drawCircle();
    glPopMatrix();
    drawWall(1.);
}

int main(int argc, char const *argv[]) {
    /* GLFW initialisation */
    GLFWwindow* window;
    if (!glfwInit()) return -1;

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

    glfwSetWindowSizeCallback(window,onWindowResized);
    glfwSetKeyCallback(window, onKey);

    onWindowResized(window,WINDOW_WIDTH,WINDOW_HEIGHT);

    glPointSize(5.0);
    glEnable(GL_DEPTH_TEST);

    Racket racket = init_racket(5.);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Get time (in second) at loop beginning */
        double startTime = glfwGetTime();

        /* Cleaning buffers and setting Matrix Mode */
        glClearColor(0.2,0.0,0.0,0.0);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        setCamera();

        update_screen(window, &racket);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        /* Elapsed time computation from loop begining */
        double elapsedTime = glfwGetTime() - startTime;
        /* If to few time is spend vs our wanted FPS, we wait */
        if(elapsedTime < FRAMERATE_IN_SECONDS)
        {
            glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS-elapsedTime);
        }

        /* Animate scenery */
        if(ball_forward) {
            ball_x -= 0.05;
        }
        else {
            ball_x += 0.05;
        }
        if(ball_x > 0. && !ball_forward) {
            ball_forward = 1;
        }
        if(ball_x < -2. && ball_forward) {
            ball_forward = 0;
        }
    }

    glfwTerminate();
    return 0;
}
