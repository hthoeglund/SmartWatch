#ifndef NOTES_H
#define	NOTES_H

#include "oled.h"
#include "keypad.h"

// Draws the notes screen
void notes_drawScreen();

// Draws a digit on the notes screen
void notes_drawDigit(char button);

// Clears the last typed character
void notes_clearChar();

// Draws previous notes
void notes_drawPrevious();

// Draws the note selection line
void notes_drawSelectionLine();

// Clears the notes selection line
void notes_clearSelectionLine();

// Clears the current note
void notes_clearCurrentNote();

#endif	/* NOTES_H */

