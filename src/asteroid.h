#ifndef _ASTEROID_H
#define _ASTEROID_H

#include <allegro5/allegro.h>

struct asteroid
{
    float sx;
    float sy;
    float heading; //Direction
    float twist; //Current rotation
    float speed; 
    float rotVelocity; //Rotation velocity per frame
    float scale; //Factor to change sizes
    int gone; //Gone?
    ALLEGRO_COLOR color;
};

typedef struct asteroid asteroid;

void drawAsteroid(float x, float y);

#endif

