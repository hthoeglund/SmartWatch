#include "reminders.h"

void reminders_drawScreen(){
    displayingRemindersScreen = true;
    
    // Draw logo
    oled_drawAppWithoutBox(3, 52);
    
    // Draw previous reminders
    reminders_drawPrevious();
    
    // Draw modes/clock
    if(settingReminderMode){
        reminders_drawModes();
    }
    else if(settingReminderTime || reminderRunning || reminderFinished || reminderAlerting){
        reminders_drawModes();
        reminders_drawClock();
    }
    
    // Draw running/finished
    if(reminderRunning){
        reminders_drawRunning();
    }
    else if(reminderFinished){
        reminders_drawFinished();
    }
}

void reminders_drawPrevious(){
    // For each reminder character
    for(int c = 0; c < 13; c++){
        oled_setCursor(0, 0 + 4*c);

        // Draw character
        if(oled_drawSingleSmallNum(reminders[c]) != 0){
            oled_drawSingleLetter(reminders[c]);
        }
    }
}

void reminders_drawDigit(char button){
    // If there are 13 digits, cannot place a new digit
    if(currentReminderDigit > 12){
        return;
    }
    
    // Set cursor
    oled_setCursor(0, 0 + 4*currentReminderDigit);
    
    // If * was the last button pressed
    if(reminderADCLastPressed){
        // Disable ADC
        ADC0.INTCTRL &= ~ADC_RESRDY_bm;

        // Increment digit and cursor
        currentReminderDigit++;
        oled_setCursor(0, 0 + 4*currentReminderDigit);

        // Reset ADCLastPressed variable
        reminderADCLastPressed = false;
    }
    
    // If # pressed
    if(button == '#'){  
        // Draw symbol corresponding to reminderCycleNum
        oled_drawSingleSmallNum(reminderCycle[reminderCycleNum]);
            
        // Update reminder string
        reminders[currentReminderDigit] = reminderCycle[reminderCycleNum];
        
        // If reminderCycleNum is at the end, reset it
        if(reminderCycleNum == 7){
            // Reset cycle to beginning for next digit
            reminderCycleNum = -1;
        }
        
        // Iterate to next cycle num, and # is last button pressed
        reminderCycleNum++;
        reminderCycleLastPressed = true;
    }
    else{
        // If # was the last button pressed,
        if(reminderCycleLastPressed){
            // Increment digit and cursor
            currentReminderDigit++;
            oled_setCursor(0, 0 + 4*currentReminderDigit);
            
            // Reset cycle variables
            reminderCycleLastPressed = false;
            reminderCycleNum = 0;
        }

        // If button is a '*'
        if(button == '*'){
            // ADC button is last pressed
            reminderADCLastPressed = true;
            
            // Enable ADC
            ADC0.INTCTRL |= ADC_RESRDY_bm;
        }
        else{
            // Adjust reminder string accordingly
            reminders[currentReminderDigit] = button;

            // Draw Number
            oled_drawSingleSmallNum(button);

            // Iterate to next digit
            currentReminderDigit++;
        }
    }
}

void reminders_clearChar(){
    // If cycle was last pressed
    if(reminderCycleLastPressed){
        // Reset cycle variables
        reminderCycleLastPressed = false;
        reminderCycleNum = 0;
        currentReminderDigit--;
    }
    // Else if ADC was last pressed
    else if(reminderADCLastPressed){
        // Disable ADC
        ADC0.INTCTRL &= ~ADC_RESRDY_bm;
    }
    // Otherwise, reverse 1 digit
    else{
        currentReminderDigit--;
    }
    
    // If there is not anything to delete
    if(currentReminderDigit < 0){
        return;
    }
    
    // Clear char in reminder string
    reminders[currentReminderDigit] = '\0';
    
    // Clear three rows
    oled_setCursor(0, 0 + 4*currentReminderDigit);
    oled_I2CwritePixel(0b00000000);
    oled_I2CwritePixel(0b00000000);
    oled_I2CwritePixel(0b00000000);
    
    // If ADC was last pressed, decrement digit afterwards
    if(reminderADCLastPressed){
        currentReminderDigit--;
    }
}

void reminders_drawModes(){
    // If in timer mode
    if(selectedReminderMode == 0){
        // Timer
        oled_setCursor(1, 0);
        // T with box
        oled_I2CwritePixel(0b11111111);
        oled_I2CwritePixel(0b10000001);
        oled_I2CwritePixel(0b10000101);
        oled_I2CwritePixel(0b10111101);
        oled_I2CwritePixel(0b10000101);
        oled_I2CwritePixel(0b10000001);
        // I with box
        oled_I2CwritePixel(0b10100101);
        oled_I2CwritePixel(0b10111101);
        oled_I2CwritePixel(0b10100101);
        oled_I2CwritePixel(0b10000001);
        // M with box
        oled_I2CwritePixel(0b10111101);
        oled_I2CwritePixel(0b10001001);
        oled_I2CwritePixel(0b10111101);
        oled_I2CwritePixel(0b10000001);
        // E with box
        oled_I2CwritePixel(0b10111101);
        oled_I2CwritePixel(0b10110101);
        oled_I2CwritePixel(0b10100101);
        oled_I2CwritePixel(0b10000001);
        // R with box
        oled_I2CwritePixel(0b10111101);
        oled_I2CwritePixel(0b10010101);
        oled_I2CwritePixel(0b10101101);
        oled_I2CwritePixel(0b10000001);
        oled_I2CwritePixel(0b11111111);
        
        // Clock
        oled_setCursor(2, 2);
        // C without box
        oled_I2CwritePixel(0b00111100);
        oled_I2CwritePixel(0b00100100);
        oled_I2CwritePixel(0b00100100);
        oled_I2CwritePixel(0b00000000);
        // L without box
        oled_I2CwritePixel(0b00111100);
        oled_I2CwritePixel(0b00100000);
        oled_I2CwritePixel(0b00100000);
        oled_I2CwritePixel(0b00000000);
        // O without box
        oled_I2CwritePixel(0b00111100);
        oled_I2CwritePixel(0b00100100);
        oled_I2CwritePixel(0b00111100);
        oled_I2CwritePixel(0b00000000);
        // C without box
        oled_I2CwritePixel(0b00111100);
        oled_I2CwritePixel(0b00100100);
        oled_I2CwritePixel(0b00100100);
        oled_I2CwritePixel(0b00000000);
        // K without box
        oled_I2CwritePixel(0b00111100);
        oled_I2CwritePixel(0b00011000);
        oled_I2CwritePixel(0b00101100);
    }
    // If in clock mode
    else{
        // Timer
        oled_setCursor(1, 2);
        // T without box
        oled_I2CwritePixel(0b00000100);
        oled_I2CwritePixel(0b00111100);
        oled_I2CwritePixel(0b00000100);
        oled_I2CwritePixel(0b00000000);
        // I without box
        oled_I2CwritePixel(0b00100100);
        oled_I2CwritePixel(0b00111100);
        oled_I2CwritePixel(0b00100100);
        oled_I2CwritePixel(0b00000000);
        // M without box
        oled_I2CwritePixel(0b00111100);
        oled_I2CwritePixel(0b00001000);
        oled_I2CwritePixel(0b00111100);
        oled_I2CwritePixel(0b00000000);
        // E without box
        oled_I2CwritePixel(0b00111100);
        oled_I2CwritePixel(0b00110100);
        oled_I2CwritePixel(0b00100100);
        oled_I2CwritePixel(0b00000000);
        // R without box
        oled_I2CwritePixel(0b00111100);
        oled_I2CwritePixel(0b00010100);
        oled_I2CwritePixel(0b00101100);
        
        oled_setCursor(2, 0);
        oled_I2CwritePixel(0b11111111);
        oled_I2CwritePixel(0b10000001);
        // C with box
        oled_I2CwritePixel(0b10111101);
        oled_I2CwritePixel(0b10100101);
        oled_I2CwritePixel(0b10100101);
        oled_I2CwritePixel(0b10000001);
        // L with box
        oled_I2CwritePixel(0b10111101);
        oled_I2CwritePixel(0b10100001);
        oled_I2CwritePixel(0b10100001);
        oled_I2CwritePixel(0b10000001);
        // O with box
        oled_I2CwritePixel(0b10111101);
        oled_I2CwritePixel(0b10100101);
        oled_I2CwritePixel(0b10111101);
        oled_I2CwritePixel(0b10000001);
        // C with box
        oled_I2CwritePixel(0b10111101);
        oled_I2CwritePixel(0b10100101);
        oled_I2CwritePixel(0b10100101);
        oled_I2CwritePixel(0b10000001);
        // K with box
        oled_I2CwritePixel(0b10111101);
        oled_I2CwritePixel(0b10011001);
        oled_I2CwritePixel(0b10101101);
        oled_I2CwritePixel(0b10000001);
        oled_I2CwritePixel(0b11111111);
    }
}

void reminders_clearModes(){
    // Clear timer mode text
    oled_setCursor(1, 0);
    for(int i = 0; i < 24; i++){
        oled_I2CwritePixel(0b00000000);
    }
    
    // Clear clock mode text
    oled_setCursor(2, 0);
    for(int i = 0; i < 24; i++){
        oled_I2CwritePixel(0b00000000);
    }
}

void reminders_drawClock(){
    // If in timer mode, display mins/secs
    if(selectedReminderMode == 0){
        // Colon
        oled_setCursor(3, 14);
        oled_I2CwritePixel(0b01100000);
        oled_I2CwritePixel(0b01100000);
        oled_setCursor(4, 14);
        oled_I2CwritePixel(0b00001100);
        oled_I2CwritePixel(0b00001100);
        
        // Only display entered digits
        if(currentReminderClockDigit > 3){
            oled_drawSingleLargeNum((reminderMins / 10 + '0'), 3, 0);
            oled_drawSingleLargeNum((reminderMins % 10 + '0'), 3, 7);
            oled_drawSingleLargeNum((reminderSecs / 10 + '0'), 3, 18);
            oled_drawSingleLargeNum((reminderSecs % 10 + '0'), 3, 25);
        }
        else if(currentReminderClockDigit == 3){
            oled_drawSingleLargeNum((reminderMins / 10 + '0'), 3, 0);
            oled_drawSingleLargeNum((reminderMins % 10 + '0'), 3, 7);
            oled_drawSingleLargeNum((reminderSecs / 10 + '0'), 3, 18);
            oled_drawSingleLargeNum('_', 3, 25);
        }
        else if(currentReminderClockDigit == 2){
            oled_drawSingleLargeNum((reminderMins / 10 + '0'), 3, 0);
            oled_drawSingleLargeNum((reminderMins % 10 + '0'), 3, 7);
            oled_drawSingleLargeNum('_', 3, 18);
            oled_drawSingleLargeNum('_', 3, 25);
        }
        else if(currentReminderClockDigit == 1){
            oled_drawSingleLargeNum((reminderMins / 10 + '0'), 3, 0);
            oled_drawSingleLargeNum('_', 3, 7);
            oled_drawSingleLargeNum('_', 3, 18);
            oled_drawSingleLargeNum('_', 3, 25);
        }
        else{
            oled_drawSingleLargeNum('_', 3, 0);
            oled_drawSingleLargeNum('_', 3, 7);
            oled_drawSingleLargeNum('_', 3, 18);
            oled_drawSingleLargeNum('_', 3, 25);
        }
    }
    // Else, in clock mode, display hours/mins
    else{
        oled_setCursor(3, 14);
        oled_I2CwritePixel(0b01100000);
        oled_I2CwritePixel(0b01100000);
        oled_setCursor(4, 14);
        oled_I2CwritePixel(0b00001100);
        oled_I2CwritePixel(0b00001100);
        
        // Only display entered digits
        if(currentReminderClockDigit > 3){
            oled_drawSingleLargeNum((reminderHours / 10 + '0'), 3, 0);
            oled_drawSingleLargeNum((reminderHours % 10 + '0'), 3, 7);
            oled_drawSingleLargeNum((reminderMins / 10 + '0'), 3, 18);
            oled_drawSingleLargeNum((reminderMins % 10 + '0'), 3, 25);
        }
        else if(currentReminderClockDigit == 3){
            oled_drawSingleLargeNum((reminderHours / 10 + '0'), 3, 0);
            oled_drawSingleLargeNum((reminderHours % 10 + '0'), 3, 7);
            oled_drawSingleLargeNum((reminderMins / 10 + '0'), 3, 18);
            oled_drawSingleLargeNum('_', 3, 25);
        }
        else if(currentReminderClockDigit == 2){
            oled_drawSingleLargeNum((reminderHours / 10 + '0'), 3, 0);
            oled_drawSingleLargeNum((reminderHours % 10 + '0'), 3, 7);
            oled_drawSingleLargeNum('_', 3, 18);
            oled_drawSingleLargeNum('_', 3, 25);
        }
        else if(currentReminderClockDigit == 1){
            oled_drawSingleLargeNum((reminderHours / 10 + '0'), 3, 0);
            oled_drawSingleLargeNum('_', 3, 7);
            oled_drawSingleLargeNum('_', 3, 18);
            oled_drawSingleLargeNum('_', 3, 25);
        }
        else{
            oled_drawSingleLargeNum('_', 3, 0);
            oled_drawSingleLargeNum('_', 3, 7);
            oled_drawSingleLargeNum('_', 3, 18);
            oled_drawSingleLargeNum('_', 3, 25);
        }
    }
}

void reminders_clearClock(){
    // Clear timer mode text
    oled_setCursor(3, 0);
    for(int i = 0; i < 34; i++){
        oled_I2CwritePixel(0b00000000);
    }
    oled_setCursor(4, 0);
    for(int i = 0; i < 34; i++){
        oled_I2CwritePixel(0b00000000);
    }
}

void reminders_drawAlert(){
    // For each reminder character
    for(int c = 0; c < 13; c++){
        oled_setCursor(5, 0 + 4*c);

        // Draw character
        if(oled_drawSingleSmallNum(reminders[c]) != 0){
            oled_drawSingleLetter(reminders[c]);
        }
    }
}

void reminders_clearAlert(){
    // Clear entire bottom section
    oled_setCursor(5, 0);
    for(int i = 0; i < 51; i++){
        oled_I2CwritePixel(0b00000000);
    }
}

void reminders_drawRunning(){
    oled_setCursor(5, 52);
    oled_drawSingleLetter('r');
    oled_I2CwritePixel(0b00000000);
    oled_drawSingleLetter('u');
    oled_I2CwritePixel(0b00000000);
    oled_drawSingleLetter('n');
}

void reminders_drawFinished(){
    oled_setCursor(5, 52);
    oled_drawSingleLetter('f');
    oled_I2CwritePixel(0b00000000);
    oled_drawSingleLetter('i');
    oled_I2CwritePixel(0b00000000);
    oled_drawSingleLetter('n');
}