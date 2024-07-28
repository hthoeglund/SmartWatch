#ifndef OLED_H
#define	OLED_H

#include <avr/io.h>
#include <stdlib.h>
#include <stdbool.h>
#include "variables.h"

// Writes two [first, second] bytes to I2C
void oled_I2CwriteDouble(int first, int second);

// Writes a command [command] to I2C using the display's protocol
void oled_I2CwriteCMD(int command);

// Writes a pixel [pixel] to I2C using the display's protocol
void oled_I2CwritePixel(int pixel);

// Initializes the display
void oled_initDisplay();

// Sets the display's cursor to a given index (row, col)
void oled_setCursor(int row, int col);

// Clears the display
void oled_clearDisplay();

// Draws app icon [num] without the surrounding selection box, right shifted by [rightShift]
void oled_drawAppWithoutBox(int num, int rightShift);

// Draws a single small (1-byte) number or calculator symbol (returns -1 if invalid)
int oled_drawSingleSmallNum(char num);

// Draws a single large (2-byte) number at a given location (returns -1 if invalid)
int oled_drawSingleLargeNum(char num, int startingRow, int startingCol);

// Draws a single small letter (returns -1 if invalid)
int oled_drawSingleLetter(char letter);

#endif	/* OLED_H */

