#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include "spaceship.h"
#include "consts.h"
void drawShip(spaceship *spaceship)
{
    ALLEGRO_TRANSFORM transform;

    al_identity_transform(&transform);
    al_rotate_transform(&transform, spaceship->heading);
    al_translate_transform(&transform, spaceship->sx, spaceship->sy);
    al_use_transform(&transform);
    al_draw_line(-8, 9, 0, -11, spaceship->color, 1.0f);
    al_draw_line(0, -11, 8, 9, spaceship->color, 1.0f);
    al_draw_line(-6, 4, -1, 4, spaceship->color, 1.0f);
    al_draw_line(6, 4, 1, 4, spaceship->color, 1.0f);
}

void createSpaceship(spaceship *spaceship, ALLEGRO_COLOR color, float speed, float positionX, float positionY)
{
    spaceship->color = color;
    spaceship->gone = 0;
    spaceship->sx = positionX;
    spaceship->sy = positionY;
    spaceship->speed = speed;
    spaceship->heading = 0;
    spaceship->radius = 9;
}



void createSpaceshipGroup(spaceship *spaceshipGroup, int quantity)
{
    for (int i = 0; i < quantity; i++)
    {
        if (i == 0)
        {
            createSpaceship(&(spaceshipGroup[i]), al_map_rgb(SPACESHIP_COLOR), 2, DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2);
        }
        else
        {
            createSpaceship(&(spaceshipGroup[i]), al_map_rgb(SPACESHIP_COLOR), 2, 80 - (i - 1) * 30, 70);
        }
    }
}

void drawSpaceshipLives(spaceship *spaceshipGroup, int quantity, int currentSpaceshipIndex)
{
    for (int i = currentSpaceshipIndex + 1; i < SPACESHIP_LIVES; i++){
        if(!spaceshipGroup[i].gone)
            drawShip(&(spaceshipGroup[i]));

    }
}