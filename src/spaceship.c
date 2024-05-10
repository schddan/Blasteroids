#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include "spaceship.h"
#include "consts.h"
void drawShip(spaceship* spaceship){
    ALLEGRO_TRANSFORM transform;
    
    al_identity_transform(&transform);
    al_rotate_transform(&transform, spaceship->heading);
    al_translate_transform(&transform, spaceship->sx, spaceship->sy);
    al_use_transform(&transform);
    al_draw_line(-8,9, 0, -11, spaceship->color, 3.0f);
    al_draw_line(0,-11, 8, 9, spaceship->color, 3.0f);
    al_draw_line(-6,4, -1, 4, spaceship->color, 3.0f);
    al_draw_line(6,4, 1, 4, spaceship->color, 3.0f);
    //al_draw_filled_circle(0, 0, spaceship->radius, al_premul_rgba(255, 0, 0, 150)); 
}

void createSpaceship(spaceship * spaceship, ALLEGRO_COLOR color, float speed){
    spaceship->color = color;
    spaceship->gone = 0;
    spaceship->sx = DISPLAY_WIDTH/2;
    spaceship->sy = DISPLAY_HEIGHT/2;
    spaceship->speed = speed;
    spaceship->heading = 0;
    spaceship->radius = 9;
}

void checkSpaceshipCollision(spaceship *spaceship, asteroid *asteroid, int asteroidQuantity){
    float distance;
    for(int i = 0; i < asteroidQuantity; i++){
        distance = sqrt(pow(spaceship->sx - asteroid[i].sx, 2) + pow(spaceship->sy - asteroid[i].sy, 2));
        if(distance < spaceship->radius + asteroid[i].radius && asteroid[i].gone == 0){
            spaceship->gone = 1;
        }
    }
}

