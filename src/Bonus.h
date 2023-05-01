#ifndef __BONUS_H__
#define __BONUS_H__

#include <stdio.h>
#include <stdlib.h>

typedef enum {
	MORELIFE,
	STICKY
} BonusType;

typedef struct {
	double x;
	double y;
	double z;
	BonusType type;
} Bonus;

/* Initialize a Bonus. */
Bonus init_bonus(double x, double y, double z, BonusType type);

/* Create a Bonus with random coordonates and random type. */
Bonus random_bonus(double depth);

#endif