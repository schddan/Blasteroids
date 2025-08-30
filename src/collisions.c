//The method used for collisions is creating a "circle" with a defined radius around every object (Distance based collision)

#include "collisions.h"
#include "consts.h"
#include "spaceship.h"
#include "asteroid.h"
#include "blast.h"
#include <math.h>

void checkSpaceshipCollision(spaceship *spaceship, asteroid *asteroidGroup, int asteroidQuantity, int *pSpaceshipInvencibilityTimer, int *pSpaceshipInvencibilityBlinkingFrequency)
{
    float distance;
    for (int i = 0; i < asteroidQuantity; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            distance = sqrt(pow(spaceship->sx - asteroidGroup[i].sx, 2) + pow(spaceship->sy - asteroidGroup[i].sy, 2));
            if (distance < spaceship->radius + asteroidGroup[i].radius && asteroidGroup[i].gone == 0 && *pSpaceshipInvencibilityTimer <= 0)
            {
                spaceship->gone = 1;
                *pSpaceshipInvencibilityTimer = SPACESHIP_INVENCIBILITY_INITIAL_TIMER;
                *pSpaceshipInvencibilityBlinkingFrequency = SPACESHIP_INVENCIBILITY_INITIAL_FREQUENCY;
            }
        }
    }
    (*pSpaceshipInvencibilityTimer)--;
}

void checkBlastCollision(blast **blastListHead, asteroid *asteroidGroup, int asteroidQuantity, int *points)
{
    float distance;
    blast *currentBlast = *blastListHead;
    while (currentBlast != NULL)
    {
        for (int i = 0; i < asteroidQuantity; i++)
        {
            distance = sqrt(pow(currentBlast->sx - asteroidGroup[i].sx, 2) + pow(currentBlast->sy - asteroidGroup[i].sy, 2));
            if (distance < currentBlast->radius + asteroidGroup[i].radius && asteroidGroup[i].gone == 0 && currentBlast->gone == 0)
            {
                currentBlast->gone = 1;
                divideAsteroidByBlast(asteroidGroup, i, asteroidQuantity);
                asteroidGroup[i].gone = 1;
                *points += 100;
            }
        }
        currentBlast = currentBlast->nextBlast;
    }
}
