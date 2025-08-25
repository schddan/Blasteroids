#include "asteroid.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <time.h>
#include <stdlib.h>
#include "consts.h"
#include <math.h>
#include <stdio.h>

float RandomFloat(float min, float max)
{
    return ((max - min) * ((float)rand() / RAND_MAX)) + min;
}

void divideAsteroidByBlast(asteroid *asteroidGroup, int rootAsteroidIndex, int asteroidQuantity)
{
    if (asteroidGroup[rootAsteroidIndex].scale == SMALL_ASTEROID_SCALE)
    {
        return;
    }

    int childrenCreated = 0;

    for (int i = 0; i < asteroidQuantity; i++)
    {
        if (asteroidGroup[i].gone == true)
        {
            asteroidGroup[i].gone = false;
            if (childrenCreated == 0)
            {
                asteroidGroup[i].sx = asteroidGroup[rootAsteroidIndex].sx + 25;
                asteroidGroup[i].sy = asteroidGroup[rootAsteroidIndex].sy;
                asteroidGroup[i].heading = RandomFloat(-45, 45) * 3.141592 / 180;
                childrenCreated++;
                if (asteroidGroup[rootAsteroidIndex].scale == BIG_ASTEROID_SCALE)
                {
                    asteroidGroup[i].scale = MEDIUM_ASTEROID_SCALE;
                }
                else
                {
                    asteroidGroup[i].scale = SMALL_ASTEROID_SCALE;
                }
            }
            else if (childrenCreated == 1)
            {
                asteroidGroup[i].sx = asteroidGroup[rootAsteroidIndex].sx - 25;
                asteroidGroup[i].sy = asteroidGroup[rootAsteroidIndex].sy;
                asteroidGroup[i].heading = RandomFloat(135, 225) * 3.141592 / 180;
                if (asteroidGroup[rootAsteroidIndex].scale == BIG_ASTEROID_SCALE)
                {
                    asteroidGroup[i].scale = MEDIUM_ASTEROID_SCALE;
                }
                else
                {
                    asteroidGroup[i].scale = SMALL_ASTEROID_SCALE;
                }
                break;
            }
        }
    }
}

void definePositionAndHeading(asteroid *asteroid)
{
    int quadrant = rand() % 4 + 1; // random number between 1 to 4
    switch (quadrant)
    {
    case 1: // Top
        asteroid->sx = rand() % DISPLAY_WIDTH;
        asteroid->sy = 0 - asteroid->radius;
        asteroid->heading = RandomFloat(0, 3.1); // 180º to 360º
        break;
    case 2: // Right
        asteroid->sx = DISPLAY_WIDTH + asteroid->radius;
        asteroid->sy = rand() % DISPLAY_HEIGHT;
        asteroid->heading = RandomFloat(1.5, 4.7); // 90º to 270º
        break;
    case 3: // Bottom
        asteroid->sx = rand() % DISPLAY_WIDTH;
        asteroid->sy = DISPLAY_HEIGHT + asteroid->radius;
        asteroid->heading = RandomFloat(3.1, 6.2); // 0º to 180º
        break;
    case 4: // Left
        asteroid->sx = 0 - asteroid->radius;
        asteroid->sy = rand() % DISPLAY_HEIGHT;
        asteroid->heading = RandomFloat(1.5, -1.5); // 90º to -90º (270º)
        break;
    }
}

void drawAsteroid(asteroid *asteroid)
{
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_rotate_transform(&transform, asteroid->rotVelocity);
    al_translate_transform(&transform, asteroid->sx, asteroid->sy);
    al_use_transform(&transform);
    // al_draw_filled_circle(0, 0, asteroid->radius, al_premul_rgba(255, 0, 0, 150));
    al_draw_line(-20 * asteroid->scale, 20 * asteroid->scale, -25 * asteroid->scale, 5 * asteroid->scale, asteroid->color, 2.0f);
    al_draw_line(-25 * asteroid->scale, 5 * asteroid->scale, -25 * asteroid->scale, -10 * asteroid->scale, asteroid->color, 2.0f);
    al_draw_line(-25 * asteroid->scale, -10 * asteroid->scale, -5 * asteroid->scale, -10 * asteroid->scale, asteroid->color, 2.0f);
    al_draw_line(-5 * asteroid->scale, -10 * asteroid->scale, -10 * asteroid->scale, -20 * asteroid->scale, asteroid->color, 2.0f);
    al_draw_line(-10 * asteroid->scale, -20 * asteroid->scale, 5 * asteroid->scale, -20 * asteroid->scale, asteroid->color, 2.0f);
    al_draw_line(5 * asteroid->scale, -20 * asteroid->scale, 20 * asteroid->scale, -10 * asteroid->scale, asteroid->color, 2.0f);
    al_draw_line(20 * asteroid->scale, -10 * asteroid->scale, 20 * asteroid->scale, -5 * asteroid->scale, asteroid->color, 2.0f);
    al_draw_line(20 * asteroid->scale, -5 * asteroid->scale, 0 * asteroid->scale, -0 * asteroid->scale, asteroid->color, 2.0f);
    al_draw_line(0 * asteroid->scale, 0 * asteroid->scale, 20 * asteroid->scale, 10 * asteroid->scale, asteroid->color, 2.0f);
    al_draw_line(20 * asteroid->scale, 10 * asteroid->scale, 10 * asteroid->scale, 20 * asteroid->scale, asteroid->color, 2.0f);
    al_draw_line(10 * asteroid->scale, 20 * asteroid->scale, 0 * asteroid->scale, 15 * asteroid->scale, asteroid->color, 2.0f);
    al_draw_line(0 * asteroid->scale, 15 * asteroid->scale, -20 * asteroid->scale, 20 * asteroid->scale, asteroid->color, 2.0f);
    asteroid->sx += asteroid->speed * cos(asteroid->heading);
    asteroid->sy += asteroid->speed * sin(asteroid->heading);
    asteroid->rotVelocity += 0.05 * asteroid->rotationDirection;
    if (asteroid->sx > DISPLAY_WIDTH + asteroid->radius || asteroid->sx < 0 - asteroid->radius || asteroid->sy > DISPLAY_HEIGHT + asteroid->radius || asteroid->sy < 0 - asteroid->radius)
    {
        definePositionAndHeading(asteroid);
    }
}

asteroid createAsteroid(ALLEGRO_COLOR color, float scale)
{
    asteroid asteroid;
    definePositionAndHeading(&asteroid);
    int randomDirection = rand() % 2 + 1;
    asteroid.rotationDirection = (randomDirection == 1) ? 1 : -1; // If quadrant == 1, rotationDirection = 1, else rotationDirection = -1
    asteroid.speed = 1.6;
    asteroid.rotVelocity = 0.07;
    asteroid.scale = scale;
    asteroid.gone = true;
    asteroid.color = color;
    asteroid.radius = 25 * scale;
    return asteroid;
}

asteroid *createAsteroidGroup(int quantity)
{
    asteroid *asteroidGroup = (asteroid *)calloc(quantity, sizeof(asteroid));
    for (int i = 0; i < quantity; i++)
    {
        asteroidGroup[i] = createAsteroid(al_map_rgb(WHITE_COLOR), BIG_ASTEROID_SCALE);
        if (i < quantity / 7)
        {

            asteroidGroup[i].gone = false;
        }
    }

    return asteroidGroup;
}



void handleAsteroidActivation(asteroid *asteroidGroup, int *pAsteroidQuantity)
{
    int asteroidQuantity = *pAsteroidQuantity;
    int goneCount = 0;
    for (int i = 0; i < asteroidQuantity; i++)
    {
        if (asteroidGroup[i].gone == true)
        {
            goneCount++;
        }
    }
    printf("%i\n", goneCount);

    // printf("%i\n", goneCount);
    int size = rand() % 3 + 1; // random number between 1 to 3
    for (int i = 0; i < asteroidQuantity; i++)
    {
        if (asteroidGroup[i].gone == true)
        {
            asteroidGroup[i].gone = false;
            definePositionAndHeading(&asteroidGroup[i]);
            if (size == 1)
            {
                asteroidGroup[i].scale = SMALL_ASTEROID_SCALE;
            }
            else if (size == 2)
            {
                asteroidGroup[i].scale = MEDIUM_ASTEROID_SCALE;
            }
            else if (size == 3)
            {
                asteroidGroup[i].scale = BIG_ASTEROID_SCALE;
            }
            break;
        }
    }
}
