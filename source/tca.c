#include "tca.h"

void initTCA() {
    // Enable overflow interrupt
    TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;

    // Set to normal mode
    TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_NORMAL_gc;

    // Disable event counting
    TCA0.SINGLE.EVCTRL &= ~(TCA_SINGLE_CNTEI_bm);

    // Set the period
    TCA0.SINGLE.PER = 41666;

    // Start timer
    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV4_gc | TCA_SINGLE_ENABLE_bm;
}

ISR(TCA0_OVF_vect){
    // Resolve Joystick inputs
    joystick_resolveInputs();
    
    // Resolve Keypad inputs
    keypad_resolveInputs();
    
    // Clear the interrupt flag
    TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}
