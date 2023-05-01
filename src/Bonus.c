#include "Bonus.h"

Bonus init_bonus(double x, double y, double z, BonusType type) {
	Bonus bonus;

	bonus.x = x;
	bonus.y = y;
	bonus.z = z;
	bonus.type = type;

	return bonus;
}

Bonus random_bonus(double depth) {
	double x, y;

	x = ((rand() % 9) - 4.) / 10.;
	y = ((rand() % 19) - 9.) / 10.;

	switch(rand() % 2) {
		case 0: return init_bonus(x,y,depth,MORELIFE);
		case 1: return init_bonus(x,y,depth,STICKY);
		default: return init_bonus(0,0,0,0);
	}
}