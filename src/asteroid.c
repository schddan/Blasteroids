#include "asteroid.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <time.h>
#include <stdlib.h>
#include "consts.h"
#include <math.h>



void drawAsteroid(asteroid * asteroid){
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_rotate_transform(&transform, asteroid->rotVelocity);
    al_translate_transform(&transform, asteroid->sx, asteroid->sy);
    al_use_transform(&transform);
    al_draw_line(-20,20, -25, 5, asteroid->color, 3.0f);
    al_draw_line(-25,5, -25, -10, asteroid->color, 3.0f);
    al_draw_line(-25,-10, -5, -10, asteroid->color, 3.0f);
    al_draw_line(-5, -10, -10, -20, asteroid->color, 3.0f);
    al_draw_line(-10, -20, 5, -20, asteroid->color, 3.0f);
    al_draw_line(5, -20, 20, -10, asteroid->color, 3.0f);
    al_draw_line(20, -10, 20, -5, asteroid->color, 3.0f);
    al_draw_line(20,-5, 0, -0, asteroid->color, 3.0f);
    al_draw_line(0,0, 20, 10, asteroid->color, 3.0f);
    al_draw_line(20,10, 10, 20, asteroid->color, 3.0f);
    al_draw_line(10,20, 0, 15, asteroid->color, 3.0f);
    al_draw_line(0,15, -20, 20, asteroid->color, 3.0f);
    asteroid->sx += asteroid->speed * sin(asteroid->heading);
    asteroid->sy+= asteroid->speed * cos(asteroid->heading);
}

asteroid createAsteroid(ALLEGRO_COLOR color){
    asteroid asteroid;
    int quadrant = rand() % 4 + 1; //random number beetween 1 to 4
    switch (quadrant)
    {
    case 1:
        asteroid.sx = rand() % DISPLAY_WIDTH;
        asteroid.sy = 0;
        break;
    case 2:
        asteroid.sx = DISPLAY_WIDTH;
        asteroid.sy = rand() % DISPLAY_HEIGHT;
        break;
    case 3:
        asteroid.sx = rand() % DISPLAY_WIDTH;
        asteroid.sy = DISPLAY_HEIGHT;
        break;
    case 4:
        asteroid.sx = 0;
        asteroid.sy = rand() % DISPLAY_HEIGHT;
        break;
    }
    asteroid.heading = (rand() % 8) - 4;
    asteroid.rotationDirection = 0;
    asteroid.speed = 1;
    asteroid.rotVelocity = 0.07;
    asteroid.scale = 0;
    asteroid.gone = 0;
    asteroid.color = color;
    return asteroid;
}

asteroid * createAsteroidGroup(int quantity){
    srand(time(NULL));
    asteroid* asteroidGroup = (asteroid*)calloc(quantity * 7, sizeof(asteroid));
    for(int i = 0; i < quantity * 7; i++){
        asteroidGroup[i] = createAsteroid(al_map_rgb(0, 0, 255));
    }
    return asteroidGroup;
}