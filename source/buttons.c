#include "buttons.h"

ISR(PORTA_PORT_vect){
    // If green button pressed
    if(PORTA.INTFLAGS & PIN4_bm){
        // If displaying PIN screen
        if(displayingPINScreen){
            // If full PIN has been entered
            if(pinNum >= 4){
                // If PIN is correct
                if(guessedPIN == PIN){
                    // Draw PIN Success Screen
                    oled_clearDisplay();
                    pin_drawCheckScreen();
                    
                    // Delay so they can see it
                    _delay_ms(500);
                    
                    // Proceed to home screen
                    oled_clearDisplay();
                    home_drawScreen();
                }
                // Otherwise, PIN is incorrect
                else{
                    // Draw PIN Failure screen
                    oled_clearDisplay();
                    pin_drawXScreen();
                    
                    // Delay so they can see it
                    _delay_ms(500);
                    
                    // Reset PIN variables
                    guessedPIN = 0;
                    pinNum = 0;
                    
                    // Draw PIN screen to let them try again
                    oled_clearDisplay();
                    pin_drawScreen();
                }
            }
        }
        // Else if displaying home screen
        else if(displayingHomeScreen){
            // If notes app is selected
            if(appNum == 0){
                // Show note selector
                selectingNote = true;
                
                // Display notes screen
                oled_clearDisplay();
                notes_drawScreen();
            }
            // If calculator app is selected
            if(appNum == 1){
                // Display calculator screen
                oled_clearDisplay();
                calculator_drawScreen();
            }
            // If simon app is selected
            if(appNum == 2){
                // Display simon screen
                oled_clearDisplay();
                simon_drawScreen();
            }
            // If reminders app is selected
            if(appNum == 3){
                // Display reminders screen
                oled_clearDisplay();
                reminders_drawScreen();
            }
        }
        // Else if displaying notes screen
        else if(displayingNotesScreen){
            // Disable ADC
            ADC0.INTCTRL &= ~ADC_RESRDY_bm;
            
            // If selecting note
            if(selectingNote){
                // Stop selecting and edit note
                selectingNote = false;
                
                notes_clearSelectionLine();
            }
            else{
                if(currentNoteIndex < 4){
                    // Proceed to next note
                    currentNoteIndex++;

                    // Reset variables
                    noteCycleNum = 0;
                    noteCycleLastPressed = false;
                    noteADCLastPressed = false;
                }
            }
        }
        // Else if displaying calculator screen
        else if(displayingCalculatorScreen){
            // Solve the equation and display the result
            int result = calculator_solve();
            
            // If failed, draw X
            if(result == -1 && !actualResultNeg1){
                pin_drawXScreen();
                
                // Delay and draw calculator screen again
                _delay_ms(500);
                oled_clearDisplay();
                calculator_drawScreen();
            }
            else{
                // Proceed to next index
                currentEquationIndex++;
                currentEquationDigit = 0;
                currentOperatorDigit = -1;
                actualResultNeg1 = false;

                // If we reach 2nd equation, push equations up and redraw
                if(currentEquationIndex == 2){
                    // Push pointer up
                    currentEquationIndex--;

                    // Shift equations array
                    strncpy((char *)equations[0], (const char *)equations[1], 13);
                    memset((char *)equations[1], 0, 13);
                    
                    // Shift solutions array
                    strncpy((char *)solutions[0], (const char *)solutions[1], 13);
                    memset((char *)solutions[1], 0, 13);

                    // Redraw
                    calculator_clearPreviousEquations();
                    calculator_drawPreviousEquations();
                }
            }
        }
        // Else if displaying simon screen
        else if(displayingSimonScreen){
            if(!runningSimon){
                // Start a Simon game
                runningSimon = true;
                currentSimonCount = 0;
                currentSimonDisplayCount = -1;
                currentSimonHigh = 0;
                memset((char *)simon_order, 0, 20);
                simon_initGame();
                
                oled_clearDisplay();
                simon_drawScreen();
                flashingColors = true;
            }
            else if(!flashingColors){
                simon_logInput(0);
            }
        }
        // Else if displaying reminders screen
        else if(displayingRemindersScreen){
            // If setting text, go to setting modes
            if(settingReminderText){
                settingReminderText = false;
                settingReminderMode = true;
                
                reminders_drawModes();
            }
            else if(settingReminderMode){
                settingReminderMode = false;
                settingReminderTime = true;
                
                reminders_drawClock();
            }
            // else if setting reminder time properly
            else if(settingReminderTime && currentReminderClockDigit > 3 && (reminderHours != 0 || reminderMins != 0 || reminderSecs != 0)){
                settingReminderTime = false;
                reminderRunning = true;
                
                // Draw success screen
                pin_drawCheckScreen();
                
                // Delay and draw reminder screen again
                _delay_ms(250);
                oled_clearDisplay();
                reminders_drawScreen();
            }
            // Else if setting reminder time improperly
            else if(settingReminderTime){
                // Draw failure screen
                pin_drawXScreen();
                
                // Delay and draw reminder screen again
                _delay_ms(250);
                oled_clearDisplay();
                reminders_drawScreen();
            }
        }

        // Clear Flag
        PORTA.INTFLAGS |= PIN4_bm;
    }
    // If red button pressed
    else if(PORTA.INTFLAGS & PIN5_bm){
        // If displaying PIN screen
        if(displayingPINScreen){
            // If any digits have been entered
            if(pinNum > 0){
                // Decrement pinNum
                pinNum--;
                
                // Clear the last digit
                pin_clearDigit(pinNum);
                
                // Adjust guessedPIN accordingly
                int factor = 1;                    // Factor is used to determine which digit is being stored
                for(int i = pinNum; i < 3; i++){
                    factor *= 10;
                }
                guessedPIN -=  (guessedPIN % (factor * 10));
            }
        }
        // Else if displaying notes screen
        else if(displayingNotesScreen){
            // If selecting note
            if(selectingNote){
                // Stop selecting and edit note
                selectingNote = false;
                
                notes_clearSelectionLine();
            }
            notes_clearChar();
        }
        // Else if displaying calculator screen
        else if(displayingCalculatorScreen){
            calculator_clearDigit();
        }
        // Else if displaying Simon screen
        else if(displayingSimonScreen && runningSimon && !flashingColors){
            simon_logInput(1);
        }
        // Else if displaying reminders screen
        else if(displayingRemindersScreen){
            // If setting reminder text, clear a character
            if(settingReminderText){
                reminders_clearChar();
            }
            // Else if setting reminder mode, return to text editor
            else if(settingReminderMode){
                settingReminderMode = false;
                settingReminderText = true;
                
                reminders_clearModes();
                reminders_clearClock();
            }
            // Else if setting clock and at first digit, return to mode selector
            else if(settingReminderTime && currentReminderClockDigit == 0){
                settingReminderTime = false;
                settingReminderMode = true;
                reminders_clearClock();
            }
            // Otherwise, set last digit to 0
            else if(settingReminderTime){
                // Decrement current reminder digit
                currentReminderClockDigit--;
                
                // If in timer mode
                if(selectedReminderMode == 0){
                    if(currentReminderClockDigit == 0){
                        reminderMins = 0;
                    }
                    else if(currentReminderClockDigit == 1){
                        reminderMins /= 10;
                        reminderMins *= 10;
                    }
                    else if(currentReminderClockDigit == 2){
                        reminderSecs = 0;
                    }
                    else if(currentReminderClockDigit == 3){
                        reminderSecs /= 10;
                        reminderSecs *= 10;
                    }
                }
                // Else, in clock mode
                else{
                    if(currentReminderClockDigit == 0){
                        reminderHours = 0;
                    }
                    else if(currentReminderClockDigit == 1){
                        reminderHours /= 10;
                        reminderHours *= 10;
                    }
                    else if(currentReminderClockDigit == 2){
                        reminderMins = 0;
                    }
                    else if(currentReminderClockDigit == 3){
                        reminderMins /= 10;
                        reminderMins *= 10;
                    }
                }
                
                reminders_drawClock();
            }
        }
        
        // Clear Flag
        PORTA.INTFLAGS |= PIN5_bm;
    }
    // If yellow button pressed
    else if(PORTA.INTFLAGS & PIN6_bm){
        // If displaying notes screen and selecting note
        if(displayingNotesScreen){
            // Disable ADC
            ADC0.INTCTRL &= ~ADC_RESRDY_bm;
            
            // Clear note
            memset((char*)notes[currentNoteIndex], 0, 12);
            noteDigit[currentNoteIndex] = 0;
            noteCycleNum = 0;
            noteCycleLastPressed = false;
            noteADCLastPressed = false;
            
            notes_clearCurrentNote();
        }
        // Else if displaying calculator screen
        else if(displayingCalculatorScreen){
            // Clear all equations
            clearAllEqSols();
        }
        // Else if displaying Simon screen
        else if(displayingSimonScreen && runningSimon && !flashingColors){
            simon_logInput(2);
        }
        // Else if displaying reminders screen
        else if(displayingRemindersScreen){
            // Disable ADC
            ADC0.INTCTRL &= ~ADC_RESRDY_bm;
            
            // Clear reminder
            memset((char *) reminders, 0, 13);
            currentReminderDigit = 0;
            reminderCycleNum = 0;
            reminderCycleLastPressed = false;
            reminderADCLastPressed = false;
            currentReminderClockDigit = 0;
            settingReminderText = true;
            settingReminderMode = false;
            selectedReminderMode = 0;
            settingReminderTime = false;
            reminderRunning = false;
            reminderAlerting = false;
            reminderFinished = false;
            reminderSecs = 0;
            reminderMins = 0;
            reminderHours = 0;
           
            oled_clearDisplay();
            reminders_drawScreen();
        }
        
        // Clear Flag
        PORTA.INTFLAGS |= PIN6_bm;
    }
    // If blue button pressed
    else if(PORTA.INTFLAGS & PIN7_bm){
        // As long as not on PIN screen
        if(!displayingPINScreen){  
            // Disable ADC
            ADC0.INTCTRL &= ~ADC_RESRDY_bm;
            
            // Stop Simon
            runningSimon = false;
            currentSimonCount = 0;
            currentSimonHigh = 0;
            currentSimonDisplayCount = 0;
            memset((char *)simon_order, 0, 20);
            
            // Turn off all LEDs
            PORTC_OUT &= ~PIN0_bm;
            PORTC_OUT &= ~PIN1_bm;
            PORTD_OUT &= ~PIN1_bm;
            
            // If selecting note
            if(selectingNote){
                // Stop selecting and edit note
                selectingNote = false;
            }
            
            // Go to home screen
            oled_clearDisplay();
            home_drawScreen();
        }
        
        // Clear Flag
        PORTA.INTFLAGS |= PIN7_bm;
    }
}
