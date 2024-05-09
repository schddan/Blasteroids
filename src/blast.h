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
    ALLEGRO_COLOR color;
};

typedef struct blast blast;

void drawBlast(blast *blast, spaceship *spaceship);
void createBlast(blast *blast);

#endif