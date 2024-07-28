#ifndef KEYPAD_H
#define	KEYPAD_H

#include "oled.h"
#include "pin.h"
#include "notes.h"
#include "calculator.h"
#include "reminders.h"

// Retrieves the oldest button press
uint8_t keypad_getButton();

// Updates the FIFO queue needed to use the keypad
void keypad_updateFIFO();

// Clears one button press, returning the button
uint8_t keypad_clearFIFO();

// Resolves keypad inputs
void keypad_resolveInputs();

// Resolves keypad inputs when on the PIN screen
void keypad_resolvePINInput();
// Resolves keypad inputs when on the notes screen
void keypad_resolveNotesInput();
// Resolves keypad inputs when on the calculator screen
void keypad_resolveCalculatorInput();
// Resolves keypad inputs when on the reminders screen
void keypad_resolveRemindersInput();

#endif	/* KEYPAD_H */

