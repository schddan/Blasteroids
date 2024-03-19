#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "spaceship.h"
#include "consts.h"

void drawShip(int x, int y, spaceship* spaceship){
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_rotate_transform(&transform, spaceship->heading);
    al_translate_transform(&transform, x, y);
    al_use_transform(&transform);
    al_draw_line(-8,9, 0, -11, spaceship->color, 3.0f);
    al_draw_line(0,-11, 8, 9, spaceship->color, 3.0f);
    al_draw_line(-6,4, -1, 4, spaceship->color, 3.0f);
    al_draw_line(6,4, 1, 4, spaceship->color, 3.0f);
}