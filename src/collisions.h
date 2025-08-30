#ifndef _COLLISIONS_H
#define _COLLISIONS_H

#include <allegro5/allegro.h>
#include "asteroid.h"
#include "consts.h"
#include "spaceship.h"
#include "blast.h"

void checkSpaceshipCollision(spaceship *spaceship, asteroid *asteroidGroup, int asteroidQuantity, int *pSpaceshipInvencibilityTimer, int *pSpaceshipInvencibilityBlinkingFrequency);
void checkBlastCollision(blast **blastListHead, asteroid *asteroidGroup, int asteroidQuantity, int *points);

#endif