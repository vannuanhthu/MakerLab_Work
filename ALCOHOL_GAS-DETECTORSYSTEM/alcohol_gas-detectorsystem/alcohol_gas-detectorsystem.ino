/*
    How the code work:
        - Read ADC value (0->1023) from pin A1 => Display on Serial Monitor with Baudrate speed 9600.
*/
#include "Wire.h"
#include "LiquidCrystal_I2C.h"

// Declare input ADC pin
#define  ALCOHOL_PIN    A1 
#define  GAS_PIN        A2 

LiquidCrystal_I2C LCD(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup(){
    Serial.begin(9600);
    LCD.init();         // Initialize LCD 1602 to display
    LCD.backlight();    // Turn on LCD backlight
}
void loop(){
    
    // Read value (0->1023) from analogPin (A1)
    int gasValue = analogRead(GAS_PIN);
    int alcoValue = analogRead(ALCOHOL_PIN);
    // Display value on LCD
    // Hien thi gia tri khi gas và nong do con
    LCD.setCursor(0, 0);
    LCD.print("Gas ");
    LCD.setCursor(0, 1);
    LCD.print(gasValue);
    LCD.setCursor(9, 0);
    LCD.print("Alcohol ");
    LCD.setCursor(9, 1);
    LCD.print(alcoValue);
    delay(100); // Wait 100ms then repeat
}
