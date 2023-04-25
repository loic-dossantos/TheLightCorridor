#include "Collision.h"

int check_collision_racket(Racket racket, Ball ball) {
	if(racket.y-racket.side < 0.085 && racket.y+racket.side > -0.085
        && racket.x-racket.side < 0.085 && racket.x+racket.side > -0.085) {
        return 1;
    }
    return 0;
}

void collision_racket(Racket* racket, Ball* ball) {
    if(ball->x > 0. && ball->move_x > 0) {
        if(check_collision_racket(*racket, *ball)) {
            ball->move_x *= -1;
        }
        else {
            ball->move_x = 0;
        }
    }
}