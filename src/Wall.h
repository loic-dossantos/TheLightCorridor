#ifndef __WALL_H__
#define __WALL_H__

#include <stdio.h>
#include <stdlib.h>
#include "WindowConfig.h"

typedef struct {
	double x;
	double y;
	double z;
	double side;
} Wall;

/* Initialise the Wall. */
Wall init_wall(double x, double y, double z, double side);

/* Initialise a random Wall with difficulty scaling with level. */
Wall random_wall_scale_level(int level);

#endif