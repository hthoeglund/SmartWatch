#include "adc.h"


void initADC(){
    // Potentiometer Setup
    PORTD.PIN6CTRL &= ~PORT_ISC_gm;
    PORTD.PIN6CTRL |= PORT_ISC_INPUT_DISABLE_gc;
    PORTD.PIN6CTRL &= ~PORT_PULLUPEN_bm;
    
    // ADC Setup
    ADC0.CTRLC = ADC_PRESC_DIV4_gc | ADC_REFSEL_VDDREF_gc;
    ADC0.CTRLA = ADC_ENABLE_bm | ADC_RESSEL_10BIT_gc | ADC_FREERUN_bm;
    ADC0.MUXPOS = ADC_MUXPOS_AIN6_gc;
    ADC0.EVCTRL |= ADC_STARTEI_bm;
    ADC0.COMMAND = ADC_STCONV_bm;
}

ISR(ADC0_RESRDY_vect){
    // Read potentiometer reading
    int adc = ADC0.RES;
    
    // Set cursor according to current screen
    if(displayingNotesScreen){
        oled_setCursor(0 + currentNoteIndex, 0 + 4*noteDigit[currentNoteIndex]);
    }
    else if(displayingRemindersScreen){
        oled_setCursor(0, 0 + 4*currentReminderDigit);
    }
    
    // Determine letter based upon ADC reading
    char letter;
    if(adc < 39){
        letter = 'a';
    }
    else if(adc < 78){
        letter = 'b';
    }
    else if(adc < 117){
        letter = 'c';
    }
    else if(adc < 156){
        letter = 'd';
    }
    else if(adc < 195){
        letter = 'e';
    }
    else if(adc < 234){
        letter = 'f';
    }
    else if(adc < 273){
        letter = 'g';
    }
    else if(adc < 312){
        letter = 'h';
    }
    else if(adc < 351){
        letter = 'i';
    }
    else if(adc < 390){
        letter = 'j';
    }
    else if(adc < 429){
        letter = 'k';
    }
    else if(adc < 468){
        letter = 'l';
    }
    else if(adc < 507){
        letter = 'm';
    }
    else if(adc < 546){
        letter = 'n';
    }
    else if(adc < 585){
        letter = 'o';
    }
    else if(adc < 624){
        letter = 'p';
    }
    else if(adc < 663){
        letter = 'q';
    }
    else if(adc < 702){
        letter = 'r';
    }
    else if(adc < 741){
        letter = 's';
    }
    else if(adc < 780){
        letter = 't';
    }
    else if(adc < 819){
        letter = 'u';
    }
    else if(adc < 858){
        letter = 'v';
    }
    else if(adc < 897){
        letter = 'w';
    }
    else if(adc < 936){
        letter = 'x';
    }
    else if(adc < 975){
        letter = 'y';
    }
    else{
        letter = 'z';
    }
    
    // Draw letter
    oled_drawSingleLetter(letter);
    
    // Adjust string accordingly
    if(displayingNotesScreen){
        notes[currentNoteIndex][noteDigit[currentNoteIndex]] = letter;
    }
    else if(displayingRemindersScreen){
        reminders[currentReminderDigit] = letter;
    }
    
    // Resolve keypad inputs
    keypad_resolveInputs();
    
    // Clear flag
    ADC0.INTFLAGS = ADC_RESRDY_bm;
}

