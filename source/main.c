#include "variables.h"
#include "init.h"
#include "oled.h"
#include "keypad.h"
#include "buttons.h"
#include "rtc.h"
#include "adc.h"
#include "tca.h"
#include "joystick.h"
#include "pin.h"
#include "home.h"
#include "notes.h"
#include "calculator.h"
#include "simon.h"
#include "reminders.h"

int main() {
    // Call Initialization Functions
    initI2C();
    initRTC();
    initADC();
    initTCA();
    initLEDs();
    initButtons();
    
    // Seed random numbers for Simon Says
    srand(time(NULL));
    
    // Initialize Display
    oled_initDisplay();
    oled_clearDisplay();
    
    // Draw the PIN screen
    pin_drawScreen();
    
    sei();
    while(1);
}