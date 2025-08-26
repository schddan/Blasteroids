#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <math.h>
#include "spaceship.h"
#include "blast.h"
#include "asteroid.h"
#include "consts.h"
#include <stdio.h>
#include "collisions.h"

void defineTextPosition(float sx, float sy)
{
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_translate_transform(&transform, sx, sy);
    al_use_transform(&transform);
}

int main()
{
    srand(time(NULL));

    // Allegro configs
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_TIMER *timer;
    ALLEGRO_FONT *pointsFont;

    al_init();
    al_init_primitives_addon();
    al_init_ttf_addon();
    al_init_font_addon();

    display = al_create_display(DISPLAY_HEIGHT, DISPLAY_WIDTH);
    queue = al_create_event_queue();
    timer = al_create_timer(1.0 / FPS);
    pointsFont = al_load_font(FONT, 25, 0);

    al_install_keyboard();
    al_install_mouse();

    al_register_event_source(queue, al_get_keyboard_event_source());       // Handles events from keyboard
    al_register_event_source(queue, al_get_mouse_event_source());          // Handles events from mouse
    al_register_event_source(queue, al_get_display_event_source(display)); // Handles events from display
    al_register_event_source(queue, al_get_timer_event_source(timer));     // Handles timer

    // Main game loop
    spaceship *spaceshipGroup[SPACESHIP_LIVES];
    createSpaceshipGroup(spaceshipGroup, SPACESHIP_LIVES);
    int currentSpaceshipIndex = 0;

    blast *blastListHead = NULL; // Initialize the head of the blast list to NULL
    int blastTimer = 0;

    int asteroidQuantity = 6 * 7;
    asteroid *asteroidGroup = createAsteroidGroup(asteroidQuantity);
    int activateAsteroidTimer = ACTIVATE_ASTEROID_INITIAL_TIMER;

    int points = 0;
    float difficultyMultiplier = 0.0; // Increases from 0.0 to 0.5
    int difficultyJustChanged = 0;
    int running = 1;

    al_start_timer(timer);
    while (running)
    {

        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            running = 0;

        ALLEGRO_KEYBOARD_STATE keystate;
        al_get_keyboard_state(&keystate);

        if (event.type == ALLEGRO_EVENT_TIMER)
        {
            if (al_key_down(&keystate, ALLEGRO_KEY_W))
            {
                spaceshipGroup[currentSpaceshipIndex]->sy -= spaceshipGroup[currentSpaceshipIndex]->speed * cos(spaceshipGroup[currentSpaceshipIndex]->heading);
                spaceshipGroup[currentSpaceshipIndex]->sx += spaceshipGroup[currentSpaceshipIndex]->speed * sin(spaceshipGroup[currentSpaceshipIndex]->heading);
            }

            if (al_key_down(&keystate, ALLEGRO_KEY_S))
            {
                spaceshipGroup[currentSpaceshipIndex]->sy += spaceshipGroup[currentSpaceshipIndex]->speed * cos(spaceshipGroup[currentSpaceshipIndex]->heading);
                spaceshipGroup[currentSpaceshipIndex]->sx -= spaceshipGroup[currentSpaceshipIndex]->speed * sin(spaceshipGroup[currentSpaceshipIndex]->heading);
            }

            if (al_key_down(&keystate, ALLEGRO_KEY_A))
            {
                spaceshipGroup[currentSpaceshipIndex]->heading -= 0.07;
            }

            if (al_key_down(&keystate, ALLEGRO_KEY_D))
            {
                spaceshipGroup[currentSpaceshipIndex]->heading += 0.07;
            }

            if (al_key_down(&keystate, ALLEGRO_KEY_SPACE) && blastTimer <= 0)
            {
                blastTimer = BLAST_INITIAL_TIMER;
                handleBlastList(&blastListHead, spaceshipGroup[currentSpaceshipIndex]->sx, spaceshipGroup[currentSpaceshipIndex]->sy, spaceshipGroup[currentSpaceshipIndex]->heading);
            }

            al_clear_to_color(al_map_rgb(0, 0, 0));

            if (activateAsteroidTimer == 0)
            {
                handleAsteroidActivation(&asteroidGroup, &asteroidQuantity);
                activateAsteroidTimer = ACTIVATE_ASTEROID_INITIAL_TIMER - ACTIVATE_ASTEROID_INITIAL_TIMER * difficultyMultiplier;
            }

            if (points % 2000 == 100)
            {
                difficultyJustChanged = false;
            }
            if (points >= 2000 && points % 2000 == 0 && difficultyMultiplier < 0.5 && difficultyJustChanged == false)
            {
                difficultyMultiplier += 0.1;
                difficultyJustChanged = true;
            }

            for (int i = 0; i < asteroidQuantity; i++)
            {
                if (asteroidGroup[i].gone == 0)
                {
                    drawAsteroid(&asteroidGroup[i]);
                }
            }

            handleActiveBlastsMovement(&blastListHead);
            checkSpaceshipCollision(spaceshipGroup[currentSpaceshipIndex], asteroidGroup, asteroidQuantity);
            checkBlastCollision(&blastListHead, asteroidGroup, asteroidQuantity, &points);
            if (spaceshipGroup[currentSpaceshipIndex]->gone != 1)
            {
                drawShip(spaceshipGroup[currentSpaceshipIndex]);
            }
            if (spaceshipGroup[currentSpaceshipIndex]->gone == 1)
            {
                currentSpaceshipIndex++;
                if (currentSpaceshipIndex >= SPACESHIP_LIVES)
                {
                    printf("Game Over!\n");
                    running = 0;
                }
                if (running)
                {
                    spaceshipGroup[currentSpaceshipIndex]->sx = DISPLAY_WIDTH / 2;
                    spaceshipGroup[currentSpaceshipIndex]->sy = DISPLAY_HEIGHT / 2;
                }
            }

            defineTextPosition(12, 17);
            al_draw_textf(pointsFont, al_map_rgb(WHITE_COLOR), 0, 0, 0, "%d", points);
            drawSpaceshipLives(spaceshipGroup, SPACESHIP_LIVES); // The game ends if the spaceship is hit in the spawn because it instantly kills the new spaceships
            blastTimer--;
            activateAsteroidTimer--;
            al_flip_display();
        }
    }

    free(asteroidGroup);
    //  Must free spaceshipGroup too
    al_destroy_display(display);
    al_uninstall_keyboard();
    al_destroy_timer(timer);
    al_destroy_font(pointsFont);

    return 0;
}