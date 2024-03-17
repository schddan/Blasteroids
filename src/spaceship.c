#include <stdio.h>
#include <allegro5/allegro.h>
#include "asteroid.h"

typedef struct spaceship
{
    float sx; //Screen x
    float sy; //Screen y
    float heading; //Direction
    float speed; 
    int gone; //Alive?
    ALLEGRO_COLOR color;
} spaceship;
