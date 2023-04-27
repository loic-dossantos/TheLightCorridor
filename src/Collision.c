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
            corridor->ball.move_x *= -1;
            corridor->ball.move_y = (-(corridor->racket.y - corridor->ball.y) * 4.5) / 40.;
            corridor->ball.move_z = ((corridor->racket.x - corridor->ball.z) * 4.5) / 40.;
        }
        else {
            corridor->ball.move_x = 0;
            corridor->ball.move_y = 0;
            corridor->ball.move_z = 0;
            corridor->pause = 1;
            corridor->racket.lives--;
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

void collision_racket_wall(Corridor *corridor) {
    for(int i = 0; i < corridor->number_of_walls; i++) {
        Wall wall = corridor->walls[i];
        if(wall.y-(wall.side/2.)*wall.y_scale < 0.085 + corridor->racket.y && wall.y+(wall.side/2.)*wall.y_scale > -0.085 + corridor->racket.y 
            && wall.z-(wall.side/2)*wall.x_scale < 0.085 - corridor->racket.x && wall.z+(wall.side/2.)*wall.x_scale > -0.085 - corridor->racket.x
            && (wall.x - corridor->racket.z) * (wall.x - corridor->racket.z) < 0.02) {
        }
        else {
            move_racket(&(corridor->racket));
            dist_zoom += corridor->racket.move;
            if(dist_zoom < 0) {
                printf("test\n");
                //phy = 90.0f;
                corridor->racket.move = 0.01;
            }
            if(dist_zoom <= 0) {
                phy = 270.0f;
            }
        }
    }
}