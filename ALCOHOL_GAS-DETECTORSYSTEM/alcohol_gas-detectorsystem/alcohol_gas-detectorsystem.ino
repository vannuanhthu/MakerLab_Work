/*
   
*/
#include "Wire.h"
#include "LiquidCrystal_I2C.h"

// Dat ten chan cong ket noi
#define   ALCOHOL_PIN       A1 
#define   GAS_PIN           A2 
#define   BUZZER_PIN        A3
#define   LED_YELLOW_PIN    D10
#define   LED_GREEN_PIN     D11

// Dat cac gia tri nguong 
#define   ALCOL_LIMIT1      200
#define   GAS_LIMIT1        600
#define   ALCOL_LIMIT2      150
#define   GAS_LIMIT2        100

LiquidCrystal_I2C LCD(0x27, 16, 2); // Thiet lap dia chi LCD 0x27 de hien thi ky tu tren 16 va hai dong

// Khai bao bien 
int gasValue  = 0;
int alcoValue = 0;

void setup() {
  Serial.begin(9600); 
  LCD.init();       //Khoi tao LCD 1602 de hien thi
  LCD.backlight();  //Bat den nen LCD 1602

  // Thiet lap LED va BUZZER o trang thai OUTPUT
  pinMode(LED_RED_PIN, OUTPUT); 
  pinMode(LED_YELLOW_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // Doc gia tri cam bien tu chan Analog
  int gasValue = analogRead(GAS_PIN);
  int alcoValue = analogRead(ALCOHOL_PIN);
  delay(100); 
  // Hien thi gia tri khi gas va nong do con
  LCD.setCursor(0, 0);
  LCD.print("Gas ");
  LCD.setCursor(0, 1);
  LCD.print(gasValue);
  LCD.setCursor(9, 0);
  LCD.print("Alcohol ");
  LCD.setCursor(9, 1);
  LCD.print(alcoValue);
  // So sanh cac gia tri nguong 
  if ((alcoValue < ALCOL_LIMIT2) && (gasValue < GAS_LIMIT2)) {
    //Ham canh bao trang thai an toan
  }
  if (((alcoValue <= ALCOL_LIMIT1) && (alcoValue > ALCOL_LIMIT2)) || ((gasValue <= GAS_LIMIT1) && (gasValue > GAS_LIMIT2))) {
    //Ham canh bao trang thai nguy hiem
    DangerAir();
  }
  if ((alcoValue > ALCOL_LIMIT1) && (gasValue > GAS_LIMIT1)) {
    //Ham canh bao trang thai rat nguy hiem
    VeryDangerAir();
  }
}

void SafeAir() {
  //Tat cac canh bao
  digitalWrite(LED_GREEN_PIN, HIGH);
  digitalWrite(LED_YELLOW_PIN, LOW);
  digitalWrite(LED_RED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
}

void DangerAir() {
  //Bat cac canh bao
  digitalWrite(LED_GREEN_PIN, HIGH);
  digitalWrite(LED_YELLOW_PIN, HIGH);
  digitalWrite(LED_RED_PIN, LOW);
  digitalWrite(BUZZER_PIN, HIGH);
  delay(300);

  //Tat cac canh bao
  digitalWrite(LED_GREEN_PIN, LOW);
  digitalWrite(LED_YELLOW_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  // delay(50);
}

void VeryDangerAir() {
  //Bat cac canh bao
  digitalWrite(LED_GREEN_PIN, HIGH);
  digitalWrite(LED_YELLOW_PIN, HIGH);
  digitalWrite(LED_RED_PIN, HIGH);
  digitalWrite(BUZZER_PIN, HIGH);
  delay(100);

  //Tat cac canh bao
  digitalWrite(LED_GREEN_PIN, LOW);
  digitalWrite(LED_YELLOW_PIN, LOW);
  digitalWrite(LED_RED_PIN, LOW);
  // delay(50);
}
