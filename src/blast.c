#include "blast.h"
#include "spaceship.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include "consts.h"
#include <stdio.h>

void drawBlast(blast *blast)
{
    ALLEGRO_TRANSFORM transform;

    al_identity_transform(&transform);
    al_rotate_transform(&transform, blast->heading);
    al_translate_transform(&transform, blast->sx, blast->sy);
    al_use_transform(&transform);
    // al_draw_filled_circle(0, 0, blast->radius, blast->color);
    al_draw_line(0, 0, 0, 10, al_map_rgb(255, 255, 255), 3);
}

void handleActiveBlastsMovement(blast **blastListHead)
{
    if (*blastListHead != NULL)
    {
        blast *currentBlast = *blastListHead;
        while (currentBlast != NULL)
        {
            if (currentBlast->gone != 1)
            {
                currentBlast->sx += currentBlast->speed * sin(currentBlast->heading);
                currentBlast->sy -= currentBlast->speed * cos(currentBlast->heading);
                drawBlast(currentBlast);
                if (currentBlast->sx < 0 || currentBlast->sx > DISPLAY_WIDTH || currentBlast->sy < 0 || currentBlast->sy > DISPLAY_HEIGHT)
                {
                    currentBlast->gone = 1; // Mark blast as gone if it goes out of bounds
                }
                currentBlast = currentBlast->nextBlast;
            }
            else if (currentBlast->gone == 1)
            {
                blast *blastToRemove = currentBlast;
                currentBlast = currentBlast->nextBlast;
                free(blastToRemove);
                *blastListHead = currentBlast;
            }
        }
    }
}

void createBlast(blast *blast)
{
    blast->sx = 0;
    blast->sy = 0;
    blast->gone = 1;
    blast->speed = 10;
    blast->heading = 1;
    blast->radius = 3;
    blast->color = al_map_rgb(255, 0, 0);
    blast->nextBlast = NULL;
}

void handleBlastList(blast **blastListHead, float positionX, float positionY, float heading)
{
    if (*blastListHead == NULL)
    {
        *blastListHead = (blast *)malloc(sizeof(blast));
        createBlast(*blastListHead);
        (*blastListHead)->sx = positionX;
        (*blastListHead)->sy = positionY;
        (*blastListHead)->heading = heading;
        (*blastListHead)->gone = 0;
        (*blastListHead)->nextBlast = NULL;
    }
    else
    {
        blast *currentBlast = *blastListHead;
        while (currentBlast->nextBlast != NULL)
        {
            currentBlast = currentBlast->nextBlast;
        }
        blast *newBlast = (blast *)malloc(sizeof(blast));
        createBlast(newBlast);
        newBlast->sx = positionX;
        newBlast->sy = positionY;
        newBlast->heading = heading;
        newBlast->gone = 0;
        newBlast->nextBlast = NULL;

        currentBlast->nextBlast = newBlast;
    }
}
void removeBlast(blast **blastToRemove)
{
    if (blastToRemove != NULL)
    {

    }
}

void checkBlastCollision(blast *blast, asteroid **asteroid, int asteroidQuantity)
{
    float distance;
    for (int i = 0; i < asteroidQuantity; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            distance = sqrt(pow(blast->sx - asteroid[i][j].sx, 2) + pow(blast->sy - asteroid[i][j].sy, 2));
            if (distance < blast->radius + asteroid[i][j].radius && asteroid[i][j].gone == 0 && blast->gone == 0)
            {
                blast->gone = 1;
                asteroid[i][j].gone = 1;
                divideAsteroidByBlast(asteroid[i], j);
            }
        }
    }
}
