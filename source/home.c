#include "home.h"

void home_drawScreen(){
    displayingHomeScreen = true;
    
    // N
    home_drawAppWithoutBox(0);
    
    // C
    home_drawAppWithoutBox(1);
    
    // S
    home_drawAppWithoutBox(2);
    
    // R
    home_drawAppWithoutBox(3);
    
    // Logo
    oled_setCursor(0, 56);
    oled_I2CwritePixel(0b11100000);
    oled_setCursor(1, 56);
    oled_I2CwritePixel(0b00000110);
    oled_setCursor(0, 57);
    oled_I2CwritePixel(0b01000000);
    oled_setCursor(1, 57);
    oled_I2CwritePixel(0b00000110);
    oled_setCursor(0, 58);
    oled_I2CwritePixel(0b11100000);
    oled_setCursor(1, 58);
    oled_I2CwritePixel(0b00000110);
    oled_setCursor(1, 59);
    oled_I2CwritePixel(0b00000110);
    oled_setCursor(0, 60);
    oled_I2CwritePixel(0b11100000);
    oled_setCursor(1, 60);
    oled_I2CwritePixel(0b00000110);
    oled_setCursor(0, 61);
    oled_I2CwritePixel(0b01000000);
    oled_setCursor(1, 61);
    oled_I2CwritePixel(0b00000110);
    oled_setCursor(0, 62);
    oled_I2CwritePixel(0b11100000);
    oled_setCursor(1, 62);
    oled_I2CwritePixel(0b00000110);
    
    // Clock
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
    
    // AppBox()
    home_drawCurrentAppBox();
}

void home_drawAppWithoutBox(int num){
    // Calls oled_drawAppWithoutBox, right shifting to correct home screen location
    oled_drawAppWithoutBox(num, 14*num);
}

void home_drawCurrentAppBox(){
    // Draw inner box edges
    oled_setCursor(0, 1 + (14*appNum));
    oled_I2CwritePixel(0b11111100);
    oled_setCursor(1, 1 + (14*appNum));
    oled_I2CwritePixel(0b00111111);
    oled_setCursor(0, 2 + (14*appNum));
    oled_I2CwritePixel(0b00001100);
    oled_setCursor(1, 2 + (14*appNum));
    oled_I2CwritePixel(0b00110000);
    oled_setCursor(0, 9 + (14*appNum));
    oled_I2CwritePixel(0b00001100);
    oled_setCursor(1, 9 + (14*appNum));
    oled_I2CwritePixel(0b00110000);
    oled_setCursor(0, 10 + (14*appNum));
    oled_I2CwritePixel(0b11111100);
    oled_setCursor(1, 10 + (14*appNum));
    oled_I2CwritePixel(0b00111111);
    
    // Draw outer box edges
    oled_setCursor(0, 0 + (14*appNum));
    oled_I2CwritePixel(0b11111100);
    oled_setCursor(1, 0 + (14*appNum));
    oled_I2CwritePixel(0b00111111);
    oled_setCursor(0, 11 + (14*appNum));
    oled_I2CwritePixel(0b11111100);
    oled_setCursor(1, 11 + (14*appNum));
    oled_I2CwritePixel(0b00111111);
    
    
    // N
    if(appNum == 0){
        oled_setCursor(0, 3);
        oled_I2CwritePixel(0b11101100);
        oled_setCursor(1, 3);
        oled_I2CwritePixel(0b00110111);
        oled_setCursor(0, 4);
        oled_I2CwritePixel(0b01001100);
        oled_setCursor(1, 4);
        oled_I2CwritePixel(0b00110000);
        oled_setCursor(0, 5);
        oled_I2CwritePixel(0b10001100);
        oled_setCursor(1, 5);
        oled_I2CwritePixel(0b00110000);
        oled_setCursor(0, 6);
        oled_I2CwritePixel(0b00001100);
        oled_setCursor(1, 6);
        oled_I2CwritePixel(0b00110001);
        oled_setCursor(0, 7);
        oled_I2CwritePixel(0b00001100);
        oled_setCursor(1, 7);
        oled_I2CwritePixel(0b00110010);
        oled_setCursor(0, 8);
        oled_I2CwritePixel(0b11101100);
        oled_setCursor(1, 8);
        oled_I2CwritePixel(0b00110111);
    }

    
    // C
    if(appNum == 1){
        oled_setCursor(0, 17);
        oled_I2CwritePixel(0b11101100);
        oled_setCursor(1, 17);
        oled_I2CwritePixel(0b00110111);
        oled_setCursor(0, 18);
        oled_I2CwritePixel(0b00101100);
        oled_setCursor(1, 18);
        oled_I2CwritePixel(0b00110100);
        oled_setCursor(0, 19);
        oled_I2CwritePixel(0b00101100);
        oled_setCursor(1, 19);
        oled_I2CwritePixel(0b00110100);
        oled_setCursor(0, 20);
        oled_I2CwritePixel(0b00101100);
        oled_setCursor(1, 20);
        oled_I2CwritePixel(0b00110100);
        oled_setCursor(0, 21);
        oled_I2CwritePixel(0b00101100);
        oled_setCursor(1, 21);
        oled_I2CwritePixel(0b00110100);
        oled_setCursor(0, 22);
        oled_I2CwritePixel(0b00101100);
        oled_setCursor(1, 22);
        oled_I2CwritePixel(0b00110100);
    }
    
    // S
    if(appNum == 2){
        oled_setCursor(0, 31);
        oled_I2CwritePixel(0b11101100);
        oled_setCursor(1, 31);
        oled_I2CwritePixel(0b00110101);
        oled_setCursor(0, 32);
        oled_I2CwritePixel(0b00101100);
        oled_setCursor(1, 32);
        oled_I2CwritePixel(0b00110101);
        oled_setCursor(0, 33);
        oled_I2CwritePixel(0b00101100);
        oled_setCursor(1, 33);
        oled_I2CwritePixel(0b00110101);
        oled_setCursor(0, 34);
        oled_I2CwritePixel(0b00101100);
        oled_setCursor(1, 34);
        oled_I2CwritePixel(0b00110101);
        oled_setCursor(0, 35);
        oled_I2CwritePixel(0b00101100);
        oled_setCursor(1, 35);
        oled_I2CwritePixel(0b00110101);
        oled_setCursor(0, 36);
        oled_I2CwritePixel(0b00101100);
        oled_setCursor(1, 36);
        oled_I2CwritePixel(0b00110111);
    }
    
    // R
    if(appNum == 3){
       oled_setCursor(0, 45);
        oled_I2CwritePixel(0b00001100);
        oled_setCursor(1, 45);
        oled_I2CwritePixel(0b00110000);
        oled_setCursor(0, 46);
        oled_I2CwritePixel(0b11101100);
        oled_setCursor(1, 46);
        oled_I2CwritePixel(0b00110111);
        oled_setCursor(0, 47);
        oled_I2CwritePixel(0b10101100);
        oled_setCursor(1, 47);
        oled_I2CwritePixel(0b00110001);
        oled_setCursor(0, 48);
        oled_I2CwritePixel(0b10101100);
        oled_setCursor(1, 48);
        oled_I2CwritePixel(0b00110010);
        oled_setCursor(0, 49);
        oled_I2CwritePixel(0b11101100);
        oled_setCursor(1, 49);
        oled_I2CwritePixel(0b00110100);
        oled_setCursor(0, 50);
        oled_I2CwritePixel(0b00001100);
        oled_setCursor(1, 50);
        oled_I2CwritePixel(0b00110000);
    }
}
