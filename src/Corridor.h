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
	Wall* walls;
} Corridor;

/* Initialise the Corridor. */
Corridor init_corridor();

/* Free the Walls of the Corridor. */
void free_corridor(Corridor* corridor);

/* Add the Walls of one level. */
void add_level(Corridor* corridor, int level);

/* Create a corridor with the first level. */
Corridor create_corridor();

#endif