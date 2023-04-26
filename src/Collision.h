#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "Racket.h"
#include "Ball.h"

/* Check if the Ball colide with the Racket. */
int check_collision_racket(Racket racket, Ball ball);

/* Handle the collision of the the Ball with the Racket. */
void collision_racket(Racket* racket, Ball* ball);

/* Handle the collision of the the Ball with the Corridor. */
void collision_corridor(Ball* ball);

#endif