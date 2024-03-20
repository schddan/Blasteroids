#include "asteroid.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

void drawAsteroid(float x, float y){
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_rotate_transform(&transform, 2);
    al_translate_transform(&transform, x, y);
    al_use_transform(&transform);
    al_draw_line(-20,20, -25, 5, al_map_rgb(255, 255, 255), 3.0f);
    al_draw_line(-25,5, -25, -10, al_map_rgb(255, 255, 255), 3.0f);
    al_draw_line(-25,-10, -5, -10, al_map_rgb(255, 255, 255), 3.0f);
    al_draw_line(-5, -10, -10, -20, al_map_rgb(255, 255, 255), 3.0f);
    al_draw_line(-10, -20, 5, -20, al_map_rgb(255, 255, 255), 3.0f);
    al_draw_line(5, -20, 20, -10, al_map_rgb(255, 255, 255), 3.0f);
    al_draw_line(20, -10, 20, -5, al_map_rgb(255, 255, 255), 3.0f);
    al_draw_line(20,-5, 0, -0, al_map_rgb(255, 255, 255), 3.0f);
    al_draw_line(0,0, 20, 10, al_map_rgb(255, 255, 255), 3.0f);
    al_draw_line(20,10, 10, 20, al_map_rgb(255, 255, 255), 3.0f);
    al_draw_line(10,20, 0, 15, al_map_rgb(255, 255, 255), 3.0f);
    al_draw_line(0,15, -20, 20, al_map_rgb(255, 255, 255), 3.0f);
}