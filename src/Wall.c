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

Wall random_wall(double depth) {
	switch(rand() % 8) {
		case 0: return half_left_wall(depth);
		case 1: return half_right_wall(depth);
		case 2: return half_top_wall(depth);
		case 3: return half_bottom_wall(depth);
		case 4: return quarter_left_wall(depth);
		case 5: return quarter_right_wall(depth);
		case 6: return third_middle_wall_horizontal(depth);
		case 7: return third_middle_wall_vertical(depth);
		default : return half_right_wall(depth);;
	}
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

Wall quarter_left_wall(double depth) {
	return init_wall(depth,-0.75,0.,1.,1.,0.5);
}

Wall quarter_right_wall(double depth) {
	return init_wall(depth,0.75,0.,1.,1.,0.5);
}

Wall third_middle_wall_horizontal(double depth) {
	return init_wall(depth,0.,0.,1.,1.,2./3.);
}

Wall third_middle_wall_vertical(double depth) {
	return init_wall(depth,0.,0.,1.,1./3.,2.);
}