#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "Racket.h"
#include "Ball.h"
#include "Wall.h"
#include "Corridor.h"

/* Check if the Ball colide with the Racket. */
int check_collision_racket(Corridor corridor);

/* Handle the collision of the the Ball with the Racket. */
void collision_racket(Corridor* corridor);

/* Handle the collision of the the Ball with the Corridor. */
void collision_corridor(Corridor* corridor);

/* Handle the collision of the the Ball with the Walls. */
void collision_walls(Corridor* corridor);

#endif