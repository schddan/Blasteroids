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
    int gone; 
    int radius; //For collision detection
    ALLEGRO_COLOR color;

};

struct asteroidList
{
    struct asteroid * asteroid;
    struct asteroidList *nextAsteroid;
};

typedef struct asteroid asteroid;
typedef struct asteroidList asteroidList;

void divideAsteroidByBlast(asteroid * asteroidGroup, int rootAsteroidIndex);
void drawAsteroid(asteroid * asteroid);
asteroid createAsteroid(ALLEGRO_COLOR color, float scale);
asteroid ** createAsteroidGroup(int quantity);
void freeAsteroidGroup(asteroid **asteroidGroupHeads, int quantity);

#endif

