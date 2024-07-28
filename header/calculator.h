#ifndef CALCULATOR_H
#define	CALCULATOR_H

#include "oled.h"
#include "keypad.h"

// Draws the Calculator screen
void calculator_drawScreen();

// Draws the next character on the calculator screen
void calculator_drawDigit(char button);

// Clears the last calculator digit
void calculator_clearDigit();

// Draws the previous equations when re-viewing calculator screen
void calculator_drawPreviousEquations();

// Clears the previous equations
void calculator_clearPreviousEquations();

// Solves the current equation and displays the result
// Returns -1 on error, result on success
long int calculator_solve();

// Clears all equations and solutions
void clearAllEqSols();

#endif	/* CALCULATOR_H */

