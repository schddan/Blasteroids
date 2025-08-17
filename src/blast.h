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
    struct blast *nextBlast; 
};


typedef struct blast blast;

void drawBlast(blast *blast);
void handleActiveBlastsMovement(blast **blastListHead);
void createBlast(blast *blast);
void checkBlastCollision(blast*  blast, asteroid **asteroid, int asteroidQuantity);
void handleBlastList(blast **blastListHead, float positionX, float positionY, float heading);
void removeBlast(blast **blastToRemove);
//The pointer to pointer is needed because 
#endif