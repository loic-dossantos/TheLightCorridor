#include "Corridor.h"

Corridor init_corridor() {
	Corridor corridor;

	corridor.racket = init_racket(0.15);
    corridor.ball = init_ball();
    corridor.number_of_walls = 0;
    corridor.pause = 0;
    corridor.depth = 0.;

    return corridor;
}

void unpause(Corridor* corridor) {
	if(corridor->racket.lives <= 0) {
		printf("GAME OVER\n");
	}
	if(corridor->pause) {
		corridor->pause = 0;
		corridor->ball = init_ball();
		corridor->ball.x = corridor->racket.z - 0.179;
		corridor->ball.y = corridor->racket.y;
		corridor->ball.z = -corridor->racket.x;
	}
}

void level_one(Corridor* corridor, int level) {
	corridor->walls[0] = half_top_wall(-2.);
	corridor->walls[1] = half_right_wall(-4.);
	corridor->walls[2] = half_left_wall(-6.);
	corridor->walls[3] = half_bottom_wall(-8.);
	corridor->number_of_walls = 4;
}

Corridor create_corridor() {
	Corridor corridor;

	corridor = init_corridor();
	level_one(&corridor, 1);

	return corridor;
}