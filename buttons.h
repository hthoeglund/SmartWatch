#ifndef BUTTONS_H
#define	BUTTONS_H

#include "oled.h"
#include "pin.h"
#include "home.h"
#include "notes.h"
#include "calculator.h"
#include "simon.h"
#include "reminders.h"

// ISR for Buttons
ISR(PORTA_PORT_vect);

#endif	/* BUTTONS_H */

