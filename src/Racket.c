#include "Racket.h"

Racket init_racket(double side) {
	Racket racket;

	racket.x = 0;
	racket.y = 0;
	racket.side = side;
	racket.lives = 5;

	return racket;
}

void keep_racket_in_window(Racket* racket) {
	racket->x = MAX(racket->x, (-GL_VIEW_SIZE / 2.) * aspectRatio + (racket->side / 2.));
	racket->y = MAX(racket->y, (-GL_VIEW_SIZE / 2. + racket->side / 2.));
	racket->x = MIN(racket->x, (GL_VIEW_SIZE / 2.) * aspectRatio - (racket->side / 2.));
	racket->y = MIN(racket->y, (GL_VIEW_SIZE / 2. - racket->side / 2.));
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