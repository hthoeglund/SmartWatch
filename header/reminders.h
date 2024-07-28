#ifndef REMINDERS_H
#define	REMINDERS_H

#include "oled.h"
#include "keypad.h"

// Draws the reminders screen
void reminders_drawScreen();

// Draws previous reminder
void reminders_drawPrevious();

// Draws a digit on the reminders screen
void reminders_drawDigit(char button);

// Clears the last typed character
void reminders_clearChar();

// Draws the reminder mode options
void reminders_drawModes();

// Clears the reminder mode options
void reminders_clearModes();

// Draws the reminder clock
void reminders_drawClock();

// Clears the reminder clock
void reminders_clearClock();

// Draws a reminder alert
void reminders_drawAlert();

// Clears a reminder alert
void reminders_clearAlert();

// Draws indicator that reminder is running
void reminders_drawRunning();

// Draws indicator that reminder is finished
void reminders_drawFinished();

#endif	/* REMINDERS_H */

