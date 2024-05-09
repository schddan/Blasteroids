#include "blast.h"
#include "spaceship.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

void drawBlast(blast *blast, spaceship *spaceship){
    ALLEGRO_TRANSFORM transform;

    al_identity_transform(&transform);
    al_rotate_transform(&transform, blast->heading);
    al_translate_transform(&transform, blast->sx, blast->sy);
    al_use_transform(&transform);
    al_draw_filled_circle(0, 0, 5, blast->color);
}

void createBlast(blast *blast){
    blast->sx = 0;
    blast->sy = 0;
    blast->gone = 1;
    blast->speed = 10;
    blast->heading = 1;
    blast->color = al_map_rgb(255, 0, 0);
}