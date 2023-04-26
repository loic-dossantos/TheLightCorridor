#include "Collision.h"

int check_collision_racket(Racket racket, Ball ball) {
	if(racket.y-racket.side < 0.085 + ball.y && racket.y+racket.side > -0.085 + ball.y 
        && racket.x-racket.side < 0.085 - ball.z && racket.x+racket.side > -0.085 - ball.z) {
        return 1;
    }
    return 0;
}

void collision_racket(Racket* racket, Ball* ball) {
    if(ball->x > 0. && ball->move_x > 0) {
        if(check_collision_racket(*racket, *ball)) {
            ball->move_x *= -1;
            ball->move_y = (-(racket->y - ball->y) * 4.5) / 40.;
            ball->move_z = ((racket->x - ball->z) * 4.5) / 40.;
        }
        else {
            ball->move_x = 0;
            ball->move_y = 0;
            ball->move_z = 0;
        }
    }
}

void collision_corridor(Ball* ball) {
    if(ball->y < -0.9 || ball->y > 0.9) {
        ball->move_y *= -1;
    }
    if(ball->z < -0.4 || ball->z > 0.4) {
        ball->move_z *= -1;
    }
}