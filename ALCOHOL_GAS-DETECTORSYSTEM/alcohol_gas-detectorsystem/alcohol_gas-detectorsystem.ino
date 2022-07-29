/*
    How the code work:
        - Read ADC value (0->1023) from pin A1 => Display on Serial Monitor with Baudrate speed 9600.
*/
#include "Wire.h"
#include "LiquidCrystal_I2C.h"

// Declare input ADC pin
#define  ALCOHOL_PIN      A1 
#define  GAS_PIN          A2 

//Xac dinh cong ket noi chan LED va BUZZER
#define LED_RED_PIN       D9
#define LED_YELLOW_PIN    D10
#define LED_GREEN_PIN     D11
#define BUZZER_PIN        A3

LiquidCrystal_I2C LCD(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int gasValue  = 0;
int alcoValue = 0;

// Khai bao gia tri nguong 
int alcol_limit1  = 200;
int gas_limit1    = 600;
int alcol_limit2 = 150;
int gas_limit2   =100;

void setup(){
    Serial.begin(9600);
    LCD.init();         // Initialize LCD 1602 to display
    LCD.backlight();    // Turn on LCD backlight
    // Set LED and Buzzer as output pin
    //Thiet lap LED va BUZZER o trang thai OUTPUT
    pinMode(LED_RED_PIN, OUTPUT); 
    pinMode(LED_YELLOW_PIN, OUTPUT);
    pinMode(LED_GREEN_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
}
void loop(){
    // Read value (0->1023) from analogPin (A1)
    int gasValue = analogRead(GAS_PIN);
    int alcoValue = analogRead(ALCOHOL_PIN);
    delay(100); // Wait 100ms then repeat
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
    if ((alcoValue < alcol_limit2) && (gasValue < gas_limit2)) {
    //Ham trang thai cua LED va Buzzer
    SafeAir();
    }
    if (((alcoValue <= alcol_limit1) && (alcoValue > alcol_limit2)) || ((gasValue <= gas_limit1) && (gasValue > gas_limit2))) {
      //Ham trang thai cua LED va Buzzer
      DangerAir();
    }
    if ((alcoValue > alcol_limit1) && (gasValue > gas_limit1)) {
      //Ham trang thai cua LED va Buzzer
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

void VeryDangerAir(){
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
