#ifndef PIN_H
#define	PIN_H

#include "oled.h"

// Draws the PIN screen
void pin_drawScreen();

// Draws the X (PIN Failure) screen
void pin_drawXScreen();

// Draws the Check (PIN Success) screen
void pin_drawCheckScreen();

// Draws PIN digit
void pin_drawDigit(int num);

// Clears the digit at [index] on the PIN screen
void pin_clearDigit(int index);

#endif	/* PIN_H */

