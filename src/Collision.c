#include "Collision.h"
#include "3Dtools.h"

int check_collision_racket(Corridor corridor) {
	if(corridor.racket.y-corridor.racket.side < 0.085 + corridor.ball.y && corridor.racket.y+corridor.racket.side > -0.085 + corridor.ball.y 
        && corridor.racket.x-corridor.racket.side < 0.085 - corridor.ball.z && corridor.racket.x+corridor.racket.side > -0.085 - corridor.ball.z) {
        return 1;
    }
    return 0;
}

void collision_racket(Corridor* corridor) {
    if(corridor->ball.x > 0. && corridor->ball.move_x > 0) {
        if(check_collision_racket(*corridor)) {
            if(corridor->racket.sticky) {
                corridor->ball.move_x = 0.;
                corridor->ball.move_y = 0.;
                corridor->ball.move_z = 0.;
            }
            else {
                corridor->ball.move_x *= -1;
                corridor->ball.move_y = (-(corridor->racket.y - corridor->ball.y) * 4.5) / 40.;
                corridor->ball.move_z = ((corridor->racket.x - corridor->ball.z) * 4.5) / 40.;
            }
        }
        else {
            corridor->ball.move_x = 0;
            corridor->ball.move_y = 0;
            corridor->ball.move_z = 0;
            corridor->pause = 1;
            corridor->racket.lives--;
            corridor->racket.sticky = 0;
        }
    }
}

void collision_corridor(Corridor* corridor) {
    if(corridor->ball.y < -0.9 || corridor->ball.y > 0.9) {
        corridor->ball.move_y *= -1;
    }
    if(corridor->ball.z < -0.4 || corridor->ball.z > 0.4) {
        corridor->ball.move_z *= -1;
    }
}


void collision_walls(Corridor* corridor) {
    for(int i = 0; i < corridor->number_of_walls; i++) {
        Wall wall = corridor->walls[i];
        if(wall.y-(wall.side/2.)*wall.y_scale < 0.085 + corridor->ball.y && wall.y+(wall.side/2.)*wall.y_scale > -0.085 + corridor->ball.y 
            && wall.z-(wall.side/2)*wall.x_scale < 0.085 - corridor->ball.z && wall.z+(wall.side/2.)*wall.x_scale > -0.085 - corridor->ball.z
            && (wall.x - corridor->ball.x) * (wall.x - corridor->ball.x) < 0.02) {
            corridor->ball.move_x *= -1;
        }
    }
}

int check_collision_racket_wall(Corridor *corridor) {
    for(int i = 0; i < corridor->number_of_walls; i++) {
        Wall wall = corridor->walls[i];
        if(wall.y-(wall.side/2.)*wall.y_scale < 0.085 + corridor->racket.y && wall.y+(wall.side/2.)*wall.y_scale > -0.085 + corridor->racket.y 
            && -wall.z-(wall.side/2)*wall.x_scale < 0.085 - corridor->racket.x && -wall.z+(wall.side/2.)*wall.x_scale > -0.085 - corridor->racket.x
            && (wall.x - corridor->racket.z) * (wall.x - corridor->racket.z) < 0.02) {
            return 1;
        }
    }
    return 0;
}

void collision_racket_wall(Corridor *corridor) {
    if(!check_collision_racket_wall(corridor)) {
        corridor->depth += 0.05;
        for(int i = 0; i < corridor->number_of_walls;i++) {
            corridor->walls[i].x += 0.05;
        }
        for(int i = 0; i < corridor->number_of_bonus; i++) {
            corridor->bonus[i].z += 0.05;
        }
        corridor->ball.x += 0.05;
    }
}

void collision_racket_bonus(Corridor *corridor) {
    for(int i = 0; i < corridor->number_of_bonus; i++) {
        Bonus bonus = corridor->bonus[i];
        if(bonus.y < 0.085 + corridor->racket.y && bonus.y > -0.085 + corridor->racket.y 
            && -bonus.x < 0.085 - corridor->racket.x && -bonus.x > -0.085 - corridor->racket.x
            && (bonus.z - corridor->racket.z) * (bonus.z - corridor->racket.z) < 0.02) {
            switch(bonus.type) {
                case MORELIFE: corridor->racket.lives++; break;
                case STICKY: corridor->racket.sticky = 1; break;
            }
            corridor->bonus[i].z = 5;
        }
    }
}