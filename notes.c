#include "notes.h"

void notes_drawScreen(){
    displayingNotesScreen = true;
    
    // Draw logo
    oled_drawAppWithoutBox(0, 52);
    
    // Draw previous notes
    notes_drawPrevious();
    
    // If selecting note
    if(selectingNote){
        
        // Draw selection line
        notes_drawSelectionLine();
    }
}

void notes_drawDigit(char button){
    // If there are 12 digits, cannot place a new digit
    if(noteDigit[currentNoteIndex] > 11){
        return;
    }
    
    // Set cursor
    oled_setCursor(0 + currentNoteIndex, 0 + 4*noteDigit[currentNoteIndex]);
    
    // If * was the last button pressed
    if(noteADCLastPressed){
        // Disable ADC
        ADC0.INTCTRL &= ~ADC_RESRDY_bm;

        // Increment digit and cursor
        noteDigit[currentNoteIndex]++;
        oled_setCursor(0 + currentNoteIndex, 0 + 4*noteDigit[currentNoteIndex]);

        // Reset ADCLastPressed variable
        noteADCLastPressed = false;
    }
    
    // If # pressed
    if(button == '#'){      
        // Draw symbol corresponding to noteCycleNum
        oled_drawSingleSmallNum(noteCycle[noteCycleNum]);
            
        // Update note string
        notes[currentNoteIndex][noteDigit[currentNoteIndex]] = noteCycle[noteCycleNum];
        
        // If noteCycleNum is at the end, reset it
        if(noteCycleNum == 7){
            // Reset cycle to beginning for next digit
            noteCycleNum = -1;
        }
        
        // Iterate to next cycle num, and # is last button pressed
        noteCycleNum++;
        noteCycleLastPressed = true;
    }
    else{
        // If # was the last button pressed,
        if(noteCycleLastPressed){
            // Increment digit and cursor
            noteDigit[currentNoteIndex]++;
            oled_setCursor(0 + currentNoteIndex, 0 + 4*noteDigit[currentNoteIndex]);
            
            // Reset cycle variables
            noteCycleLastPressed = false;
            noteCycleNum = 0;
        }

        // If button is a '*'
        if(button == '*'){
            // ADC button is last pressed
            noteADCLastPressed = true;
            
            // Enable ADC
            ADC0.INTCTRL |= ADC_RESRDY_bm;
        }
        else{
            // Adjust notes string accordingly
            notes[currentNoteIndex][noteDigit[currentNoteIndex]] = button;

            // Draw Number
            oled_drawSingleSmallNum(button);

            // Iterate to next digit
            noteDigit[currentNoteIndex]++;
        }
    }
}

void notes_clearChar(){
    // If cycle was last pressed
    if(noteCycleLastPressed){
        // Reset cycle variables
        noteCycleLastPressed = false;
        noteCycleNum = 0;
        noteDigit[currentNoteIndex]--;
    }
    // Else if ADC was last pressed
    else if(noteADCLastPressed){
        // Disable ADC
        ADC0.INTCTRL &= ~ADC_RESRDY_bm;
    }
    else{
        noteDigit[currentNoteIndex]--;
    }
    
    // If there is not anything to delete
    if(noteDigit[currentNoteIndex] < 0){
        return;
    }
    
    // Clear char in notes string
    notes[currentNoteIndex][noteDigit[currentNoteIndex]] = '\0';
    
    // Clear three rows
    oled_setCursor(0 + currentNoteIndex, 0 + 4*noteDigit[currentNoteIndex]);
    oled_I2CwritePixel(0b00000000);
    oled_I2CwritePixel(0b00000000);
    oled_I2CwritePixel(0b00000000);
    
    if(noteADCLastPressed){
        noteDigit[currentNoteIndex]--;
    }
}

void notes_drawPrevious(){
    // For each note
    for(int n = 0; n < 5; n++){
        // Set cursor to start of note
        oled_setCursor(0 + n, 0);

        // For each character
        for(int c = 0; c < 12; c++){
            oled_setCursor(0 + n, 0 + 4*c);
            
            // Draw character
            if(oled_drawSingleSmallNum(notes[n][c]) != 0){
                oled_drawSingleLetter(notes[n][c]);
            }
        }
    }
}

void notes_drawSelectionLine(){
    oled_setCursor(currentNoteIndex, 50);
    oled_I2CwritePixel(0b11111111);
}

void notes_clearSelectionLine(){
    for(int i = 0; i < 5; i++){
        oled_setCursor(i, 50);
        oled_I2CwritePixel(0b00000000);
    }
}

void notes_clearCurrentNote(){
    for(int i = 0; i < 48; i++){
        oled_setCursor(currentNoteIndex, i);
        oled_I2CwritePixel(0b00000000);
    }
}

