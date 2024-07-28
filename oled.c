#include "oled.h"

void oled_I2CwriteDouble(int first, int second){
    // Send I2C Address
    TWI0.MADDR = (0x3D << 1) | 0;
    
    // Wait...
    while (!(TWI0.MSTATUS & TWI_WIF_bm));

    // Send first byte
    TWI0.MDATA = first;
    
    // Wait...
    while (!(TWI0.MSTATUS & TWI_WIF_bm));

    // Send second byte
    TWI0.MDATA = second;
    
    // Wait...
    while (!(TWI0.MSTATUS & TWI_WIF_bm));
        
    // NACK and STOP the bus
    TWI0.MCTRLB = TWI_ACKACT_NACK_gc | TWI_MCMD_STOP_gc;
}

void oled_I2CwriteCMD(int command){
    // Writes 0x00 and then a command (Display protocol)
    oled_I2CwriteDouble(0x00, command);
}

void oled_I2CwritePixel(int pixel){
    // Writes 0x40 and then pixel information to I2C (Display protocol)
    oled_I2CwriteDouble(0x40, pixel);
}

void oled_initDisplay(){
    oled_I2CwriteCMD(0xAE);    // Display off
    oled_I2CwriteCMD(0x2E);    // Stop scrolling
    
    oled_I2CwriteCMD(0xD5);    // Set Display Clock Div
    oled_I2CwriteCMD(0x80);    // Suggested Ratio for Oscillator Frequency
    
    oled_I2CwriteCMD(0xA8);    // Set Multiplex
    oled_I2CwriteCMD(0x2F);    // 48 - 1 (48 pixels tall)

    oled_I2CwriteCMD(0xD3);    // Set Display Offset
    oled_I2CwriteCMD(0x0);     // No Offset
    
    oled_I2CwriteCMD(0x40 | 0x0);    // SETSTARTLINE to 0
    oled_I2CwriteCMD(0x8D);          // CHARGEPUMP
    oled_I2CwriteCMD(0x14);          // Enable Internal ChargePump
    
    oled_I2CwriteCMD(0xA0 | 0x01);   // SERGEMAP
    oled_I2CwriteCMD(0xC8);          // COMSCANDEC
    
    oled_I2CwriteCMD(0xDA);    // SETCOMPINS
    oled_I2CwriteCMD(0x12);
    
    oled_I2CwriteCMD(0x81);    // SETCONTRAST
    oled_I2CwriteCMD(0x8F);    // Contrast Value
    
    oled_I2CwriteCMD(0xD9);    // SETPRECHARGE
    oled_I2CwriteCMD(0xF1);    // Pre-Charge Settings Value
    
    oled_I2CwriteCMD(0xDB);    // SETVCOMDESELECT
    oled_I2CwriteCMD(0x40);    // Deselect Value
    
    oled_I2CwriteCMD(0xA4);    // Resume RAM content to Display
    oled_I2CwriteCMD(0xA6);    // Display in Normal Mode
    oled_I2CwriteCMD(0xAF);    // Display On
}

void oled_setCursor(int row, int col){
    oled_I2CwriteCMD(0x20);    // Set Memory Addressing
    oled_I2CwriteCMD(0x00);    // Horizontal Addressing
    
    oled_I2CwriteCMD(0x21);    // Set Column Addressing
    oled_I2CwriteCMD(32 + col);     // Lower Column Address
    oled_I2CwriteCMD(96);      // Upper Column Address
    
    oled_I2CwriteCMD(0x22);    // Set Page (chunk of 8 rows) Address
    oled_I2CwriteCMD(row);     // Lower Page Address
    oled_I2CwriteCMD(5);       // Upper Page Address
}

void oled_clearDisplay(){
    // Not displaying any screen anymore
    displayingPINScreen = false;
    displayingHomeScreen = false;
    displayingNotesScreen = false;
    displayingCalculatorScreen = false;
    displayingSimonScreen = false;
    displayingRemindersScreen = false;
    
    // Disable display and reset cursor
    oled_I2CwriteCMD(0xAE);
    oled_setCursor(0, 0);
    
    // Resume RAM content to display
    oled_I2CwriteCMD(0xA4);  
    
    // Display on in Normal Mode
    oled_I2CwriteCMD(0xAF);
    
    // Write empty bytes to pixels
    for(int i = 0; i < 786; i++){
        oled_I2CwriteDouble(0xC0, 0x00);
    }
}

void oled_drawAppWithoutBox(int num, int rightShift){
    // Box Edges
    oled_setCursor(0, 0 + rightShift);
    oled_I2CwritePixel(0b00000000);
    oled_setCursor(1, 0 + rightShift);
    oled_I2CwritePixel(0b00000000);
    oled_setCursor(0, 1 + rightShift);
    oled_I2CwritePixel(0b11111000);
    oled_setCursor(1, 1 + rightShift);
    oled_I2CwritePixel(0b00011111);
    oled_setCursor(0, 2 + rightShift);
    oled_I2CwritePixel(0b00001000);
    oled_setCursor(1, 2 + rightShift);
    oled_I2CwritePixel(0b00010000);

    oled_setCursor(0, 9 + rightShift);
    oled_I2CwritePixel(0b00001000);
    oled_setCursor(1, 9 + rightShift);
    oled_I2CwritePixel(0b00010000);
    oled_setCursor(0, 10 + rightShift);
    oled_I2CwritePixel(0b11111000);
    oled_setCursor(1, 10 + rightShift);
    oled_I2CwritePixel(0b00011111);
    oled_setCursor(0, 11 + rightShift);
    oled_I2CwritePixel(0b00000000);
    oled_setCursor(1, 11 + rightShift);
    oled_I2CwritePixel(0b00000000);
    
    // N
    if(num == 0){
        oled_setCursor(0, 3 + rightShift);
        oled_I2CwritePixel(0b11101000);
        oled_setCursor(1, 3 + rightShift);
        oled_I2CwritePixel(0b00010111);
        oled_setCursor(0, 4 + rightShift);
        oled_I2CwritePixel(0b01001000);
        oled_setCursor(1, 4 + rightShift);
        oled_I2CwritePixel(0b00010000);
        oled_setCursor(0, 5 + rightShift);
        oled_I2CwritePixel(0b10001000);
        oled_setCursor(1, 5 + rightShift);
        oled_I2CwritePixel(0b00010000);
        oled_setCursor(0, 6 + rightShift);
        oled_I2CwritePixel(0b00001000);
        oled_setCursor(1, 6 + rightShift);
        oled_I2CwritePixel(0b00010001);
        oled_setCursor(0, 7 + rightShift);
        oled_I2CwritePixel(0b00001000);
        oled_setCursor(1, 7 + rightShift);
        oled_I2CwritePixel(0b00010010);
        oled_setCursor(0, 8 + rightShift);
        oled_I2CwritePixel(0b11101000);
        oled_setCursor(1, 8 + rightShift);
        oled_I2CwritePixel(0b00010111);
    }
    
    // C
    if(num == 1){
        oled_setCursor(0, 3 + rightShift);
        oled_I2CwritePixel(0b11101000);
        oled_setCursor(1, 3 + rightShift);
        oled_I2CwritePixel(0b00010111);
        oled_setCursor(0, 4 + rightShift);
        oled_I2CwritePixel(0b00101000);
        oled_setCursor(1, 4 + rightShift);
        oled_I2CwritePixel(0b00010100);
        oled_setCursor(0, 5 + rightShift);
        oled_I2CwritePixel(0b00101000);
        oled_setCursor(1, 5 + rightShift);
        oled_I2CwritePixel(0b00010100);
        oled_setCursor(0, 6 + rightShift);
        oled_I2CwritePixel(0b00101000);
        oled_setCursor(1, 6 + rightShift);
        oled_I2CwritePixel(0b00010100);
        oled_setCursor(0, 7 + rightShift);
        oled_I2CwritePixel(0b00101000);
        oled_setCursor(1, 7 + rightShift);
        oled_I2CwritePixel(0b00010100);
        oled_setCursor(0, 8 + rightShift);
        oled_I2CwritePixel(0b00101000);
        oled_setCursor(1, 8 + rightShift);
        oled_I2CwritePixel(0b00010100);
    }
    
    // S
    if(num == 2){
        oled_setCursor(0, 3 + rightShift);
        oled_I2CwritePixel(0b11101000);
        oled_setCursor(1, 3 + rightShift);
        oled_I2CwritePixel(0b00010101);
        oled_setCursor(0, 4 + rightShift);
        oled_I2CwritePixel(0b00101000);
        oled_setCursor(1, 4 + rightShift);
        oled_I2CwritePixel(0b00010101);
        oled_setCursor(0, 5 + rightShift);
        oled_I2CwritePixel(0b00101000);
        oled_setCursor(1, 5 + rightShift);
        oled_I2CwritePixel(0b00010101);
        oled_setCursor(0, 6 + rightShift);
        oled_I2CwritePixel(0b00101000);
        oled_setCursor(1, 6 + rightShift);
        oled_I2CwritePixel(0b00010101);
        oled_setCursor(0, 7 + rightShift);
        oled_I2CwritePixel(0b00101000);
        oled_setCursor(1, 7 + rightShift);
        oled_I2CwritePixel(0b00010101);
        oled_setCursor(0, 8 + rightShift);
        oled_I2CwritePixel(0b00101000);
        oled_setCursor(1, 8 + rightShift);
        oled_I2CwritePixel(0b00010111);
    }
    
    // R
    if(num == 3){
        oled_setCursor(0, 3 + rightShift);
        oled_I2CwritePixel(0b00001000);
        oled_setCursor(1, 3 + rightShift);
        oled_I2CwritePixel(0b00010000);
        oled_setCursor(0, 4 + rightShift);
        oled_I2CwritePixel(0b11101000);
        oled_setCursor(1, 4 + rightShift);
        oled_I2CwritePixel(0b00010111);
        oled_setCursor(0, 5 + rightShift);
        oled_I2CwritePixel(0b10101000);
        oled_setCursor(1, 5 + rightShift);
        oled_I2CwritePixel(0b00010001);
        oled_setCursor(0, 6 + rightShift);
        oled_I2CwritePixel(0b10101000);
        oled_setCursor(1, 6 + rightShift);
        oled_I2CwritePixel(0b00010010);
        oled_setCursor(0, 7 + rightShift);
        oled_I2CwritePixel(0b11101000);
        oled_setCursor(1, 7 + rightShift);
        oled_I2CwritePixel(0b00010100);
        oled_setCursor(0, 8 + rightShift);
        oled_I2CwritePixel(0b00001000);
        oled_setCursor(1, 8 + rightShift);
        oled_I2CwritePixel(0b00010000);
    }
}

int oled_drawSingleSmallNum(char num){
    if(num == '0'){
        oled_I2CwritePixel(0b01111100);
        oled_I2CwritePixel(0b01000100);
        oled_I2CwritePixel(0b01111100);
    }
    else if(num == '1'){
        oled_I2CwritePixel(0b00000000);
        oled_I2CwritePixel(0b01111100);
        oled_I2CwritePixel(0b00000000);
    }
    else if(num == '2'){
        oled_I2CwritePixel(0b01110100);
        oled_I2CwritePixel(0b01010100);
        oled_I2CwritePixel(0b01011100);
    }
    else if(num == '3'){
        oled_I2CwritePixel(0b01010100);
        oled_I2CwritePixel(0b01010100);
        oled_I2CwritePixel(0b01111100);
    }
    else if(num == '4'){
        oled_I2CwritePixel(0b00011100);
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b01111100);
    }
    else if(num == '5'){
        oled_I2CwritePixel(0b01011100);
        oled_I2CwritePixel(0b01010100);
        oled_I2CwritePixel(0b01110100);
    }
    else if(num == '6'){
        oled_I2CwritePixel(0b01111100);
        oled_I2CwritePixel(0b01010000);
        oled_I2CwritePixel(0b01110000);
    }
    else if(num == '7'){
        oled_I2CwritePixel(0b00000100);
        oled_I2CwritePixel(0b00000100);
        oled_I2CwritePixel(0b01111100);
    }
    else if(num == '8'){
        oled_I2CwritePixel(0b01111100);
        oled_I2CwritePixel(0b01010100);
        oled_I2CwritePixel(0b01111100);
    }
    else if(num == '9'){
        oled_I2CwritePixel(0b00011100);
        oled_I2CwritePixel(0b00010100);
        oled_I2CwritePixel(0b01111100);
    }
    else if(num == '*'){
        oled_I2CwritePixel(0b00101000);
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b00101000);
    }
    else if(num == '+'){
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b00111000);
        oled_I2CwritePixel(0b00010000);
    }
    else if(num == '-'){
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b00010000);
    }
    else if(num == '/'){
        oled_I2CwritePixel(0b00100000);
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b00001000);
    }
    else if(num == '='){
        oled_I2CwritePixel(0b00101000);
        oled_I2CwritePixel(0b00101000);
        oled_I2CwritePixel(0b00101000);
    }
    else if(num == ','){
        oled_I2CwritePixel(0b10000000);
        oled_I2CwritePixel(0b01000000);
        oled_I2CwritePixel(0b00000000);
    }
    else if(num == '\''){
        oled_I2CwritePixel(0b00000000);
        oled_I2CwritePixel(0b00000110);
        oled_I2CwritePixel(0b00000000);
    }
    else if(num == ':'){
        oled_I2CwritePixel(0b00000000);
        oled_I2CwritePixel(0b00101000);
        oled_I2CwritePixel(0b00000000);
    }
    else if(num == ';'){
        oled_I2CwritePixel(0b00000000);
        oled_I2CwritePixel(0b01101000);
        oled_I2CwritePixel(0b00000000);
    }
    else if(num == '.'){
        oled_I2CwritePixel(0b00000000);
        oled_I2CwritePixel(0b01000000);
        oled_I2CwritePixel(0b00000000);
    }
    else if(num == '!'){
        oled_I2CwritePixel(0b00000000);
        oled_I2CwritePixel(0b01011100);
        oled_I2CwritePixel(0b00000000);
    }
    else if(num == '?'){
        oled_I2CwritePixel(0b00000100);
        oled_I2CwritePixel(0b01010100);
        oled_I2CwritePixel(0b00011100);
    }
    else if(num == '_'){
        oled_I2CwritePixel(0b00000000);
        oled_I2CwritePixel(0b00000000);
        oled_I2CwritePixel(0b00000000);
    }
    else{
        return -1;
    }
    
    return 0;
}

int oled_drawSingleLargeNum(char num, int startingRow, int startingCol){
    if(num == '0'){
        oled_setCursor(startingRow, startingCol);
        oled_I2CwritePixel(0b11110000);
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b11110000);
        oled_setCursor(startingRow+1, startingCol);
        oled_I2CwritePixel(0b00011111);
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b00011111);
    }
    else if(num == '1'){
        oled_setCursor(startingRow, startingCol);
        oled_I2CwritePixel(0b00000000);
        oled_I2CwritePixel(0b00000000);
        oled_I2CwritePixel(0b11110000);
        oled_I2CwritePixel(0b00000000);
        oled_I2CwritePixel(0b00000000);
        oled_setCursor(startingRow+1, startingCol);
        oled_I2CwritePixel(0b00000000);
        oled_I2CwritePixel(0b00000000);
        oled_I2CwritePixel(0b00011111);
        oled_I2CwritePixel(0b00000000);
        oled_I2CwritePixel(0b00000000);
    }
    else if(num == '2'){
        oled_setCursor(startingRow, startingCol);
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b11110000);
        oled_setCursor(startingRow+1, startingCol);
        oled_I2CwritePixel(0b00011111);
        oled_I2CwritePixel(0b00010001);
        oled_I2CwritePixel(0b00010001);
        oled_I2CwritePixel(0b00010001);
        oled_I2CwritePixel(0b00010001);
    }
    else if(num == '3'){
        oled_setCursor(startingRow, startingCol);
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b11110000);
        oled_setCursor(startingRow+1, startingCol);
        oled_I2CwritePixel(0b00010001);
        oled_I2CwritePixel(0b00010001);
        oled_I2CwritePixel(0b00010001);
        oled_I2CwritePixel(0b00010001);
        oled_I2CwritePixel(0b00011111);
    }
    else if(num == '4'){
        oled_setCursor(startingRow, startingCol);
        oled_I2CwritePixel(0b11110000);
        oled_I2CwritePixel(0b00000000);
        oled_I2CwritePixel(0b00000000);
        oled_I2CwritePixel(0b00000000);
        oled_I2CwritePixel(0b11110000);
        oled_setCursor(startingRow+1, startingCol);
        oled_I2CwritePixel(0b00000001);
        oled_I2CwritePixel(0b00000001);
        oled_I2CwritePixel(0b00000001);
        oled_I2CwritePixel(0b00000001);
        oled_I2CwritePixel(0b00011111);
    }
    else if(num == '5'){
        oled_setCursor(startingRow, startingCol);
        oled_I2CwritePixel(0b11110000);
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b00010000);
        oled_setCursor(startingRow+1, startingCol);
        oled_I2CwritePixel(0b00010001);
        oled_I2CwritePixel(0b00010001);
        oled_I2CwritePixel(0b00010001);
        oled_I2CwritePixel(0b00010001);
        oled_I2CwritePixel(0b00011111);
    }
    else if(num == '6'){
        oled_setCursor(startingRow, startingCol);
        oled_I2CwritePixel(0b11110000);
        oled_I2CwritePixel(0b00000000);
        oled_I2CwritePixel(0b00000000);
        oled_I2CwritePixel(0b00000000);
        oled_I2CwritePixel(0b00000000);
        oled_setCursor(startingRow+1, startingCol);
        oled_I2CwritePixel(0b00011111);
        oled_I2CwritePixel(0b00010001);
        oled_I2CwritePixel(0b00010001);
        oled_I2CwritePixel(0b00010001);
        oled_I2CwritePixel(0b00011111);
    }
    else if(num == '7'){
        oled_setCursor(startingRow, startingCol);
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b11110000);
        oled_setCursor(startingRow+1, startingCol);
        oled_I2CwritePixel(0b00000000);
        oled_I2CwritePixel(0b00000000);
        oled_I2CwritePixel(0b00000000);
        oled_I2CwritePixel(0b00000000);
        oled_I2CwritePixel(0b00011111);
    }
    else if(num == '8'){
        oled_setCursor(startingRow, startingCol);
        oled_I2CwritePixel(0b11110000);
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b11110000);
        oled_setCursor(startingRow+1, startingCol);
        oled_I2CwritePixel(0b00011111);
        oled_I2CwritePixel(0b00010001);
        oled_I2CwritePixel(0b00010001);
        oled_I2CwritePixel(0b00010001);
        oled_I2CwritePixel(0b00011111);
    }
    else if(num == '9'){
        oled_setCursor(startingRow, startingCol);
        oled_I2CwritePixel(0b11110000);
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b11110000);
        oled_setCursor(startingRow+1, startingCol);
        oled_I2CwritePixel(0b00000001);
        oled_I2CwritePixel(0b00000001);
        oled_I2CwritePixel(0b00000001);
        oled_I2CwritePixel(0b00000001);
        oled_I2CwritePixel(0b00011111);
    }
    else if(num == '_'){
        oled_setCursor(startingRow, startingCol);
        oled_I2CwritePixel(0b00000000);
        oled_I2CwritePixel(0b00000000);
        oled_I2CwritePixel(0b00000000);
        oled_I2CwritePixel(0b00000000);
        oled_I2CwritePixel(0b00000000);
        oled_setCursor(startingRow+1, startingCol);
        oled_I2CwritePixel(0b00000000);
        oled_I2CwritePixel(0b00000000);
        oled_I2CwritePixel(0b00000000);
        oled_I2CwritePixel(0b00000000);
        oled_I2CwritePixel(0b00000000);
    }
    else{
        return -1;
    }
    
    return 0;
}

int oled_drawSingleLetter(char letter){
    if(letter == 'a'){
        oled_I2CwritePixel(0b01111100);
        oled_I2CwritePixel(0b00010100);
        oled_I2CwritePixel(0b01111100);
    }
    else if(letter == 'b'){
        oled_I2CwritePixel(0b01111100);
        oled_I2CwritePixel(0b01010100);
        oled_I2CwritePixel(0b00101000);
    }
    else if(letter == 'c'){
        oled_I2CwritePixel(0b01111100);
        oled_I2CwritePixel(0b01000100);
        oled_I2CwritePixel(0b01000100);
    }
    else if(letter == 'd'){
        oled_I2CwritePixel(0b01111100);
        oled_I2CwritePixel(0b01000100);
        oled_I2CwritePixel(0b00111000);
    }
    else if(letter == 'e'){
        oled_I2CwritePixel(0b01111100);
        oled_I2CwritePixel(0b01010100);
        oled_I2CwritePixel(0b01000100);
    }
    else if(letter == 'f'){
        oled_I2CwritePixel(0b01111100);
        oled_I2CwritePixel(0b00010100);
        oled_I2CwritePixel(0b00010100);
    }
    else if(letter == 'g'){
        oled_I2CwritePixel(0b01111100);
        oled_I2CwritePixel(0b01010100);
        oled_I2CwritePixel(0b01110100);
    }
    else if(letter == 'h'){
        oled_I2CwritePixel(0b01111100);
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b01111100);
    }
    else if(letter == 'i'){
        oled_I2CwritePixel(0b01000100);
        oled_I2CwritePixel(0b01111100);
        oled_I2CwritePixel(0b01000100);
    }
    else if(letter == 'j'){
        oled_I2CwritePixel(0b01000100);
        oled_I2CwritePixel(0b01111100);
        oled_I2CwritePixel(0b00000100);
    }
    else if(letter == 'k'){
        oled_I2CwritePixel(0b01111100);
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b01101100);
    }
    else if(letter == 'l'){
        oled_I2CwritePixel(0b01111100);
        oled_I2CwritePixel(0b01000000);
        oled_I2CwritePixel(0b01000000);
    }
    else if(letter == 'm'){
        oled_I2CwritePixel(0b01111100);
        oled_I2CwritePixel(0b00001000);
        oled_I2CwritePixel(0b01111100);
    }
    else if(letter == 'n'){
        oled_I2CwritePixel(0b01111100);
        oled_I2CwritePixel(0b00000100);
        oled_I2CwritePixel(0b01111100);
    }
    else if(letter == 'o'){
        oled_I2CwritePixel(0b01111100);
        oled_I2CwritePixel(0b01000100);
        oled_I2CwritePixel(0b01111100);
    }
    else if(letter == 'p'){
        oled_I2CwritePixel(0b01111100);
        oled_I2CwritePixel(0b00010100);
        oled_I2CwritePixel(0b00011100);
    }
    else if(letter == 'q'){
        oled_I2CwritePixel(0b00111100);
        oled_I2CwritePixel(0b00100100);
        oled_I2CwritePixel(0b01011100);
    }
    else if(letter == 'r'){
        oled_I2CwritePixel(0b01111100);
        oled_I2CwritePixel(0b00110100);
        oled_I2CwritePixel(0b01011100);
    }
    else if(letter == 's'){
        oled_I2CwritePixel(0b01011100);
        oled_I2CwritePixel(0b01010100);
        oled_I2CwritePixel(0b01110100);
    }
    else if(letter == 't'){
        oled_I2CwritePixel(0b00000100);
        oled_I2CwritePixel(0b01111100);
        oled_I2CwritePixel(0b00000100);
    }
    else if(letter == 'u'){
        oled_I2CwritePixel(0b01111100);
        oled_I2CwritePixel(0b01000000);
        oled_I2CwritePixel(0b01111100);
    }
    else if(letter == 'v'){
        oled_I2CwritePixel(0b00111100);
        oled_I2CwritePixel(0b01000000);
        oled_I2CwritePixel(0b00111100);
    }
    else if(letter == 'w'){
        oled_I2CwritePixel(0b01111100);
        oled_I2CwritePixel(0b00100000);
        oled_I2CwritePixel(0b01111100);
    }
    else if(letter == 'x'){
        oled_I2CwritePixel(0b01101100);
        oled_I2CwritePixel(0b00010000);
        oled_I2CwritePixel(0b01101100);
    }
    else if(letter == 'y'){
        oled_I2CwritePixel(0b00001100);
        oled_I2CwritePixel(0b01110000);
        oled_I2CwritePixel(0b00001100);
    }
    else if(letter == 'z'){
        oled_I2CwritePixel(0b01100100);
        oled_I2CwritePixel(0b01010100);
        oled_I2CwritePixel(0b01001100);
    }
    else{
        return -1;
    }
    
    return 0;
}
