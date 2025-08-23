#ifndef _SPACESHIP_H
#define _SPACESHIP_H

#include <allegro5/allegro.h>
#include "asteroid.h"

struct spaceship
{
    float sx; //Screen x
    float sy; //Screen y
    float heading; //Direction
    float speed; 
    int gone; //Alive?
    int radius; 
    ALLEGRO_COLOR color;
};

typedef struct spaceship spaceship;

void drawShip(spaceship* spaceship);
void createSpaceship(spaceship * spaceship, ALLEGRO_COLOR color, float speed, float positionX, float positionY);
void checkSpaceshipCollision(spaceship *spaceship, asteroid *asteroidGroup, int asteroidQuantity);
void createSpaceshipGroup(spaceship **spaceshipGroup, int quantity);
void drawSpaceshipLives(spaceship **spaceshipGroup, int quantity);

#endif