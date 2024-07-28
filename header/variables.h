#ifndef VARIABLES_H
#define	VARIABLES_H

#ifndef F_CPU
#define F_CPU 3333333
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>        // Time is only included for random number generation
#include <string.h>
#include <stdbool.h>
#include <avr/interrupt.h>

// Pointer Location Variables (where is user?)
extern volatile int appNum;         // App selected (0 -> 3, left to right on home screen)
extern volatile int pinNum;         // Cursor index on PIN screen

// Display Variables
extern volatile bool displayingPINScreen;         // Whether displaying PIN screen
extern volatile bool displayingHomeScreen;        // Whether displaying home screen
extern volatile bool displayingNotesScreen;       // Whether displaying notes screen
extern volatile bool displayingCalculatorScreen;  // Whether displaying calculator screen
extern volatile bool displayingSimonScreen;       // Whether displaying simon screen
extern volatile bool displayingRemindersScreen;   // Whether displaying reminders screen

// Clock Counter Variables
extern volatile int clockSecs;      // Clock seconds count
extern volatile int clockMins;      // Clock minutes count
extern volatile int clockHours;     // Clock hours count

// PIN Variables
extern volatile int PIN;            // Correct PIN
extern volatile int guessedPIN;     // PIN that user guessed

// Note Variables
extern volatile char notes[5][12];          // Note strings
extern volatile int currentNoteIndex;       // Index of the current note
extern volatile int noteDigit[5];           // Cursor location in each note
extern volatile int noteCycleNum;           // Current location in the punctuation operator cycle
extern volatile char noteCycle[8];          // Punctuation cycle
extern volatile bool noteCycleLastPressed;  // Whether # was the last button pressed
extern volatile bool noteADCLastPressed;    // Whether * was the last button pressed
extern volatile bool selectingNote;         // Whether in the note selector

// Calculator Variables
extern volatile char equations[2][13];       // Equation strings
extern volatile char solutions[2][13];       // Solution strings
extern volatile int currentEquationIndex;    // Index of the current equation
extern volatile int currentEquationDigit;    // Cursor location in the current equation
extern volatile int currentOperatorDigit;              // Current index of the operator in the current equation
extern volatile char calculatorCycle[8];               // Operator cycle
extern volatile int calculatorCycleNum;                // Current location in the '#' operator cycle
extern volatile bool calculatorCycleLastPressed;       // Whether # was the last button pressed (whether user is in cycle)
extern volatile bool actualResultNeg1;                 // Whether the actual result is -1, for error purposes

// Simon Variables
extern volatile bool runningSimon;                  // Whether simon is running
extern volatile bool flashingColors;             // Whether flashing colors
extern volatile int currentSimonCount;              // Current count of button presses
extern volatile int currentSimonDisplayCount;       // Current count of flashing colors
extern volatile int currentSimonHigh;               // Current high score
extern volatile int simon_order[20];                // Ordering for a specific game of simon

// Reminder Text Variables
extern volatile char reminders[13];              // Reminder string
extern volatile int currentReminderDigit;        // Current cursor location in the reminder string
extern volatile int reminderCycleNum;            // Current location in the reminder punctuation cycle
extern volatile char reminderCycle[8];           // Reminder punctuation cycle
extern volatile bool reminderCycleLastPressed;   // Whether # was the last button pressed (whether user is in cycle)
extern volatile bool reminderADCLastPressed;     // Whether * was the last button pressed (whether user is in ADC)
extern volatile int currentReminderClockDigit;   // Current cursor location on the reminder clock

// Reminder mode variables
extern volatile bool settingReminderText;        // Whether user is setting reminder text
extern volatile bool settingReminderMode;        // Whether user is setting reminder mode
extern volatile int selectedReminderMode;        // Reminder mode selected (0 for timer, 1 for clock)
extern volatile bool settingReminderTime;        // Whether user is setting reminder time

// Reminder Timer Variables
extern volatile bool reminderRunning;            // Whether the reminder is running
extern volatile bool reminderAlerting;           // Whether the reminder is alerting
extern volatile bool reminderFinished;           // Whether the reminder is finished
extern volatile int reminderAlertTime;           // Time left on the reminder alert
extern volatile int reminderSecs;                // Reminder clock second count
extern volatile int reminderMins;                // Reminder clock minute count
extern volatile int reminderHours;               // Reminder clock hour count

#endif	/* VARIABLES_H */

