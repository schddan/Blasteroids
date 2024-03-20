#ifndef _SPACESHIP_H
#define _SPACESHIP_H

#include <allegro5/allegro.h>

struct spaceship
{
    float sx; //Screen x
    float sy; //Screen y
    float heading; //Direction
    float speed; 
    int gone; //Alive?
    ALLEGRO_COLOR color;
};

typedef struct spaceship spaceship;

void drawShip(int x, int y, spaceship* spaceship);
void createSpaceship(spaceship * spaceship, ALLEGRO_COLOR color);

#endif