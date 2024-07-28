#ifndef ADC_H
#define	ADC_H

#include "oled.h"
#include "keypad.h"

// Initializes ADC Variables
void initADC();

// Interrupt for ADC
ISR(ADC0_RESRDY_vect);

#endif	/* ADC_H */

