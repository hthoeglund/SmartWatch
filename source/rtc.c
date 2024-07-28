#include "rtc.h"

void initRTC(){
    // Wait for registers to synchronize
    while (RTC.STATUS > 0);

    // Set PER to 32767 for 1 second, CMP to 16383 for 0.5 seconds
    RTC.PER = 32767;
    RTC.CMP = 16383;

    // Use 32.768kHz Internal Oscillator
    RTC.CLKSEL = RTC_CLKSEL_INT32K_gc;
    
    RTC.CTRLA = RTC_PRESCALER_DIV1_gc  // Pre-scale of 1
    | RTC_RTCEN_bm                     // Enable: enabled
    | RTC_RUNSTDBY_bm;                 // Run In Standby: enabled
    
    // Enable Overflow and CMP Interrupts
    RTC.INTCTRL |= RTC_OVF_bm | RTC_CMP_bm;
}

ISR(RTC_CNT_vect){
    // If 1 second has passed
    if(RTC.INTFLAGS & RTC_OVF_bm){  
        // Clear 5 keypad inputs (to handle invalid keypad presses)
        if(displayingHomeScreen){
            keypad_clearFIFO();
            keypad_clearFIFO();
            keypad_clearFIFO();
            keypad_clearFIFO();
            keypad_clearFIFO();
        }
        
        // Update clock second count
        clockSecs += 1;
        
        // Handle clock second roll-over
        if(clockSecs == 60){
            clockMins += 1;
            clockSecs = 0;
            
            // Handle minute roll-over
            if(clockMins == 60){
                clockHours += 1;
                clockMins = 0;
                
                // Handle hour roll-over
                if(clockHours == 13){
                    clockHours = 1;
                }
            }
        }
        
        // If a reminder is in timer mode and running
        if(selectedReminderMode == 0 && reminderRunning){
            reminderSecs--;
            
            // Handle timer second roll-over
            if(reminderSecs == -1){
                reminderMins -= 1;
                reminderSecs = 59;
            }
            
            // If it is finished
            if(reminderSecs == 0 && reminderMins == 0){
                // Adjust variables and start alerting
                reminderRunning = false;
                reminderAlerting = true;  
                reminderAlertTime = 5;
            }
        }
        // Else if a reminder is in clock mode, running, and finished
        else if(selectedReminderMode == 1 && reminderRunning && reminderMins == clockMins && reminderHours == clockHours){
            // Adjust variables and start alerting
            reminderRunning = false;
            reminderAlerting = true;  
            reminderAlertTime = 5;
        }
        // Else if reminder alerting
        else if(reminderAlerting){
            reminderAlertTime -= 1;
            
            // If finished alerting
            if(reminderAlertTime == 0){
                // Stop alerting
                reminderAlerting = false;
                
                // Reminder Finished
                reminderFinished = true;
                if(displayingRemindersScreen){
                    reminders_drawFinished();
                }
                
                // Clear reminder
                reminders_clearAlert();
            }
        }
        
        // If playing Simon and flashing colors
        if(runningSimon && flashingColors){
            // Turn off all LEDs
            PORTC_OUT &= ~PIN0_bm;
            PORTC_OUT &= ~PIN1_bm;
            PORTD_OUT &= ~PIN1_bm;
            
            // Increment to next flashed color
            currentSimonDisplayCount++;
            
            // If last color has been flashed
            if(currentSimonDisplayCount == currentSimonHigh + 1){
                // Stop flashing and reset variable
                flashingColors = false;
                currentSimonDisplayCount = -1;
            }
            else{
                // Flash appropriate LED
                if(simon_order[currentSimonDisplayCount] == 0){
                    PORTC_OUT |= PIN0_bm;
                }
                else if(simon_order[currentSimonDisplayCount] == 1){
                    PORTC_OUT |= PIN1_bm;
                }
                else{
                    PORTD_OUT |= PIN1_bm;
                }
            }
        }
        
        // If on home screen, diplay RTC
        if(displayingHomeScreen){
            // UpdateClock
            if((clockHours / 10) != 0){
                oled_setCursor(4, 46);
                oled_drawSingleSmallNum((clockHours / 10) + '0');
            }
            oled_setCursor(4, 50);
            oled_drawSingleSmallNum((clockHours % 10) + '0');
            oled_setCursor(4, 54);
            oled_I2CwritePixel(0b00101000);
            oled_setCursor(4, 56);
            oled_drawSingleSmallNum((clockMins / 10) + '0');
            oled_setCursor(4, 60);
            oled_drawSingleSmallNum((clockMins % 10) + '0');
        }
        // Else if displaying reminders screen, display reminder clock
        else if(displayingRemindersScreen && (reminderRunning || reminderFinished || reminderAlerting)){
            reminders_drawClock();
        } 
        // If reminder alerting, display on bottom  
        if(reminderAlerting){
            reminders_drawAlert();
        }
        
        // Clear flag
        RTC.INTFLAGS = RTC_OVF_bm;
    }
    // If half second has passed, turn off anything that needs to be flashing
    else if(RTC.INTFLAGS & RTC_CMP_bm){   
        // If on home screen
        if(displayingHomeScreen){
            // Toggle the colon off
            oled_setCursor(4, 54);
            oled_I2CwritePixel(0b00000000);
        }
        
        // If alerting, toggle alert off
        if(reminderAlerting){
            reminders_clearAlert();
        }
        
        // If playing simon, turn off LEDs
        if(runningSimon){
            // Turn off all LEDs
            PORTC_OUT &= ~PIN0_bm;
            PORTC_OUT &= ~PIN1_bm;
            PORTD_OUT &= ~PIN1_bm;
        }
        
        // Clear flag
        RTC.INTFLAGS = RTC_CMP_bm;
    }
}

