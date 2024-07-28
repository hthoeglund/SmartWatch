#ifndef SIMON_H
#define	SIMON_H

#include "oled.h"
#include "pin.h"

// Draws the simon screen
void simon_drawScreen();

// Initializes the ordering for a simon game
void simon_initGame();

// Logs an input of [color] with 0 = green, 1 = red, 2 = yellow
void simon_logInput(int color);

#endif	/* SIMON_H */

