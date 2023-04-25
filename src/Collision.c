#include "Collision.h"

int check_collision_racket(Racket racket, Ball ball) {
	if(ball.x > 0. && ball.move_x > 0
        && racket.y-racket.side < 0.085 && racket.y+racket.side > -0.085
        && racket.x-racket.side < 0.085 && racket.x+racket.side > -0.085) {
        printf("Rebond.\n");
    }

    return 0;
}

void collision_racket(Racket* racket, Ball* ball) {
    
}