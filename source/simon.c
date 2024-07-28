#include "simon.h"

void simon_drawScreen(){
    displayingSimonScreen = true;
    
    // If not running, display "ready?"
    if(!runningSimon){
        oled_setCursor(0, 0);
        oled_drawSingleLetter('r');
        oled_I2CwritePixel(0b00000000);
        oled_drawSingleLetter('e');
        oled_I2CwritePixel(0b00000000);
        oled_drawSingleLetter('a');
        oled_I2CwritePixel(0b00000000);
        oled_drawSingleLetter('d');
        oled_I2CwritePixel(0b00000000);
        oled_drawSingleLetter('y');
        oled_I2CwritePixel(0b00000000);
        oled_drawSingleSmallNum('?');
    }
    // Otherwise, display the score
    else{
        oled_setCursor(0, 0);
        oled_drawSingleLetter('s');
        oled_I2CwritePixel(0b00000000);
        oled_drawSingleLetter('c');
        oled_I2CwritePixel(0b00000000);
        oled_drawSingleLetter('o');
        oled_I2CwritePixel(0b00000000);
        oled_drawSingleLetter('r');
        oled_I2CwritePixel(0b00000000);
        oled_drawSingleLetter('e');
        oled_I2CwritePixel(0b00000000);
        oled_drawSingleSmallNum(':');
        oled_I2CwritePixel(0b00000000);
        oled_drawSingleSmallNum('_');
        oled_I2CwritePixel(0b00000000);
        oled_drawSingleSmallNum('0');
        oled_I2CwritePixel(0b00000000);
    }
    
    // Draw the logo in the top right
    oled_drawAppWithoutBox(2, 52);
}

void simon_initGame(){
    // Generate random colors and fill the "order" variable
    for(int i = 0; i < 20; i++){
        simon_order[i] = rand() % 3;
    }
}

void simon_logInput(int color){
    // Flash LEDs when button is pressed
    if(color == 0){
        PORTC_OUT |= PIN0_bm;
        _delay_ms(25);
        PORTC_OUT &= ~PIN0_bm;
    }
    else if(color == 1){
        PORTC_OUT |= PIN1_bm;
        _delay_ms(25);
        PORTC_OUT &= ~PIN1_bm;
    }
    else{
        PORTD_OUT |= PIN1_bm;
        _delay_ms(25);
        PORTD_OUT &= ~PIN1_bm;
    }
    
    // If color is correct
    if(color == simon_order[currentSimonCount]){
        // Increase score
        currentSimonCount++;
        
        // If they got the new color
        if(currentSimonCount > currentSimonHigh){
            // Reset count and flash colors
            currentSimonCount = 0;
            flashingColors = true;
            
            // Increase score
            currentSimonHigh++;
            
            // Display score
            if(currentSimonHigh < 10){
                oled_setCursor(0, 28);
                oled_drawSingleSmallNum(currentSimonHigh + '0');
            }
            else if(currentSimonHigh < 20){
                oled_setCursor(0, 28);
                oled_drawSingleSmallNum((currentSimonHigh / 10) + '0');
                oled_setCursor(0, 32);
                oled_drawSingleSmallNum((currentSimonHigh % 10) + '0');
            }
            // Otherwise, if they have reached the end
            else{
                // Display final score
                oled_setCursor(0, 28);
                oled_drawSingleSmallNum((currentSimonHigh / 10) + '0');
                oled_setCursor(0, 32);
                oled_drawSingleSmallNum((currentSimonHigh % 10) + '0');

                // Reset Simon variables
                runningSimon = false;
                currentSimonCount = 0;
                currentSimonHigh = 0;
                currentSimonDisplayCount = -1;
                memset((char *)simon_order, 0, 20);

                // Draw Check for success
                pin_drawCheckScreen();

                // Delay so they can see it
                _delay_ms(250);

                // Reset screen
                oled_clearDisplay();
                simon_drawScreen();
            }
        }
    }
    else{
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

        // Draw X for failure
        pin_drawXScreen();
        
        // Delay so they can see it
        _delay_ms(250);
        
        // Reset SS screen
        oled_clearDisplay();
        simon_drawScreen();
    }
}