#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "spaceship.h"
#include "blast.h"
#include "asteroid.h"

void drawShip(){
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_rotate_transform(&transform, 21);
    al_translate_transform(&transform, 56, 23);
    al_use_transform(&transform);
    al_draw_line(-8,9, 0, -11, al_map_rgb(0, 254, 0), 3.0f);
    al_draw_line(0,-11, 8, 9, al_map_rgb(0, 254, 0), 3.0f);
    al_draw_line(-6,4, -1, 4, al_map_rgb(0, 254, 0), 3.0f);
    al_draw_line(6,4, 1, 4, al_map_rgb(0, 254, 0), 3.0f);

}

int main (){

    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_TIMER *timer;

    al_init();
    al_init_primitives_addon();

    display = al_create_display(600, 600);
    queue = al_create_event_queue();
    timer = al_create_timer( 1.0 / 60 );
    
    al_install_keyboard();

    al_register_event_source(queue, al_get_keyboard_event_source()); //Handles events from keyboard
    al_register_event_source(queue, al_get_display_event_source(display)); //Handles events from display
    al_register_event_source(queue, al_get_timer_event_source(timer));
    
    //Main game loop
    int running = 1;

    al_start_timer(timer);
    while(running){

        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        if(event.type == ALLEGRO_EVENT_KEY_UP || event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            running = 0;
        }

        if(event.type == ALLEGRO_EVENT_TIMER){
            drawShip();
            al_flip_display();
        }
        
    }

    al_destroy_display(display);
    al_uninstall_keyboard();
    al_destroy_timer(timer);

    return 0;
}