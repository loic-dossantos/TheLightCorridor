#include "Racket.h"

Racket init_racket(double side) {
	Racket racket;

	racket.x = 0;
	racket.y = 0;
	racket.z = 0.129;
	racket.side = side;
	racket.lives = 5;
	racket.sticky = 0;

	return racket;
}

void keep_racket_in_window(Racket* racket) {
	racket->x = MAX(racket->x, -0.34);
	racket->y = MAX(racket->y, -0.84);
	racket->x = MIN(racket->x, 0.34);
	racket->y = MIN(racket->y, 0.84);
}

void update_racket(Racket* racket, double x, double y) {
	racket->x = x;
	racket->y = y;
	keep_racket_in_window(racket);
}

void lose_life(Racket *racket) {
	racket->lives--;
}

int is_over(Racket racket) {
	return !(racket.lives);
}