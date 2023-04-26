#include "Wall.h"

Wall init_wall(double x, double y, double z, double side) {
	Wall wall;

	wall.x = x;
	wall.y = y;
	wall.z = z;
	wall.side = side;

	return wall;
}

Wall random_wall_scale_level(int level) {
	return init_wall(0.5,0.5,0.5,1.);
}