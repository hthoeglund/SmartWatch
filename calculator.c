#include "calculator.h"

void calculator_drawScreen(){
    displayingCalculatorScreen = true;
    
    // Draw calculator icon
    oled_drawAppWithoutBox(1, 52);
    
    // Draw previous equations
    calculator_drawPreviousEquations();
}

void calculator_drawDigit(char button){
    // If there are 13 digits, cannot place a new digit
    if(currentEquationDigit > 13){
        return;
    }
    
    // Set cursor
    oled_setCursor(0 + 2*currentEquationIndex, 0 + 4*currentEquationDigit);
    
    // If # pressed and NOT in cycle and already have an operator
    if(button == '#' && !calculatorCycleLastPressed && currentOperatorDigit != -1 && currentOperatorDigit != 0){
        return;
    }
    else if(button == '*' && currentOperatorDigit != -1){
        return;
    }
    // If # pressed (a first time)
    else if(button == '#'){
        // Draw operator
        oled_drawSingleSmallNum(calculatorCycle[calculatorCycleNum]);
        
        // Update equation string
        equations[currentEquationIndex][currentEquationDigit] = '+';
        
        // If at the end of the cycle, reset cycleNum
        if(calculatorCycleNum == 3){
            calculatorCycleNum = -1;
        }
        
        // Store the operator's location
        currentOperatorDigit = currentEquationDigit;
        
        // Iterate to next cycle num, and # is last button pressed
        calculatorCycleNum++;
        calculatorCycleLastPressed = true;
    }
    else{
        // If # was the last button pressed,
        if(calculatorCycleLastPressed){
            // Increment digit and cursor
            currentEquationDigit++;
            oled_setCursor(0 + 2*currentEquationIndex, 0 + 4*currentEquationDigit);
            
            // Reset cycle variables
            calculatorCycleLastPressed = false;
            calculatorCycleNum = 0;
        }
        
        if(button == '*'){
            // Store the operator's location
            currentOperatorDigit = currentEquationDigit;
        }
        
        // Adjust equation string accordingly
        equations[currentEquationIndex][currentEquationDigit] = button;
        
        // Draw Number or *
        oled_drawSingleSmallNum(button);
        
        // Iterate to next digit
        currentEquationDigit++;
    }
}

void calculator_clearDigit(){
    // If cycle was not last pressed, decrement currentEquationDigit
    if(!calculatorCycleLastPressed){
        currentEquationDigit--;
    }
    // Otherwise, reset cycle variables
    else{
        calculatorCycleLastPressed = false;
        calculatorCycleNum = 0;
    }
    
    // If clearing the operator, adjust currentOperatorDigit
    if(currentEquationDigit == currentOperatorDigit){
        currentOperatorDigit = -1;
    }
    
    // If there is not anything to delete
    if(currentEquationDigit < 0){
        return;
    }
    
    // Clear digit in equation string
    equations[currentEquationIndex][currentEquationDigit] = '\0';
    
    // Clear three rows
    oled_setCursor(0 + 2*currentEquationIndex, 0 + 4*currentEquationDigit);
    oled_I2CwritePixel(0b00000000);
    oled_I2CwritePixel(0b00000000);
    oled_I2CwritePixel(0b00000000);
}

void calculator_drawPreviousEquations(){
    // For each equation
    for(int eq = 0; eq < 2; eq++){
        // Set cursor to start of equation
        oled_setCursor(0 + 2*eq, 0);

        // For each equation digit
        for(int digit = 0; digit < 13; digit++){
            oled_setCursor(0 + 2*eq, 0 + 4*digit);
            oled_drawSingleSmallNum(equations[eq][digit]);
        }
        
        // For each result digit (using different for loop so it looks nice on oled)
        for(int digit = 0; digit < 13; digit++){
            oled_setCursor(1 + 2*eq, 0 + 4*digit);
            oled_drawSingleSmallNum(solutions[eq][digit]);
        }
    }
}

void calculator_clearPreviousEquations(){
    // For each equation
    for(int eq = 0; eq <= 5; eq++){
        // Set cursor to start of equation
        oled_setCursor(0 + eq, 0);

        // For each digit
        for(int digit = 0; digit < 13; digit++){
            oled_setCursor(0 + eq, 0 + 4*digit);
            oled_I2CwritePixel(0b00000000);
            oled_I2CwritePixel(0b00000000);
            oled_I2CwritePixel(0b00000000);
        }
    }
}

long int calculator_solve(){
    // Set currentEquation to equations[currentEquationIndex]
    char currentEquation[13] = {};
    strncpy(currentEquation, (const char *)equations[currentEquationIndex], 13);
    
    // If first number is negative
    if(equations[currentEquationIndex][0] == '-'){
        // Make first character space instead of -
        currentEquation[0] = ' ';
    }
    
    // Use strtok to find operands and operation
    char* operand1String = strtok(currentEquation, "+-/*");
    char operation = equations[currentEquationIndex][strlen(operand1String)];
    char* operand2String = strtok(NULL, "+-/*");
    
    // If either operand is blank or the operands are too big, fail
    if(operand1String == NULL || operand2String == NULL  || (strlen(operand1String) + strlen(operand2String)) > 9){
        return -1;
    }
    
    long int operand1 = strtol(operand1String, NULL, 10);
    // If first number is negative, multiply by -1
    if(equations[currentEquationIndex][0] == '-'){
        operand1 *= -1;
    }
    
    long int operand2 = strtol(operand2String, NULL, 10);
 
    // Otherwise, solve the equation
    long int result;
    if(operation == '+'){
        result = operand1 + operand2;
    }
    else if(operation == '-'){
        result = operand1 - operand2;
    }
    else if(operation == '*'){
       result = operand1 * operand2;
    }
    else if(operation == '/'){
        if(operand2 == 0){
            return -1;
        }
        result = operand1 / operand2;
    }
    else{
         return -1;
    }
    
    // Convert result to string
    char ret[12];
    sprintf(ret, "%ld", result);
    
    // Update solutions with =
    solutions[currentEquationIndex][0] = '=';

    // Add result to solutions string and return it
    strcpy((char*)solutions[currentEquationIndex]+1, ret); 
    
    // Display solution
    for(int i = 0; i < 13; i++){
        oled_setCursor(1 + 2*currentEquationIndex, 0 + 4*i);
        oled_drawSingleSmallNum(solutions[currentEquationIndex][i]);
    }
    
    // If the result is truly -1, then assert that
    if(result == -1){
        actualResultNeg1 = true;
    }
    
    return result;
}

void clearAllEqSols(){
    // Reset all variables
    for(int i = 0; i < sizeof(equations) / sizeof(equations[0]); i++){
        memset((char *)equations[i], 0, 13);
        memset((char *)solutions[i], 0, 13);
    }
    currentEquationIndex = 0;
    currentEquationDigit = 0;
    calculatorCycleNum = 0;
    calculatorCycleLastPressed = false;
    
    // Clear display and redraw
    oled_clearDisplay();
    calculator_drawScreen();
}