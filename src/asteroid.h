#ifndef _ASTEROID_H
#define _ASTEROID_H

#include <allegro5/allegro.h>

struct asteroid
{
    float sx;
    float sy;
    float heading; //Direction
    int rotationDirection;
    float speed; 
    float rotVelocity; //Rotation velocity per frame
    float scale; //Factor to change sizes
    int gone; //Gone?
    int radius; //For collision detection
    ALLEGRO_COLOR color;
};

struct asteroidList
{
    struct asteroid * asteroid;
    struct asteroidList * next1;
    struct asteroidList * next2;
};

typedef struct asteroid asteroid;

void divideAsteroidByBlast(asteroid * asteroidGroup, int rootAsteroidIndex);
void drawAsteroid(asteroid * asteroid);
asteroid createAsteroid(ALLEGRO_COLOR color, float scale);
asteroid ** createAsteroidGroup(int quantity);
void checkAsteroidCollision(asteroid *asteroid, int asteroidQuantity);
void freeAsteroidGroup(asteroid **asteroidGroupHeads, int quantity);

#endif

