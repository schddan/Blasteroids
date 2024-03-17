#ifndef _BLAST_H
#define _BLAST_H

#include <allegro5/allegro.h>

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

#endif