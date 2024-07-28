#include "init.h"

void initI2C() {
    // Set Display SDA and SCL pins as output
    PORTA.DIRSET |= PIN2_bm | PIN3_bm;
    
    // Clear MSTATUS (write 1 to flags). BUSSTATE set to idle
    TWI0.MSTATUS = TWI_RIF_bm | TWI_WIF_bm | TWI_RXACK_bm | TWI_BUSSTATE_IDLE_gc;
    
    // Set baud rate
    TWI0.MBAUD = 10;
    
    //[No ISRs] and Host Mode
    TWI0.MCTRLA = TWI_ENABLE_bm; 
}

void initButtons(){
    // Set button pins as input (good practice)
    PORTA.DIR &= ~PIN4_bm;
    PORTA.DIR &= ~PIN5_bm;
    PORTA.DIR &= ~PIN6_bm;
    PORTA.DIR &= ~PIN7_bm;
    
    // Enable pull-up resistors for buttons, with rising (letting go) firing interrupts
    PORTA.PIN4CTRL |= PORT_PULLUPEN_bm | PORT_ISC_RISING_gc;
    PORTA.PIN5CTRL |= PORT_PULLUPEN_bm | PORT_ISC_RISING_gc;
    PORTA.PIN6CTRL |= PORT_PULLUPEN_bm | PORT_ISC_RISING_gc;
    PORTA.PIN7CTRL |= PORT_PULLUPEN_bm | PORT_ISC_RISING_gc;
}

void initLEDs(){
    // Set LED pins as output
    PORTC.DIR |= PIN0_bm | PIN1_bm;
    PORTD.DIR |= PIN1_bm;
}
