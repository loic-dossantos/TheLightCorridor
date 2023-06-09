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


/* RANDOM */
int flickerCount = 0;
float incre=0;

/* INTERRACTION */
GLdouble modelMat[16];
GLdouble projectionMat[16];
GLint view[4];
typedef struct
{
    float xmin, ymin, xmax, ymax;
} CoordinatesQuads;

GLfloat dummyHitbox[4][3];
GLfloat playHitbox[4][3];
GLfloat playWindowHitbox[4][3];
GLfloat quitHitbox[4][3];
GLfloat quitWindowHitbox[4][3];
GLfloat TitleHitbox[4][3];

/* TEXTURE Declaration */
#define nbTextures 22
GLuint textures[nbTextures];
textureData *images_datas;
char *texturesPath[nbTextures] = {      
    "./ressources/0.png",
    "./ressources/1.png",
    "./ressources/2.png",
    "./ressources/3.png",
    "./ressources/4.png",
    "./ressources/5.png",
    "./ressources/6.png",
    "./ressources/7.png",
    "./ressources/8.png",
    "./ressources/9.png",

    "./ressources/playButton.jpg", // 28 chars
    "./ressources/quitButton.jpg",  // 28 chars
    "./ressources/Title.png",  // 23 chars
    "./ressources/Title2.png",  // 24 chars
    "./ressources/heartFull.png",
    "./ressources/heartEmpty.png",
    "./ressources/GameOver.png",
    "./ressources/WIN.png",
    "./ressources/score.png",
    "./ressources/BedrockMC3x3.jpg",     
    "./ressources/StoneMC3x3.jpg",
    "./ressources/ObstacleTexture.jpg"

};

/* Game variable */

static int timeStep = 0;
static int clicked = 0;

/* INTERFACE */
typedef enum{
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
    float aspectRatio = width / (float)height;

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
            freeTextures(textures, images_datas, nbTextures);
            glDisable(GL_TEXTURE_2D);
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;
        case GLFW_KEY_ENTER:
            if (currentScreen == MENU){
                currentScreen = JEU;
                theta = 0.0f; // Angle between x axis and viewpoint
                phy = 90.0f; // Angle between z axis and viewpoint
                dist_zoom = 1.0f; // Distance between origin and viewpoint
            }
            break;
        // case GLFW_KEY_L:
        //     glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //     break;
        // case GLFW_KEY_P:
        //     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        //     break;
        // case GLFW_KEY_J:
        //     if (dist_zoom < 100.0f)
        //         dist_zoom += 0.2;
        //     printf("Zoom is %f\n", dist_zoom);
        //     break;
        // case GLFW_KEY_H:
        //     //if (dist_zoom > 1.0f)
        //     dist_zoom -= 0.2;
        //     printf("Zoom is %f\n", dist_zoom);
        //     break;
        // case GLFW_KEY_UP:
        //     if (phy > 0)
        //         phy -= 2;
        //     printf("Phy %f\n", phy);
        //     break;
        // case GLFW_KEY_DOWN:
        //     if (phy <= 178.)
        //         phy += 2;
        //     printf("Phy %f\n", phy);
        //     break;
        // case GLFW_KEY_U:
        //     incre += 0.5;
        //     // printf("incre %f\n", incre);
        //     break;
        // case GLFW_KEY_I:
        //     incre -= 0.5;
        //     //printf("incre %f\n", incre);
        //     break;
        // case GLFW_KEY_LEFT:
        //     theta -= 2;
        //     printf("theta %f\n", theta);

        //     break;
        // case GLFW_KEY_RIGHT:
        //     theta += 2;
        //     printf("theta %f\n", theta);

        //     break;
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
    int r = 0;
    int g = 0;
    int b = 0;
    if ( !racket.sticky && !racket.exp){
        glColor3f(1., 1., 1.);    
    }
    else  {
        if (racket.sticky){
            b = 1;
        }
        if (racket.exp){
            g = 1;
        }
         glColor3f(r,g,b); 
    } 
    glBegin(GL_LINE_LOOP);
    glVertex3f(racket.x - racket.side, racket.y - racket.side, racket.z);
    glVertex3f(racket.x + racket.side, racket.y - racket.side, racket.z);
    glVertex3f(racket.x + racket.side, racket.y + racket.side, racket.z);
    glVertex3f(racket.x - racket.side, racket.y + racket.side, racket.z);
    glEnd();
    glPopMatrix();
}

void drawCorridor(Corridor corridor)
{
    float z = -0.5;
    float z2 = -1.;
    glEnable(GL_TEXTURE_2D);
    for (int i = 0; i < 2000; i++){
        //glColor3f((1. / 20.) * i, (1. / 20.) * i, (1. / 20.) * i);
        glColor3f(1,1,1);
        double x = -0.5*i + corridor.depth;

        // SOL
        glBindTexture(GL_TEXTURE_2D, textures[19]);
        glPushMatrix();
        glTranslatef(x, 0.0, z);
        glScalef(0.5, 1., 0.5);
        drawRectangleTx();
        glPopMatrix();

        // MUR DROIT
        glBindTexture(GL_TEXTURE_2D, textures[20]);
        glPushMatrix();
        glRotatef(90., 1.0, 0., 0.);
        glTranslatef(x, 0.0, z2);
        glScalef(0.5, 1., 0.5);
        drawSquareTx();
        glPopMatrix();

        // MUR GAUCHE
        glBindTexture(GL_TEXTURE_2D, textures[20]);
        glPushMatrix();
        glRotatef(-90., 1.0, 0., 0.);
        glTranslatef(x, 0.0, z2);
        glScalef(0.5, 1., 0.5);
        drawSquareTx();
        glPopMatrix();

        // PLAFOND
        glBindTexture(GL_TEXTURE_2D, textures[19]);
        glPushMatrix();
        glRotatef(180., 1.0, 0., 0.);
        glTranslatef(x, 0.0, z);
        glScalef(0.5, 1., 0.5);
        drawRectangleTx();
        glPopMatrix();
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

}

void drawWalls(Corridor corridor) {        
    glEnable(GL_TEXTURE_2D);
    for(int i = 0; i < corridor.number_of_walls; i++) {
        Wall wall = corridor.walls[i];
        glPushMatrix();
            glRotatef(90., 0., 1., 0.);
            glTranslatef(wall.z, wall.y, wall.x);
            glScalef(wall.x_scale, wall.y_scale, 1.0);
            glColor3f(0, 0, 0.7);
            glBindTexture(GL_TEXTURE_2D, textures[21]);
            drawSquareTx();
            glColor3f(1, 1, 1);
        glPopMatrix();
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void drawBonus(Corridor corridor) {
    for(int i = 0; i < corridor.number_of_bonus; i++) {
        Bonus bonus = corridor.bonus[i];
        glPushMatrix();
            glRotatef(90., 0., 1., 0.);
            glTranslatef(bonus.x, bonus.y, bonus.z);
            glRotatef(45., 0., 0., 1.);
            glScalef(0.1,0.1,0.1);
            if (bonus.type == MORELIFE){
                glColor3f(1, 0, 0);
            }else if (bonus.type == EXP) {
                glColor3f(0, 1, 0);
            }else if (bonus.type == STICKY) {
                glColor3f(0, 0, 1);
            }
            drawSquare();
            glColor3f(1, 1, 1);
        glPopMatrix();
    }
}
    
void drawRectangleTextured(float x_length, float y_length, float x_offset, float y_offset,float z_offset, float scale, int textuID,GLfloat hitbox[][3]){

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[textuID]);
    glBegin(GL_QUADS);

    float x1  = (-x_length / 2 * scale) + x_offset;
    float x2  = (x_length / 2 * scale) + x_offset;
    float y2  = (y_length / 2 * scale) + y_offset;
    float y1  = (-y_length / 2 * scale) + y_offset;

    GLfloat rect[4][3] = {
    {x1, y2, z_offset},  // Top-left
    {x2, y2, z_offset},  // Top-right
    {x2, y1, z_offset},  // Bottom-right
    {x1, y1, z_offset}   // Bottom-left
    };
    for (int i = 0; i<4;i++){
        for (int j = 0; j<3;j++){
            hitbox[i][j] = rect[i][j];
        }
    }

    glTexCoord3f(0, 0, 0);
    glVertex3f(x1, y2, z_offset);

    glTexCoord3f(1, 0, 0);
    glVertex3f(x2, y2, z_offset);

    glTexCoord3f(1, 1, 0);
    glVertex3f(x2, y1, z_offset);

    glTexCoord3f(0, 1, 0);
    glVertex3f(x1, y1, z_offset);

    // Reset
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    return;
}

float easeOutExpo(float x){
    return x == 1 ? 1 : 1-  pow(2,-10*x);
}

void drawEndTitle(int type){
    static float x = 0;
    // pos y  = 2 -> 0
    glColor4f(1.0,1.0,1.0,x);
    if (type == 0){
        // LOSE Title
        drawRectangleTextured(9., 3., 0, 2- (easeOutExpo(x)*2), -14, 2, 16, dummyHitbox);
    }else {
        // WIN title
        drawRectangleTextured(9., 3., 0, 2- (easeOutExpo(x)*2), -14, 2, 17, dummyHitbox);
    }
    x += 0.005;
}

void update_screen(GLFWwindow *window, Corridor* corridor)
{
    double x, y, x_racket, y_racket, x_diff, y_diff;

    glfwGetCursorPos(window, &x, &y);
    x_racket = (y / WINDOW_HEIGHT) - 0.5;
    y_racket = (x / WINDOW_HEIGHT) - 1.;

    x_diff = corridor->racket.x - (y / WINDOW_HEIGHT - 0.5);
    y_diff = corridor->racket.y - (x / WINDOW_HEIGHT - 1.);

    if(corridor->racket.sticky && check_collision_racket(*corridor) && corridor->ball.move_x == 0 && corridor->pause == 0) {
        corridor->ball.z += x_diff;
        corridor->ball.y -= y_diff;
    }

    update_racket(&(corridor->racket), x_racket, y_racket);
    drawCorridor(*corridor);
}

void mouse_click_callback(GLFWwindow *window, int key, int action, int mods){
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
            if (x > -1.7 && x < 1.7 && y < -1.2 && y > -3.5){
                currentScreen = JEU;
                theta = 0.0f; // Angle between x axis and viewpoint
                phy = 90.0f; // Angle between z axis and viewpoint
                dist_zoom = 1.0f; // Distance between origin and viewpoint
                glDisable(GL_TEXTURE_2D);
            }
            if (x > -1.7 && x < 1.7 && y < -4.7 && y > -7.0){
                freeTextures(textures, images_datas, nbTextures);
                glDisable(GL_TEXTURE_2D);
                glfwSetWindowShouldClose(window, GLFW_TRUE);
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

void draw_ball(Corridor *corridor){
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

    images_datas = prepareTexture(textures ,nbTextures, texturesPath);

    /* RANDOM INIT*/
    srand(time(NULL));
    /*  ----  */

    onWindowResized(window, WINDOW_WIDTH, WINDOW_HEIGHT);
    glPointSize(5.0);
    glEnable(GL_DEPTH_TEST);

    /* CORRIDOR */
    int nbObstacle = 50; // doit être plus que 9
    int nbBonus = 1 + nbObstacle / 10;

    Corridor corridor = create_corridor(nbObstacle, nbBonus);

    /* SCORE */
    int score = 0;
    char ScoreArray[11];
    float numbers_offset;


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)){
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
            //setCamera()
            glPushMatrix();

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            // pseudo-Flickering
            if (flickerCount == 0){
            if ( rand() % 20 == 0){
                drawRectangleTextured(9., 3., 0, 2, -14, 2, 13, dummyHitbox);
                flickerCount += (rand()%4 + 2);
            } else {
                drawRectangleTextured(9., 3., 0, 2, -14, 2, 12, dummyHitbox);
            }}else {
                drawRectangleTextured(9., 3., 0, 2, -14, 2, 13, dummyHitbox);
                flickerCount--;
            }

            glDisable(GL_BLEND);
            glBlendFunc(GL_ONE, GL_ZERO);

            drawRectangleTextured(6., 2., 0, -2,-14., 1, 10, playHitbox);
            drawRectangleTextured(6., 2., 0, -5, -14, 1, 11, quitHitbox);

            glPopMatrix();
            break;
        case JEU:
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            // INIT Light 
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT1); // Light on Camera
            glEnable(GL_DEPTH_TEST);

            setCamera();
            
            float overall_intensity = 0.2;
            
            /* BALL LIGHT SOURCE */
            GLfloat ball_light_ambient[] = { 0.7, 0, 0, 1.0 };
            GLfloat ball_light_diffuse[] = {overall_intensity,overall_intensity,overall_intensity,0.5};
            GLfloat ball_light_specular[] = { 50, overall_intensity, overall_intensity, 1 };
            GLfloat ball_light_position[] = { corridor.ball.x, corridor.ball.y, corridor.ball.z, 1 };

            glLightfv(GL_LIGHT0, GL_AMBIENT, ball_light_ambient);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, ball_light_diffuse);
            glLightfv(GL_LIGHT0, GL_SPECULAR, ball_light_specular);
            glLightfv(GL_LIGHT0, GL_POSITION, ball_light_position);
            glLightf(GL_LIGHT0,GL_CONSTANT_ATTENUATION,0);
            glLightf(GL_LIGHT0,GL_LINEAR_ATTENUATION,0.0);
            glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION,0.2);

            glEnable(GL_LIGHT0); // Light on ball


            /*  CAMERA LIGHT SOURCE*/
            glGetDoublev(GL_MODELVIEW_MATRIX, modelMat);
            GLfloat cam_pos[] = { 0, 0, 0}; 
            overall_intensity = 50;
            GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
            GLfloat light_diffuse[] = {overall_intensity,overall_intensity,overall_intensity,1};
            GLfloat light_specular[] = { 50, overall_intensity, overall_intensity, 1 };

            glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
            glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
            glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
            glLightfv(GL_LIGHT1, GL_POSITION, cam_pos);
            glLightf(GL_LIGHT1,GL_CONSTANT_ATTENUATION,0);
            glLightf(GL_LIGHT1,GL_LINEAR_ATTENUATION,0);
            glLightf(GL_LIGHT1,GL_QUADRATIC_ATTENUATION,0.1);     

            drawWalls(corridor);
            update_screen(window, &corridor);

            glDisable(GL_LIGHT0); // Light on ball stop
            glDisable(GL_LIGHT1); // Light from Camera stop
            glDisable(GL_LIGHTING);


            drawRacket(window, corridor.racket);
            drawBonus(corridor);
            draw_ball(&corridor); // Ball is unaffected by light

            update_ball(&(corridor.ball));
            collision_racket(&corridor);
            collision_corridor(&corridor);
            if(corridor.racket.sticky && right_clicked && corridor.ball.move_x == 0.) {
                corridor.ball.move_x = -0.05;
                corridor.ball.move_y = (-(corridor.racket.y - corridor.ball.y) * 4.5) / 40.;
                corridor.ball.move_z = ((corridor.racket.x - corridor.ball.z) * 4.5) / 40.;
            }
            if(corridor.pause && right_clicked) {
                unpause(&corridor);
            }
            if(clicked && !corridor.pause && corridor.ball.move_x != 0) {
                if (collision_racket_wall(&corridor)){
                    // SCORE GAIN CAN BE MODIFIED WITH BONUS
                    corridor.racket.exp <1? 0 : corridor.racket.exp--;
                    score += 50 * ( corridor.racket.exp ? 2 : 1);
                }
            }
            collision_walls(&corridor);
            collision_racket_bonus(&corridor);

            timeStep++;

            // Reset richtclicked.
            if(right_clicked) {
                right_clicked = 0;
            }


            /* UI DISPLAY */
            glPushMatrix();
            glRotatef(90., 0., 1., 0.);
            glRotatef(90., 0., 0., 1.);
            glTranslatef(-0.9, 0.43,0);
            glScalef(0.2,0.2,0.2);

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            for (int i = 0; i< 10;i++){
                if (i < corridor.racket.lives  ){
                drawRectangleTextured(1, 1., 0+i, 0,0.999 , 0.25, 14, playHitbox);
                }else {
                drawRectangleTextured(1, 1., 0+i, 0, 0.999 , 0.25, 15, playHitbox);
                }
            }
            drawRectangleTextured(400, 100., 0.4, -3.75, 0.999, 0.01*0.25, 18, playHitbox);
            sprintf(ScoreArray, "%010d", score);
            numbers_offset = 0.25;
            for (int i =0; i <10 ; i++){       
                drawRectangleTextured(40, 70., numbers_offset, -4, 0.999 , 0.01*0.25, ScoreArray[i]-48, playHitbox);
                numbers_offset += 0.1;
            }

            glDisable(GL_BLEND);
            glBlendFunc(GL_ONE, GL_ZERO);
            glPopMatrix();
            
            if ( corridor.racket.lives <=0 || corridor.depth >= nbObstacle*2 -2){
                currentScreen = FIN;
                glDisable(GL_LIGHTING);
                }
            break;

        case FIN:
            glClearColor(0.0, 0.0, 0.2, 0.0);
            glClear(GL_COLOR_BUFFER_BIT);

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            // Title
            if ( corridor.racket.lives <=0 ){           
                drawEndTitle(0);
            } else {
                drawEndTitle(1);
            }

            // DISPLAY SCORE at bottom left
            glColor3f(1.0,1.0,1.0);
            drawRectangleTextured(400, 100., 0, -2.2,-13, 0.01, 18, playHitbox);
            sprintf(ScoreArray, "%010d", score + corridor.racket.lives * 20000);
            numbers_offset = 0.25;
            for (int i =0; i <10 ; i++){       
                drawRectangleTextured(40, 70., numbers_offset- 0.5*5, -3,-13, 0.01, ScoreArray[i]-48, playHitbox);
                numbers_offset += 0.5;
            }
            glDisable(GL_BLEND);
            glBlendFunc(GL_ONE, GL_ZERO);

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
