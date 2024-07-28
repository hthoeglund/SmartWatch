#include "keypad.h"

uint8_t keypad_getButton(){
    uint8_t dest[1];
    
    // Send I2C Address with a write bit
    TWI0.MADDR = (0x4B << 1) | 0;
    
    // Wait for write
    while (!(TWI0.MSTATUS & TWI_WIF_bm));
    
    // Write the KEYPAD_BUTTON register to I2C
    TWI0.MDATA = 0x03;
    
    // Wait for write
    while (!(TWI0.MSTATUS & TWI_WIF_bm));
    
    // Restart
    TWI0.MCTRLB = TWI_MCMD_REPSTART_gc;
    
    // Send Address with a read bit
    TWI0.MADDR = (0x4B << 1) | 1;
    
    // Release the clock hold
    TWI0.MSTATUS = TWI_CLKHOLD_bm;
    
    // Wait for data to read
    while (!(TWI0.MSTATUS & TWI_RIF_bm));
    
    // Store data byte
    dest[0] = TWI0.MDATA;
    
    // NACK and STOP the bus
    TWI0.MCTRLB = TWI_ACKACT_NACK_gc | TWI_MCMD_STOP_gc;

    // Return data byte
    return dest[0];
}

void keypad_updateFIFO(){
    // Send I2C Address with a write bit
    TWI0.MADDR = (0x4B << 1) | 0;
    
    // Wait for write
    while (!(TWI0.MSTATUS & TWI_WIF_bm));

    // Write the KEYPAD_UPDATE_FIFO register to I2C
    TWI0.MDATA = 0x06;
    
    // Wait for write
    while (!(TWI0.MSTATUS & TWI_WIF_bm));

    // Write 0x01 to the register
    TWI0.MDATA = 0x01;
    
    // Wait for write
    while (!(TWI0.MSTATUS & TWI_WIF_bm));
        
    // NACK and STOP the bus
    TWI0.MCTRLB = TWI_ACKACT_NACK_gc | TWI_MCMD_STOP_gc;
}

uint8_t keypad_clearFIFO(){
    // Update the queue and then read in a keypad press
    keypad_updateFIFO();
    char button = keypad_getButton();
    
    // If a valid button was pressed, return it
    if(button != 0){
        return button;
    }
    return 0;
}

void keypad_resolveInputs(){
    // If on the PIN screen
    if(displayingPINScreen){
        // Resolve keypad PIN inputs
        keypad_resolvePINInput();
    }
    // Else if on the notes screen
    else if(displayingNotesScreen){
        // Resolve keypad notes inputs
        keypad_resolveNotesInput();
    }
    // Else if on the calculator screen
    else if(displayingCalculatorScreen){
        // Resolve keypad calculator inputs
        keypad_resolveCalculatorInput();
    }
    // Else if on the reminders screen
    else if(displayingRemindersScreen){
        // Resolve keypad reminders inputs
        keypad_resolveRemindersInput();
    }
}

void keypad_resolvePINInput(){
    // Update FIFO and Get Button (read oldest button input from queue))
    keypad_updateFIFO();
    char button = keypad_getButton();
    
    // If number button pressed
    if(button != 0 && button != '*' && button != '#' && pinNum < 4){
        // Store pressed number (converting char to int)
        int guessedDigit = button - '0';
        
        // Draw it to PIN screen
        pin_drawDigit(guessedDigit);
        
        // Store number to guessedPIN
        int factor = 1;                    // Factor is used to determine which digit is being stored
        for(int i = pinNum; i < 3; i++){
            factor *= 10;
        }
        guessedPIN += guessedDigit * factor;
        
        // Increment to next digit
        pinNum++;
    }
}

void keypad_resolveNotesInput(){
    // Update FIFO and Get Button (read oldest button input from queue))
    keypad_updateFIFO();
    char button = keypad_getButton();
    
    // If button pressed
    if(button != 0){
        // If selecting note
        if(selectingNote){
            // Stop selecting note and start editing note
            selectingNote = false;
            notes_clearSelectionLine();
        }
        
        // Draw it to notes screen and handle complexities
        notes_drawDigit(button);
    }
}

void keypad_resolveCalculatorInput(){
    // Update FIFO and Get Button (read oldest button input from queue))
    keypad_updateFIFO();
    char button = keypad_getButton();
    
    // If button pressed
    if(button != 0){
        // Draw it to calculator screen and handle complexities
        calculator_drawDigit(button);
    }
}

void keypad_resolveRemindersInput(){
    // Update FIFO and Get Button (read oldest button input from queue))
    keypad_updateFIFO();
    char button = keypad_getButton();
    
    // If button pressed
    if(button != 0){
        // If setting reminder text
        if(settingReminderText){
            // Draw it to reminders screen and handle complexities
            reminders_drawDigit(button);
        }
        // Else if setting reminder time and input is valid
        else if(settingReminderTime && button != '*' && button != '#' && currentReminderClockDigit < 4){
            int digit = button - '0';
            
            // If in timer mode
            if(selectedReminderMode == 0){
                if(currentReminderClockDigit == 0){
                    reminderMins += digit*10;
                }
                else if(currentReminderClockDigit == 1){
                    reminderMins += digit;
                }
                else if(currentReminderClockDigit == 2 && digit < 6){
                    reminderSecs += digit*10;
                }
                else if(currentReminderClockDigit == 3){
                    reminderSecs += digit;
                }
                else{
                    return;
                }
            }
            // Else, in clock mode
            else{
                if(currentReminderClockDigit == 0){
                    reminderHours += digit*10;
                }
                else if(currentReminderClockDigit == 1){
                    reminderHours += digit;
                    if(reminderHours > 12 || reminderHours == 0){
                        reminderHours -= digit;
                        return;
                    }
                }
                else if(currentReminderClockDigit == 2 && digit < 6){
                    reminderMins += digit*10;
                }
                else if(currentReminderClockDigit == 3){
                    reminderMins += digit;
                }
                else{
                    return;
                }
            }
            
            // Draw clock and increment digit
            currentReminderClockDigit++;
            reminders_drawClock();
        }
    }
}


