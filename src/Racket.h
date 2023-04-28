#ifndef __RACKET_H__
#define __RACKET_H__

#include <stdio.h>
#include "WindowConfig.h"

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

typedef struct {
	double x;
	double y;
	double z;
	double side;
	int lives;
} Racket;

/* Initialise the Racket. */
Racket init_racket(double side);

/* Constrains the Racket in the Window. */
void keep_racket_in_window(Racket* racket);

/* Update position of the Racket in the Window and use keep_racket_in_window */
void update_racket(Racket* racket, double x, double y);

/* Lose a life. */
void lose_life(Racket *racket);

/* Return 0 if the racket still has lives,
 * Return 1 otherwise. */
int is_over(Racket racket);

#endif