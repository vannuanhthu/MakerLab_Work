/*
  
*/
#include "Wire.h"
#include "LiquidCrystal_I2C.h"

// Declare input ADC pin
#define  LDR_PIN    A3

//Xac dinh cong ket noi chan LED va BUZZER
#define LED_RED_PIN       D11
#define LED_YELLOW_PIN    D10
#define LED_GREEN_PIN     D9
#define LED_STREET_PIN    A1

LiquidCrystal_I2C LCD(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup(){
  
  LCD.init();         // Initialize LCD 1602 to display
  LCD.backlight();    // Turn on LCD backlight
  Serial.begin(9600);
  // Set LED and Buzzer as output pin
  // Thiet lap LED va BUZZER o trang thai OUTPUT
  pinMode(LED_RED_PIN, OUTPUT); 
  pinMode(LED_YELLOW_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_STREET_PIN, OUTPUT);
}

void loop() {
  int count1 = 7;
  digitalWrite(LED_GREEN_PIN, HIGH);
  digitalWrite(LED_YELLOW_PIN, LOW);
  digitalWrite(LED_RED_PIN, LOW);
  for(int i = 0; i < 7; i++) {
    for(int j = 0; j < 10; j++) {
      int LRDValue = analogRead(LDR_PIN);
      LCD.setCursor(0, 0);
      LCD.print("TRAFFIC");
      LCD.setCursor(8, 0);
      LCD.print("|");
      LCD.setCursor(10, 0);
      LCD.print("STREET");
      LCD.setCursor(0, 1);
      LCD.print(count1);
      LCD.setCursor(8, 1);
      LCD.print("|");
      LCD.setCursor(10, 1);
      LCD.print((LRDValue));
      LCD.print(("  "));
      if(LRDValue > 150){
        digitalWrite(LED_STREET_PIN, HIGH);
      }
      else{
        digitalWrite(LED_STREET_PIN, LOW);
      }
      delay(100);
    }
    count1 -= 1;  
  }
  count1 = 0;
  digitalWrite(LED_GREEN_PIN, LOW);
  digitalWrite(LED_YELLOW_PIN, HIGH);
  digitalWrite(LED_RED_PIN, LOW);
  int count2 = 3;
    for(int i = 0; i < 3; i++) {
      for(int j = 0; j < 10; j++) {
      int LRDValue = analogRead(LDR_PIN);
      LCD.setCursor(0, 0);
      LCD.print("TRAFFIC");
      LCD.setCursor(8, 0);
      LCD.print("|");
      LCD.setCursor(10, 0);
      LCD.print("STREET");
      LCD.setCursor(0, 1);
      LCD.print(count2);
      LCD.setCursor(8, 1);
      LCD.print("|");
      LCD.setCursor(10, 1);
      LCD.print((LRDValue));
      LCD.print(("  "));
      if(LRDValue > 150) {
        digitalWrite(LED_STREET_PIN, HIGH);
      }
      else {
        digitalWrite(LED_STREET_PIN, LOW);
      }
      delay(100);
    }
    count2 -= 1;  
  }
  count2 = 0;
  digitalWrite(LED_GREEN_PIN, LOW);
  digitalWrite(LED_YELLOW_PIN, LOW);
  digitalWrite(LED_RED_PIN, HIGH);
    int count3 = 10;
    for(int i = 0; i < 10; i++) {
     LCD.clear();
     for(int j = 0; j < 10; j++) {
      int LRDValue = analogRead(LDR_PIN);
      LCD.setCursor(0, 0);
      LCD.print("TRAFFIC");
      LCD.setCursor(8, 0);
      LCD.print("|");
      LCD.setCursor(10, 0);
      LCD.print("STREET");
      LCD.setCursor(0, 1);
      LCD.print(count3);
      LCD.setCursor(8, 1);
      LCD.print("|");
      LCD.setCursor(10, 1);
      LCD.print((LRDValue));
      LCD.print(("  "));
      if(LRDValue > 150) {
        digitalWrite(LED_STREET_PIN, HIGH);
      }
      else {
        digitalWrite(LED_STREET_PIN, LOW);
      }
      delay(100);
    }
    count3 -= 1;  
  }
  count3 = 0;
  LCD.clear();
}
