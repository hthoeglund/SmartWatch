#include "joystick.h"

void joystick_read(uint8_t *dest, uint8_t len){
    // Send I2C Address
    TWI0.MADDR = (0x20 << 1) | 0;
    
    // Wait for write
    while (!(TWI0.MSTATUS & TWI_WIF_bm));
    
    // Write the register to I2C
    TWI0.MDATA = 0x03;
    
    // Wait for write
    while (!(TWI0.MSTATUS & TWI_WIF_bm));
    
    // Restart
    TWI0.MCTRLB = TWI_MCMD_REPSTART_gc;
    
    // Send Address
    TWI0.MADDR = (0x20 << 1) | 1;
   
    // Release the clock hold
    TWI0.MSTATUS = TWI_CLKHOLD_bm;
    
    // Read in len bytes
    uint8_t bCount = 0;
    while (bCount < len)
    {
        // Wait for read
        while (!(TWI0.MSTATUS & TWI_RIF_bm));
        
        // Store data
        dest[bCount] = TWI0.MDATA;

        // Increment the counter
        bCount += 1;
        
        // If not done, then ACK and read the next byte
        if (bCount != len)
        {
            TWI0.MCTRLB = TWI_ACKACT_ACK_gc | TWI_MCMD_RECVTRANS_gc;
        }
    }
    
    // NACK and STOP the bus
    TWI0.MCTRLB = TWI_ACKACT_NACK_gc | TWI_MCMD_STOP_gc;
}

void joystick_resolveInputs(){
    uint8_t joystick[4];
    
    // Read in 4 bytes (MSB and LSB for up/down, left/right respectively)
    // Only MSB will be used in this case
    joystick_read(joystick, 4);
    
    if(displayingHomeScreen){
        // RIGHT
        if(joystick[2] > 150){
            // Move app selector to the right
            if(appNum < 3){
                home_drawAppWithoutBox(appNum);
                appNum += 1;
                home_drawCurrentAppBox();
            }
        }
        // LEFT
        else if(joystick[2] < 100){
            if(appNum > 0){
                home_drawAppWithoutBox(appNum);
                appNum -= 1;
                home_drawCurrentAppBox();
            }
        } 
    }
    else if(displayingNotesScreen){
        // UP
        if(joystick[0] > 150){
            // Disable ADC
            ADC0.INTCTRL &= ~ADC_RESRDY_bm;
            
            // If not selecting, start selecting
            if(!selectingNote){
                selectingNote = true;
                
                notes_drawSelectionLine();
            }
            // Otherwise move note selector up
            else if(currentNoteIndex > 0){
                currentNoteIndex--;
                
                notes_clearSelectionLine();
                notes_drawSelectionLine();
            }
        }
        // Down
        else if(joystick[0] < 100){
            // Disable ADC
            ADC0.INTCTRL &= ~ADC_RESRDY_bm;
            
            // If not selecting, start selecting
            if(!selectingNote){
                selectingNote = true;
                
                notes_drawSelectionLine();
            }
            // Otherwise move note selector down
            else if(currentNoteIndex < 4){
                currentNoteIndex++;
                
                notes_clearSelectionLine();
                notes_drawSelectionLine();
            }
        }
    }
    else if(displayingRemindersScreen && settingReminderMode){
        // UP
        if(joystick[0] > 150 && selectedReminderMode == 1){
            // If in clock mode, select timer mode
            selectedReminderMode--;
            
            reminders_clearModes();
            reminders_drawModes();
        }
        // Down
        else if(joystick[0] < 100 && selectedReminderMode == 0){
            // If in timer mode, select clock mode
            selectedReminderMode++;

            reminders_clearModes();
            reminders_drawModes();
        }
    }
}
