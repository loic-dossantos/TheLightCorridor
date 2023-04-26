#include "Collision.h"

int check_collision_racket(Corridor corridor) {
	if(corridor.racket.y-corridor.racket.side < 0.085 + corridor.ball.y && corridor.racket.y+corridor.racket.side > -0.085 + corridor.ball.y 
        && corridor.racket.x-corridor.racket.side < 0.085 - corridor.ball.z && corridor.racket.x+corridor.racket.side > -0.085 - corridor.ball.z) {
        return 1;
    }
    return 0;
}

void collision_racket(Corridor* corridor) {
    if(corridor->ball.x > 0. && corridor->ball.move_x > 0) {
        if(check_collision_racket(*corridor)) {
            corridor->ball.move_x *= -1;
            corridor->ball.move_y = (-(corridor->racket.y - corridor->ball.y) * 4.5) / 40.;
            corridor->ball.move_z = ((corridor->racket.x - corridor->ball.z) * 4.5) / 40.;
        }
        else {
            corridor->ball.move_x = 0;
            corridor->ball.move_y = 0;
            corridor->ball.move_z = 0;
        }
    }
}

void collision_corridor(Corridor* corridor) {
    if(corridor->ball.y < -0.9 || corridor->ball.y > 0.9) {
        corridor->ball.move_y *= -1;
    }
    if(corridor->ball.z < -0.4 || corridor->ball.z > 0.4) {
        corridor->ball.move_z *= -1;
    }
}