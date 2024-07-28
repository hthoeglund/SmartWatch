#include "pin.h"

void pin_drawScreen(){
    displayingPINScreen = true;
    
    // E
    oled_setCursor(0, 5);
    oled_I2CwritePixel(0b11110000);
    oled_setCursor(1, 5);
    oled_I2CwritePixel(0b00011111);
    for(int i = 6; i <= 9; i++){
        oled_setCursor(0, i);
        oled_I2CwritePixel(0b00010000);
        oled_setCursor(1, i);
        oled_I2CwritePixel(0b00010001);
    }
    
    // n
    oled_setCursor(1, 12);
    oled_I2CwritePixel(0b00011111);
    for(int i = 13; i <= 15; i++){
        oled_setCursor(1, i);
        oled_I2CwritePixel(0b00000001);
    }
    oled_setCursor(1, 16);
    oled_I2CwritePixel(0b00011111);
    
    // t
    for(int i = 19; i <= 20; i++){
        oled_setCursor(1, i);
        oled_I2CwritePixel(0b00000010);
    }
    oled_setCursor(1, 21);
    oled_I2CwritePixel(0b00011111);
    for(int i = 22; i <= 23; i++){
        oled_setCursor(1, i);
        oled_I2CwritePixel(0b00000010);
    }
    
    // e
    oled_setCursor(1, 26);
    oled_I2CwritePixel(0b00011111);
    for(int i = 27; i <= 29; i++){
        oled_setCursor(1, i);
        oled_I2CwritePixel(0b00010101);
    }
    oled_setCursor(1, 30);
    oled_I2CwritePixel(0b00010111);
    
    // r
    oled_setCursor(1, 33);
    oled_I2CwritePixel(0b00011111);
    for(int i = 34; i <= 35; i++){
        oled_setCursor(1, i);
        oled_I2CwritePixel(0b0000001);
    }
    
    // P
    oled_setCursor(0, 40);
    oled_I2CwritePixel(0b11110000);
    oled_setCursor(1, 40);
    oled_I2CwritePixel(0b00011111);
    for(int i = 41; i <= 43; i++){
        oled_setCursor(0, i);
        oled_I2CwritePixel(0b00010000);
        oled_setCursor(1, i);
        oled_I2CwritePixel(0b00000001);
    }
    oled_setCursor(0, 44);
    oled_I2CwritePixel(0b11110000);
    oled_setCursor(1, 44);
    oled_I2CwritePixel(0b00000001);
        
    // I
    for(int i = 47; i <= 48; i++){
        oled_setCursor(0, i);
        oled_I2CwritePixel(0b00010000);
        oled_setCursor(1, i);
        oled_I2CwritePixel(0b00010000);
    }
    oled_setCursor(0, 49);
        oled_I2CwritePixel(0b11110000);
        oled_setCursor(1, 49);
        oled_I2CwritePixel(0b00011111);
    for(int i = 50; i <= 51; i++){
        oled_setCursor(0, i);
        oled_I2CwritePixel(0b00010000);
        oled_setCursor(1, i);
        oled_I2CwritePixel(0b00010000);
    }
        
    // N
    oled_setCursor(0, 54);
    oled_I2CwritePixel(0b11110000);
    oled_setCursor(1, 54);
    oled_I2CwritePixel(0b00011111);
    oled_setCursor(0, 55);
    oled_I2CwritePixel(0b11000000);
    oled_setCursor(1, 56);
    oled_I2CwritePixel(0b00000001);
    oled_setCursor(1, 57);
    oled_I2CwritePixel(0b00000110);
    oled_setCursor(0, 58);
    oled_I2CwritePixel(0b11110000);
    oled_setCursor(1, 58);
    oled_I2CwritePixel(0b00011111);
    
    // Dashes
    for(int i = 9; i <= 18; i++){
        oled_setCursor(3, i);
        oled_I2CwritePixel(0b01000000);
    }
    for(int i = 21; i <= 30; i++){
        oled_setCursor(3, i);
        oled_I2CwritePixel(0b01000000);
    }
    for(int i = 33; i <= 42; i++){
        oled_setCursor(3, i);
        oled_I2CwritePixel(0b01000000);
    }
    for(int i = 45; i <= 54; i++){
        oled_setCursor(3, i);
        oled_I2CwritePixel(0b01000000);
    } 
}

void pin_drawXScreen(){
    // Top Left to Bottom Right
    oled_setCursor(1, 17);
    oled_I2CwritePixel(0b00000110);
    
    // Top Right to Bottom Left
    oled_setCursor(1, 46);
    oled_I2CwritePixel(0b00000110);
    
    // Loops to draw all squares
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            oled_setCursor(1 + i, 18 + j + (8 * i));
            oled_I2CwritePixel(0b00001110 << j);
            
            oled_setCursor(1 + i, 45 - j - (8 * i));
            oled_I2CwritePixel(0b00001110 << j);
        }
        
        if(i < 3){
            oled_setCursor(1 + i, 22 + (8 * i));
            oled_I2CwritePixel(0b11100000);
           
            oled_setCursor(1 + i, 41 - (8 * i));
            oled_I2CwritePixel(0b11100000);
        }
        else{
            oled_setCursor(1 + i, 22 + (8 * i));
            oled_I2CwritePixel(0b01100000);
            
            oled_setCursor(1 + i, 41 - (8 * i));
            oled_I2CwritePixel(0b01100000);
        }  
    }
    // Edge cases
    for(int i = 0; i < 3; i++){
        // Top Left to Bottom Right
        oled_setCursor(1 + i, 23 + (8 * i));
        oled_I2CwritePixel(0b11000000);
        oled_setCursor(2 + i, 23 + (8 * i));
        oled_I2CwritePixel(0b00000001);
        oled_setCursor(1 + i, 24 + (8 * i));
        oled_I2CwritePixel(0b10000000);
        oled_setCursor(2 + i, 24 + (8 * i));
        oled_I2CwritePixel(0b000000011);
        oled_setCursor(2 + i, 25 + (8 * i));
        oled_I2CwritePixel(0b000000111);
        
        // Top Right to Bottom Left
        oled_setCursor(1 + i, 40 - (8 * i));
        oled_I2CwritePixel(0b11000000);
        oled_setCursor(2 + i, 40 - (8 * i));
        oled_I2CwritePixel(0b00000001);
        oled_setCursor(1 + i, 39 - (8 * i));
        oled_I2CwritePixel(0b10000000);
        oled_setCursor(2 + i, 39 - (8 * i));
        oled_I2CwritePixel(0b000000011);
        oled_setCursor(2 + i, 38 - (8 * i));
        oled_I2CwritePixel(0b000000111);
    }

    // Center
    oled_setCursor(2, 31);
    oled_I2CwritePixel(0b111000000);
    oled_setCursor(3, 32);
    oled_I2CwritePixel(0b000000011);
}

void pin_drawCheckScreen(){
    // Bottom left of check
    oled_setCursor(3, 12);
    oled_I2CwritePixel(0b01100000);
    oled_setCursor(3, 13);
    oled_I2CwritePixel(0b11100000);
    oled_setCursor(3, 14);
    oled_I2CwritePixel(0b11000000);
    oled_setCursor(4, 14);
    oled_I2CwritePixel(0b00000001);
    oled_setCursor(3, 15);
    oled_I2CwritePixel(0b10000000);
    oled_setCursor(4, 15);
    oled_I2CwritePixel(0b00000011);
    for(int i = 0; i < 6; i++){
        oled_setCursor(4, 16 + i);
        oled_I2CwritePixel(0b00000111 << i);
    }

    // Body of check
    oled_setCursor(1, 51);
    oled_I2CwritePixel(0b00000110);
    // Loops to draw all squares
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 5; j++){
            oled_setCursor(1 + i, 50 - j - (8 * i));
            oled_I2CwritePixel(0b00001110 << j);
        }
    }
    // Edge cases
    for(int i = 0; i < 3; i++){
        oled_setCursor(1 + i, 45 - (8 * i));
        oled_I2CwritePixel(0b11000000);
        oled_setCursor(2 + i, 45 - (8 * i));
        oled_I2CwritePixel(0b00000001);
        oled_setCursor(1 + i, 44 - (8 * i));
        oled_I2CwritePixel(0b10000000);
        oled_setCursor(2 + i, 44 - (8 * i));
        oled_I2CwritePixel(0b000000011);
        oled_setCursor(2 + i, 43 - (8 * i));
        oled_I2CwritePixel(0b000000111);
    }
}

void pin_drawDigit(int num){
    // Draw digit corresponding to num, of PIN screen size
    if(num == 0){
        oled_setCursor(2, 11 + 12*pinNum);
        oled_I2CwritePixel(0b11110000);
        oled_setCursor(3, 11 + 12*pinNum);
        oled_I2CwritePixel(0b01011111);
        for(int i = 0; i < 4; i++){
            oled_setCursor(2, 12 + i + 12*pinNum);
            oled_I2CwritePixel(0b00010000);
            oled_setCursor(3, 12 + i + 12*pinNum);
            oled_I2CwritePixel(0b01010000);
        }
        oled_setCursor(2, 16 + 12*pinNum);
        oled_I2CwritePixel(0b11110000);
        oled_setCursor(3, 16 + 12*pinNum);
        oled_I2CwritePixel(0b01011111);
    }
    else if(num == 1){
        oled_setCursor(2, 16 + 12*pinNum);
        oled_I2CwritePixel(0b11110000);
        oled_setCursor(3, 16 + 12*pinNum);
        oled_I2CwritePixel(0b01011111);
    }
    else if(num == 2){
        oled_setCursor(2, 11 + 12*pinNum);
        oled_I2CwritePixel(0b00010000);
        oled_setCursor(3, 11 + 12*pinNum);
        oled_I2CwritePixel(0b01011111);
        for(int i = 0; i < 4; i++){
            oled_setCursor(2, 12 + i + 12*pinNum);
            oled_I2CwritePixel(0b00010000);
            oled_setCursor(3, 12 + i + 12*pinNum);
            oled_I2CwritePixel(0b01010001);
        }
        oled_setCursor(2, 16 + 12*pinNum);
        oled_I2CwritePixel(0b11110000);
        oled_setCursor(3, 16 + 12*pinNum);
        oled_I2CwritePixel(0b01010001);
    }
    else if(num == 3){
        for(int i = 0; i < 5; i++){
            oled_setCursor(2, 11 + i + 12*pinNum);
            oled_I2CwritePixel(0b00010000);
            oled_setCursor(3, 11 + i + 12*pinNum);
            oled_I2CwritePixel(0b01010001);
        }
        oled_setCursor(2, 16 + 12*pinNum);
        oled_I2CwritePixel(0b11110000);
        oled_setCursor(3, 16 + 12*pinNum);
        oled_I2CwritePixel(0b01011111);
    }
    else if(num == 4){
        oled_setCursor(2, 11 + 12*pinNum);
        oled_I2CwritePixel(0b11110000);
        oled_setCursor(3, 11 + 12*pinNum);
        oled_I2CwritePixel(0b01000001);
        for(int i = 0; i < 4; i++){
            oled_setCursor(2, 12 + i + 12*pinNum);
            oled_I2CwritePixel(0b00000000);
            oled_setCursor(3, 12 + i + 12*pinNum);
            oled_I2CwritePixel(0b01000001);
        }
        oled_setCursor(2, 16 + 12*pinNum);
        oled_I2CwritePixel(0b11110000);
        oled_setCursor(3, 16 + 12*pinNum);
        oled_I2CwritePixel(0b01011111);
    }
    else if(num == 5){
        oled_setCursor(2, 11 + 12*pinNum);
        oled_I2CwritePixel(0b11110000);
        oled_setCursor(3, 11 + 12*pinNum);
        oled_I2CwritePixel(0b01010001);
        for(int i = 0; i < 4; i++){
            oled_setCursor(2, 12 + i + 12*pinNum);
            oled_I2CwritePixel(0b00010000);
            oled_setCursor(3, 12 + i + 12*pinNum);
            oled_I2CwritePixel(0b01010001);
        }
        oled_setCursor(2, 16 + 12*pinNum);
        oled_I2CwritePixel(0b00010000);
        oled_setCursor(3, 16 + 12*pinNum);
        oled_I2CwritePixel(0b01011111);
    }
    else if(num == 6){
        oled_setCursor(2, 11 + 12*pinNum);
        oled_I2CwritePixel(0b11110000);
        oled_setCursor(3, 11 + 12*pinNum);
        oled_I2CwritePixel(0b01011111);
        for(int i = 0; i < 4; i++){
            oled_setCursor(2, 12 + i + 12*pinNum);
            oled_I2CwritePixel(0b00010000);
            oled_setCursor(3, 12 + i + 12*pinNum);
            oled_I2CwritePixel(0b01010001);
        }
        oled_setCursor(2, 16 + 12*pinNum);
        oled_I2CwritePixel(0b00010000);
        oled_setCursor(3, 16 + 12*pinNum);
        oled_I2CwritePixel(0b01011111);
    }
    else if(num == 7){
        for(int i = 0; i < 5; i++){
            oled_setCursor(2, 11 + i + 12*pinNum);
            oled_I2CwritePixel(0b00010000);
        }
        oled_setCursor(2, 16 + 12*pinNum);
        oled_I2CwritePixel(0b11110000);
        oled_setCursor(3, 16 + 12*pinNum);
        oled_I2CwritePixel(0b01011111);
    }
    else if(num == 8){
        oled_setCursor(2, 11 + 12*pinNum);
        oled_I2CwritePixel(0b11110000);
        oled_setCursor(3, 11 + 12*pinNum);
        oled_I2CwritePixel(0b01011111);
        for(int i = 0; i < 4; i++){
            oled_setCursor(2, 12 + i + 12*pinNum);
            oled_I2CwritePixel(0b00010000);
            oled_setCursor(3, 12 + i + 12*pinNum);
            oled_I2CwritePixel(0b01010001);
        }
        oled_setCursor(2, 16 + 12*pinNum);
        oled_I2CwritePixel(0b11110000);
        oled_setCursor(3, 16 + 12*pinNum);
        oled_I2CwritePixel(0b01011111);
    }
    else if(num == 9){
        oled_setCursor(2, 11 + 12*pinNum);
        oled_I2CwritePixel(0b11110000);
        oled_setCursor(3, 11 + 12*pinNum);
        oled_I2CwritePixel(0b01000001);
        for(int i = 0; i < 4; i++){
            oled_setCursor(2, 12 + i + 12*pinNum);
            oled_I2CwritePixel(0b00010000);
            oled_setCursor(3, 12 + i + 12*pinNum);
            oled_I2CwritePixel(0b01000001);
        }
        oled_setCursor(2, 16 + 12*pinNum);
        oled_I2CwritePixel(0b11110000);
        oled_setCursor(3, 16 + 12*pinNum);
        oled_I2CwritePixel(0b01011111);
    }
}

void pin_clearDigit(int index){
    // Clear digit based on index
    for(int i = 0; i < 6; i++){
        oled_setCursor(2, 11 + i + 12*index);
        oled_I2CwritePixel(0b00000000);
        oled_setCursor(3, 11 + i + 12*index);
        oled_I2CwritePixel(0b01000000);
    }
}
