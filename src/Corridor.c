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
	corridor->walls[2] = quarter_left_wall(-6.);
	corridor->walls[3] = quarter_right_wall(-6.);
	corridor->walls[4] = half_bottom_wall(-8.);
	corridor->walls[5] = quarter_left_wall(-10.);
	corridor->walls[6] = half_bottom_wall(-10.);
	corridor->walls[7] = third_middle_wall_horizontal(-12.);
	corridor->walls[8] = third_middle_wall_vertical(-12.);
	corridor->number_of_walls = 9;
}

Corridor create_corridor(int nb, int nb_bonus) {
	Corridor corridor;

	corridor = init_corridor();
	level_one(&corridor, 1);

	for(int i = 9; i < nb; i++) {
		corridor.walls[i] = random_wall(-14. - 2. * ((float)i-9.));
	}
	corridor.number_of_walls = nb;

	for(int i = 0; i < nb_bonus; i++) {
		corridor.bonus[i] = random_bonus(-1. + (i * -14.));
	}
	corridor.number_of_bonus = nb_bonus;

	return corridor;
}