#include "Corridor.h"

Corridor init_corridor() {
	Corridor corridor;

	corridor.racket = init_racket(0.15);
    corridor.ball = init_ball();
    corridor.walls = (Wall*) malloc(200 * sizeof(Wall));

    return corridor;
}

void free_corridor(Corridor* corridor) {
	free(corridor->walls);
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