#include "asteroid.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <time.h>
#include <stdlib.h>
#include "consts.h"
#include <math.h>
#include <stdio.h>

void divideAsteroid(asteroid * asteroidGroup, int rootAsteroidIndex){
    if(rootAsteroidIndex == 0 || rootAsteroidIndex % 7 == 0){
        asteroidGroup[rootAsteroidIndex + 1].gone = 0;
        asteroidGroup[rootAsteroidIndex + 1].sx = asteroidGroup[rootAsteroidIndex].sx + 25;
        asteroidGroup[rootAsteroidIndex + 1].sy = asteroidGroup[rootAsteroidIndex].sy;
        asteroidGroup[rootAsteroidIndex + 1].heading = 1.5;

        asteroidGroup[rootAsteroidIndex + 2].gone = 0;
        asteroidGroup[rootAsteroidIndex + 2].sx = asteroidGroup[rootAsteroidIndex].sx - 25;
        asteroidGroup[rootAsteroidIndex + 2].sy = asteroidGroup[rootAsteroidIndex].sy;
        asteroidGroup[rootAsteroidIndex + 2].heading = -1.5;

    }
}

float RandomFloat(float min, float max){
   return ((max - min) * ((float)rand() / RAND_MAX)) + min;
}

void definePositionAndHeading(asteroid * asteroid){
    int quadrant = rand() % 4 + 1; //random number beetween 1 to 4
    switch (quadrant)
    {
    case 1: //Top
        asteroid->sx = rand() % DISPLAY_WIDTH;
        asteroid->sy = 0;
        asteroid->heading = RandomFloat(3.1, 6.2); //180º to 360º
        break;
    case 2: //Right
        asteroid->sx = DISPLAY_WIDTH;
        asteroid->sy = rand() % DISPLAY_HEIGHT;
        asteroid->heading = RandomFloat(1.5, 4.7); //90º to 270º
        break;
    case 3: //Bottom 
        asteroid->sx = rand() % DISPLAY_WIDTH;
        asteroid->sy = DISPLAY_HEIGHT;
        asteroid->heading = RandomFloat(0, 3.1); //0º to 180º
        break;
    case 4: //Left
        asteroid->sx = 0;
        asteroid->sy = rand() % DISPLAY_HEIGHT;
        asteroid->heading = RandomFloat(1.5, -1.5); //90º to -90º (270º)
        break;
    }
}


void drawAsteroid(asteroid * asteroid){
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_rotate_transform(&transform, asteroid->rotVelocity);
    al_translate_transform(&transform, asteroid->sx, asteroid->sy);
    al_use_transform(&transform);
    //al_draw_filled_circle(0, 0, asteroid->radius, al_premul_rgba(255, 0, 0, 150));
    al_draw_line(-20 * asteroid->scale,20* asteroid->scale, -25* asteroid->scale, 5* asteroid->scale, asteroid->color, 3.0f);
    al_draw_line(-25 * asteroid->scale,5 * asteroid->scale, -25 * asteroid->scale, -10* asteroid->scale, asteroid->color, 3.0f);
    al_draw_line(-25 * asteroid->scale,-10 * asteroid->scale, -5* asteroid->scale, -10* asteroid->scale, asteroid->color, 3.0f);
    al_draw_line(-5 * asteroid->scale, -10 * asteroid->scale, -10* asteroid->scale, -20* asteroid->scale, asteroid->color, 3.0f);
    al_draw_line(-10 * asteroid->scale, -20 * asteroid->scale, 5 * asteroid->scale, -20 * asteroid->scale, asteroid->color, 3.0f);
    al_draw_line(5 * asteroid->scale, -20 * asteroid->scale, 20* asteroid->scale, -10* asteroid->scale, asteroid->color, 3.0f);
    al_draw_line(20 * asteroid->scale, -10* asteroid->scale, 20* asteroid->scale, -5* asteroid->scale, asteroid->color, 3.0f);
    al_draw_line(20 * asteroid->scale,-5 * asteroid->scale, 0* asteroid->scale, -0* asteroid->scale, asteroid->color, 3.0f);
    al_draw_line(0 * asteroid->scale,0* asteroid->scale, 20* asteroid->scale, 10* asteroid->scale, asteroid->color, 3.0f);
    al_draw_line(20 * asteroid->scale,10* asteroid->scale, 10* asteroid->scale, 20* asteroid->scale, asteroid->color, 3.0f);
    al_draw_line(10 * asteroid->scale,20* asteroid->scale, 0* asteroid->scale, 15* asteroid->scale, asteroid->color, 3.0f);
    al_draw_line(0 * asteroid->scale,15* asteroid->scale, -20* asteroid->scale, 20* asteroid->scale, asteroid->color, 3.0f);
    asteroid->sx += asteroid->speed * sin(asteroid->heading);
    asteroid->sy+= asteroid->speed * cos(asteroid->heading);
    asteroid->rotVelocity += 0.05 * asteroid->rotationDirection;
    if(asteroid->sx > DISPLAY_WIDTH || asteroid->sx < 0 || asteroid->sy > DISPLAY_HEIGHT || asteroid -> sy < 0){
        definePositionAndHeading(asteroid);
    }
    
}

asteroid createAsteroid(ALLEGRO_COLOR color, float scale){
    asteroid asteroid;
    definePositionAndHeading(&asteroid);
    int randomDirection = rand() % 2 + 1;
    asteroid.rotationDirection = (randomDirection == 1) ? 1 : -1; //If quadrant == 1, rotationDirection = 1, else rotationDirection = -1
    asteroid.speed = 0.8;
    asteroid.rotVelocity = 0.07;
    asteroid.scale = scale;
    if(scale == 1.0){
        asteroid.gone = 0;
    } else {
        asteroid.gone = 1;
    }
    asteroid.color = color;
    asteroid.radius = 25 * scale;
    return asteroid;
}

asteroid * createAsteroidGroup(int quantity){
    srand(time(NULL));
    float scale;
    int groupCount = 0;
    asteroid* asteroidGroup = (asteroid*)calloc(quantity * 7, sizeof(asteroid));
    for(int i = 0; i < quantity * 7; i++){
        if(groupCount == 0){
            scale = 1.0;
        } else if( groupCount == 1 || groupCount == 2){
            scale = 0.75;
        } else {
            scale = 0.5;
        }
        groupCount++;
        if(groupCount == 7){
            groupCount = 0;
        }
        asteroidGroup[i] = createAsteroid(al_map_rgb(0, 0, 255), scale);
    }
    return asteroidGroup;
}

void checkAsteroidCollision(asteroid *asteroid, int asteroidQuantity){
    float distance;
    for(int i = 0; i < asteroidQuantity; i++){
        for(int j = 0; j < asteroidQuantity; j++){
            if(j == i){
                continue;
            }
            distance = sqrt(pow(asteroid[i].sx - asteroid[j].sx, 2) + pow(asteroid[i].sy - asteroid[j].sy, 2));
            if(distance < asteroid[i].radius + asteroid[j].radius && asteroid[i].gone == 0 && asteroid[j].gone == 0){
                asteroid[i].gone = 1;
                asteroid[j].gone = 1;
                divideAsteroid(asteroid, i);
                divideAsteroid(asteroid, j);
            }
        }
    }
}