#include "Ball.h"

Ball init_ball() {
	Ball ball;

	ball.x = 0.;
	ball.y = 0.;
	ball.z = 0.;
	ball.moving_forward = 1;
	ball.speed = 0.05;

	return ball;
}

void update_ball(Ball* ball) {
	if(ball->moving_forward) {
		ball->x -= ball->speed;
	}
	else {
		ball->x += ball->speed;	
	}
}