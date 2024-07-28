#ifndef JOYSTICK_H
#define	JOYSTICK_H

#include "oled.h"
#include "home.h"
#include "notes.h"
#include "reminders.h"

// Read from the joystick
void joystick_read(uint8_t *dest, uint8_t len);

// Resolves joystick inputs
void joystick_resolveInputs();

#endif	/* JOYSTICK_H */

