#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "spaceship.h"
#include "blast.h"
#include "asteroid.h"
#include "consts.h"

int main (){

    //Allegro configs
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_TIMER *timer;

    al_init();
    al_init_primitives_addon();

    display = al_create_display(DISPLAY_HEIGHT, DISPLAY_WIDTH);
    queue = al_create_event_queue();
    timer = al_create_timer( 1.0 / 60 );
    
    al_install_keyboard();
    al_install_mouse();

    al_register_event_source(queue, al_get_keyboard_event_source()); //Handles events from keyboard
    al_register_event_source(queue, al_get_mouse_event_source()); //Handles events from mouse
    al_register_event_source(queue, al_get_display_event_source(display)); //Handles events from display
    al_register_event_source(queue, al_get_timer_event_source(timer));
    
    //Main game loop
    spaceship Spaceship1;
    spaceship* pSpaceship1 = &Spaceship1;
    createSpaceship(pSpaceship1, al_map_rgb(0, 255, 0));

    int running = 1;

    int x = 0, y = 0;
    
    al_start_timer(timer);
    while(running){

        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){ //Handles if the window is closed
            running = 0;
        }

        ALLEGRO_KEYBOARD_STATE keystate;
        al_get_keyboard_state(&keystate);

        if(al_key_down(&keystate, ALLEGRO_KEY_D)){
            x += 1;
        }
        if(al_key_down(&keystate, ALLEGRO_KEY_A)){
            x -= 1;
        }
        if(al_key_down(&keystate, ALLEGRO_KEY_W)){
            y -= 1;
        }
        if(al_key_down(&keystate, ALLEGRO_KEY_S)){
            y += 1;
        }

        if(event.type == ALLEGRO_EVENT_TIMER){
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_line(0, 2, 3, 5, al_map_rgb(255, 255, 255), 3);
            drawShip(x, y, pSpaceship1);
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
            al_flip_display();
            
        }

    }

    al_destroy_display(display);
    al_uninstall_keyboard();
    al_destroy_timer(timer);

    return 0;
}