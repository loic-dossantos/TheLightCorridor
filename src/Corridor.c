#include "Corridor.h"

Corridor init_corridor() {
	Corridor corridor;

	corridor.racket = init_racket(0.15);
    corridor.ball = init_ball();
    corridor.pause = 0;

    return corridor;
}

void unpause(Corridor* corridor) {
	if(corridor->racket.lives <= 0) {
		printf("GAME OVER\n");
	}
	if(corridor->pause) {
		corridor->pause = 0;
		corridor->ball = init_ball();
		corridor->ball.x = corridor->racket.z -0.179;
		corridor->ball.y = corridor->racket.y;
		corridor->ball.z = -corridor->racket.x;
	}
}

void add_level(Corridor* corridor, int level) {
	for(int i = 0; i < 10; i++) {
		//corridor->walls[i] = random_wall_scale_level(level);	
	}
}

Corridor create_corridor() {
	Corridor corridor;

	corridor = init_corridor();
	add_level(&corridor, 1);

	return corridor;
}