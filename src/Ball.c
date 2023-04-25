#include "Ball.h"

Ball init_ball() {
	Ball ball;

	ball.x = 0.0;
	ball.y = 0.0;
	ball.z = 0.0;
	ball.move_x = -0.05;
	ball.move_y = 0.0;
	ball.move_z = 0.0;

	return ball;
}

void update_ball(Ball* ball) {
	ball->x += ball->move_x;
	ball->y += ball->move_y;
	ball->z += ball->move_z;
}