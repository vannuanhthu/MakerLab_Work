// Include library
#include "Wire.h"
#include "LiquidCrystal_I2C.h"
// Define connected pin
// Dat ten chan cong ket noi
#define   ALCOHOL_PIN       A1 
#define   GAS_PIN           A2 
#define   BUZZER_PIN        A3
#define   LED_YELLOW_PIN    D10
#define   LED_GREEN_PIN     D11
// Set gas and alcohol limt
// Dat cac gia tri nguong 
#define   ALCOL_LIMIT1      200
#define   GAS_LIMIT1        600
#define   ALCOL_LIMIT2      150
#define   GAS_LIMIT2        100
// Set the LCD address to 0x27 for a 16 chars and 2 line display
// Thiet lap dia chi LCD 0x27 de hien thi ky tu LCD 16 ký tự và 2 dòng
LiquidCrystal_I2C LCD(0x27, 16, 2); 
// Declare variables
// Khai bao bien 
int gasValue  = 0;
int alcoValue = 0;

void setup() {
 // We initialize serial connection so that we could print values from sensor
  // Khoi tao cong ket noi noi tiep
  Serial.begin(9600);
  // Initialize LCD 1602 to display
  // Khoi tao LCD 1602 de hien thi
  LCD.init();  
  // Turn on LCD backlight   
  // Bat den nen LCD 1602    
  LCD.backlight();
  // Thiet lap LED va BUZZER o trang thai OUTPUT
  pinMode(LED_RED_PIN, OUTPUT); 
  pinMode(LED_YELLOW_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // Read gas and alcohol value 
  // Doc gia tri cam bien khi gas va nong do con
  int gasValue = analogRead(GAS_PIN);
  int alcoValue = analogRead(ALCOHOL_PIN);
  delay(100); 
  // Print gas and alcohol value on LCD at column 1 and row 1
  // Hien thi gia tri khi gas va nong do con
  LCD.setCursor(0, 0);
  LCD.print("Gas ");
  LCD.setCursor(0, 1);
  LCD.print(gasValue);
  LCD.setCursor(9, 0);
  LCD.print("Alcohol ");
  LCD.setCursor(9, 1);
  LCD.print(alcoValue);
  // Compare current gas and alcohol value to their limitt
  // So sanh cac gia tri nguong 
  if ((alcoValue < ALCOL_LIMIT2) && (gasValue < GAS_LIMIT2)) {
    // Safe state function
    // Ham canh bao trang thai an toan
    SafeAir();
  }
  if (((alcoValue <= ALCOL_LIMIT1) && (alcoValue > ALCOL_LIMIT2)) || ((gasValue <= GAS_LIMIT1) && (gasValue > GAS_LIMIT2))) {
    // Danger state function
    // Ham canh bao trang thai nguy hiem
    DangerAir();
  }
  if ((alcoValue > ALCOL_LIMIT1) && (gasValue > GAS_LIMIT1)) {
    // Very danger state function
    //Ham canh bao trang thai rat nguy hiem
    VeryDangerAir();
  }
}

void SafeAir() {
  // Turn off warning
  // Tat cac canh bao
  digitalWrite(LED_GREEN_PIN, HIGH);
  digitalWrite(LED_YELLOW_PIN, LOW);
  digitalWrite(LED_RED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
}

void DangerAir() {
  // Turn on warning Led
  // Bat cac canh bao
  digitalWrite(LED_GREEN_PIN, HIGH);
  digitalWrite(LED_YELLOW_PIN, HIGH);
  digitalWrite(LED_RED_PIN, LOW);
  digitalWrite(BUZZER_PIN, HIGH);
  delay(300);
  digitalWrite(LED_GREEN_PIN, LOW);
  digitalWrite(LED_YELLOW_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
}

void VeryDangerAir() {
  // Turn on warning Led
  // Bat cac canh bao
  digitalWrite(LED_GREEN_PIN, HIGH);
  digitalWrite(LED_YELLOW_PIN, HIGH);
  digitalWrite(LED_RED_PIN, HIGH);
  digitalWrite(BUZZER_PIN, HIGH);
  delay(100);
  //Tat cac canh bao
  digitalWrite(LED_GREEN_PIN, LOW);
  digitalWrite(LED_YELLOW_PIN, LOW);
  digitalWrite(LED_RED_PIN, LOW);
}
