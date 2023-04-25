#ifndef __BALL_H__
#define __BALL_H__

#include <stdio.h>

typedef struct {
	double x;
	double y;
	double z;
	double move_x;
	double move_y;
	double move_z;
} Ball;

/* Initialise the Ball. */
Ball init_ball();

/* Update position of the Ball. */
void update_ball(Ball* ball);

#endif