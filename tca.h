#ifndef TCA_H
#define	TCA_H

#include "oled.h"
#include "joystick.h"

// Initialize TCA
void initTCA();

// ISR for TCA (joystick and keypad inputs)
ISR(TCA0_OVF_vect);

#endif	/* TCA_H */

