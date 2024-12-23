#ifndef _BLAST_H
#define _BLAST_H

#include <allegro5/allegro.h>
#include "spaceship.h"

struct blast
{
    float sx;
    float sy;
    float heading;
    float speed;
    int gone;
    int radius;
    ALLEGRO_COLOR color;
};

typedef struct blast blast;

void drawBlast(blast *blast);
void createBlast(blast *blast);
void checkBlastCollision(blast*  blast, asteroid *asteroid, int asteroidQuantity);

#endif