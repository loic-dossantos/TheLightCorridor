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
	double x_scale;
	double y_scale;
} Wall;

/* Initialise the Wall. */
Wall init_wall(double x, double y, double z, double side, double x_scale, double y_scale);

/* Initialise a random Wall. */
Wall random_wall(double depth);

Wall half_left_wall(double depth);

Wall half_right_wall(double depth);

Wall half_top_wall(double depth);

Wall half_bottom_wall(double depth);

Wall quarter_left_wall(double depth);

Wall quarter_right_wall(double depth);

Wall third_middle_wall_horizontal(double depth);

Wall third_middle_wall_vertical(double depth);

#endif