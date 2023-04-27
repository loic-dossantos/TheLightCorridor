#ifndef __CORRIDOR_H__
#define __CORRIDOR_H__

#include <stdio.h>
#include <stdlib.h>

#include "Racket.h"
#include "Ball.h"
#include "Wall.h"

typedef struct {
	Racket racket;
	Ball ball;
	Wall walls[50];
	int number_of_walls;
	int pause;
} Corridor;

/* Initialise the Corridor. */
Corridor init_corridor();

/* Set pause to 0 and reset the Ball in front of the Racket. */
void unpause(Corridor* corridor);

/* Add the Walls of level one. */
void level_one(Corridor* corridor, int level);

/* Create a corridor with the first level. */
Corridor create_corridor();

#endif