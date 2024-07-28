#include "variables.h"

// Pointer Location Variables (where is user?)
volatile int appNum = 0;
volatile int pinNum = 0;

// Display Variables
volatile bool displayingPINScreen = true;
volatile bool displayingHomeScreen = false;
volatile bool displayingNotesScreen = false;
volatile bool displayingCalculatorScreen = false;
volatile bool displayingSimonScreen = false;
volatile bool displayingRemindersScreen = false;

// Clock Counter Variables
volatile int clockSecs = 0;
volatile int clockMins = 0;
volatile int clockHours = 12;

// PIN Variables
volatile int PIN = 1234;
volatile int guessedPIN = 0;

// Note Variables
volatile char notes[5][12] = {};
volatile int currentNoteIndex = 0;
volatile int noteDigit[5] = {};
volatile int noteCycleNum = 0;
volatile char noteCycle[8] = {',', '\'', ':', ';', '.', '!', '?', '_'};
volatile bool noteCycleLastPressed = false;
volatile bool noteADCLastPressed = false;
volatile bool selectingNote = false;

// Calculator Variables
volatile char equations[2][13] = {};
volatile char solutions[2][13] = {};
volatile int currentEquationIndex = 0;
volatile int currentEquationDigit = 0;
volatile int currentOperatorDigit = -1;
volatile int calculatorCycleNum = 0;
volatile char calculatorCycle[8] = {'+', '-', '/', '*'};
volatile bool calculatorCycleLastPressed = false;
volatile bool actualResultNeg1 = false;

// Simon Variables
volatile bool runningSimon = false;
volatile bool flashingColors = false;
volatile int currentSimonCount = 0;
volatile int currentSimonDisplayCount = -1;
volatile int currentSimonHigh = 0;
volatile int simon_order[20] = {};

// Reminder Text Variables
volatile char reminders[13] = {};
volatile int currentReminderDigit = 0;
volatile int reminderCycleNum = 0;
volatile char reminderCycle[8] = {',', '\'', ':', ';', '.', '!', '?', '_'};
volatile bool reminderCycleLastPressed = false;
volatile bool reminderADCLastPressed = false;
volatile int currentReminderClockDigit = 0;

// Reminder mode variables
volatile bool settingReminderText = true;
volatile bool settingReminderMode = false;
volatile int selectedReminderMode = 0;
volatile bool settingReminderTime = false;

// Reminder Timer Variables
volatile bool reminderRunning = false;
volatile bool reminderAlerting = false;
volatile bool reminderFinished = false;
volatile int reminderAlertTime = 3;
volatile int reminderSecs = 0;
volatile int reminderMins = 0;
volatile int reminderHours = 0;