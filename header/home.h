#ifndef HOME_H
#define	HOME_H

#include "oled.h"

// Draws the home screen
void home_drawScreen();

// Draws app icon [num] without the surrounding selection box, in home screen placement
// Also clears the selection box in doing so
void home_drawAppWithoutBox(int num);

// Draws current home screen app with the surrounding selection box
void home_drawCurrentAppBox();

#endif	/* HOME_H */

