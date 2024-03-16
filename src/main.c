#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "spaceship.h"

int main (){

    al_init();
    ALLEGRO_DISPLAY *display = al_create_display(600, 600);
    al_set_window_position(display, 200, 200);

    //spaceship *s = {0.0, 0.0, 2.0, 2.0, 0, {0.0, 255.0, 0, 0}};
    //al_draw_line(-8, 9, 0, -11, s -> color, 3.0f);

}