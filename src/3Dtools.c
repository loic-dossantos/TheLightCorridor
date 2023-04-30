#include "3Dtools.h"

/* Camera parameters and functions */
float theta = -90.0f; // Angle between x axis and viewpoint
float phy = 0.00001f; // Angle between z axis and viewpoint
float dist_zoom = 1.f; // Distance between origin and viewpoint

void setCamera() {
	gluLookAt(dist_zoom*cos(toRad(theta))*sin(toRad(phy)),
			  dist_zoom*sin(toRad(theta))*sin(toRad(phy)),
			  dist_zoom*cos(toRad(phy)),
			  0.0,0.0,0.0,
			  0.0,0.0,1.0);
}

/* Convert degree to radians */
float toRad(float deg) {
	return deg*M_PI/180.0f;
}


void drawSquare() {
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(-0.5,-0.5,0.0);
		glVertex3f(0.5,-0.5,0.0);
		glVertex3f(0.5,0.5,0.0);
		glVertex3f(-0.5,0.5,0.0);
	glEnd();
}
void drawSquareTx() {
	glBegin(GL_TRIANGLE_FAN);
	    glTexCoord3f(0, 0, 0);
		glVertex3f(-0.5,-0.5,0.0);
		glTexCoord3f(1, 0, 0);
		glVertex3f(0.5,-0.5,0.0);
		glTexCoord3f(1, 1, 0);
		glVertex3f(0.5,0.5,0.0);
		glTexCoord3f(0, 1, 0);
		glVertex3f(-0.5,0.5,0.0);
	glEnd();
}
void drawRectangle() {
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(-0.5,-1.0,0.0);
	glVertex3f(0.5,-1.0,0.0);
	glVertex3f(0.5,1.0,0.0);
	glVertex3f(-0.5,1.0,0.0);
	glEnd();
}
void drawRectangleTx() {
	glBegin(GL_TRIANGLE_FAN);
    glTexCoord3f(0, 0, 0);
	glVertex3f(-0.5,-1.0,0.0);
	glTexCoord3f(1, 0, 0);
	glVertex3f(0.5,-1.0,0.0);
    glTexCoord3f(1, 1, 0);
	glVertex3f(0.5,1.0,0.0);
    glTexCoord3f(0, 1, 0);
	glVertex3f(-0.5,1.0,0.0);
	glEnd();
}

void drawCircle() {
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0.0,0.0,0.0);
		float step_rad = 2*M_PI/(float)NB_SEG_CIRCLE;
		for(int i=0;i<=NB_SEG_CIRCLE;i++) {
			glVertex3f(cos(i*step_rad),sin(i*step_rad),0.0f);
		}
	glEnd();
}

void drawCone() {
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0.0,0.0,1.0);
		float step_rad = 2*M_PI/(float)NB_SEG_CIRCLE;
		for(int i=0;i<=NB_SEG_CIRCLE;i++) {
			glVertex3f(cos(i*step_rad),sin(i*step_rad),0.0f);
		}
	glEnd();
}

void drawSphere() {
	gluSphere(gluNewQuadric(),1.0,NB_SEG_CIRCLE,NB_SEG_CIRCLE);
}
