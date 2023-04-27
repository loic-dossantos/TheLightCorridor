#include "Wall.h"

Wall init_wall(double x, double y, double z, double side, double x_scale, double y_scale) {
	Wall wall;

	wall.x = x;
	wall.y = y;
	wall.z = z;
	wall.side = side;
	wall.x_scale = x_scale;
	wall.y_scale = y_scale;

	return wall;
}

Wall random_wall_scale_level(int level) {
	return init_wall(0.5,0.5,0.5,1.,1.,1.);
}

Wall half_left_wall(double depth) {
	return init_wall(depth,-0.5,0.,1.,1.,1.);
}

Wall half_right_wall(double depth) {
	return init_wall(depth,0.5,0.,1.,1.,1.);
}


Wall half_top_wall(double depth) {
	return init_wall(depth,0.,-0.25,1.,0.5,2.);
}

Wall half_bottom_wall(double depth) {
	return init_wall(depth,0.,0.25,1.,0.5,2.);
}