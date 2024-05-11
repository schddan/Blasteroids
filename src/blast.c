#include "blast.h"
#include "spaceship.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>

void drawBlast(blast *blast, spaceship *spaceship){
    ALLEGRO_TRANSFORM transform;

    al_identity_transform(&transform);
    al_rotate_transform(&transform, blast->heading);
    al_translate_transform(&transform, blast->sx, blast->sy);
    al_use_transform(&transform);
    //al_draw_filled_circle(0, 0, 5, blast->color);
    al_draw_line(0, 0, 0, -10, al_map_rgb(255, 255, 255), 3);
}

void createBlast(blast *blast){
    blast->sx = 0;
    blast->sy = 0;
    blast->gone = 1;
    blast->speed = 10;
    blast->heading = 1;
    blast->radius = 1;
    blast->color = al_map_rgb(255, 0, 0);
}

void checkBlastCollision(blast*  blast, asteroid *asteroid, int asteroidQuantity){
    float distance;
    for(int i = 0; i < asteroidQuantity; i++){
        distance = sqrt(pow(blast->sx - asteroid[i].sx, 2) + pow(blast->sy - asteroid[i].sy, 2));
        if(distance < blast->radius + asteroid[i].radius && asteroid[i].gone == 0){
            blast->gone = 1;
            asteroid[i].gone = 1;
            divideAsteroid(asteroid, i);
        }
    }
}
