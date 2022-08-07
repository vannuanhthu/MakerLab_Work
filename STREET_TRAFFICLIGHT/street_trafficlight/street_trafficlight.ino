// Include library
#include "Wire.h"
#include "LiquidCrystal_I2C.h"


// Define connected pin
// Dat ten chan cong ket noi
#define LDR_PIN         A3
#define LED_STREET_PIN  A1
#define LED_RED_PIN     D11
#define LED_YELLOW_PIN  D10
#define LED_GREEN_PIN   D9

// Set the LCD address to 0x27 for a 16 chars and 2 line display
// Thiet lap dia chi LCD 0x27 de hien thi 16 ky tu tren hai dong
LiquidCrystal_I2C LCD(0x27, 16, 2); 

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
  // Set LED and BUZZER Pin as Output
  // Thiet lap LED va BUZZER o trang thai OUTPUT
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_YELLOW_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_STREET_PIN, OUTPUT);
}

void loop() {
  // Turn on Green Light and countdown 7s
  // Dem nguoc den xanh 7s
  digitalWrite(LED_GREEN_PIN, HIGH);
  digitalWrite(LED_YELLOW_PIN, LOW);
  digitalWrite(LED_RED_PIN, LOW);
  int count1 = 7;
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 10; j++) {
      int LRDValue = analogRead(LDR_PIN); //
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
      //
      if (LRDValue > 150) {
        digitalWrite(LED_STREET_PIN, HIGH);
      } else {
        digitalWrite(LED_STREET_PIN, LOW);
      }
      delay(100);
    }
    count1 -= 1;
  }
  count1 = 0;
  // Turn on Yellow Light and countdown 3s
  // Dem nguoc den vang 3s
  digitalWrite(LED_GREEN_PIN, LOW);
  digitalWrite(LED_YELLOW_PIN, HIGH);
  digitalWrite(LED_RED_PIN, LOW);
  int count2 = 3;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 10; j++) {
      int LRDValue = analogRead(LDR_PIN); //
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
      //
      if (LRDValue > 150) {
        digitalWrite(LED_STREET_PIN, HIGH);
      } else {
        digitalWrite(LED_STREET_PIN, LOW);
      }
      delay(100);
    }
    count2 -= 1;
  }
  count2 = 0;
  // Turn on Red Light and countdown 10s
  // Dem nguoc den do 10s
  digitalWrite(LED_GREEN_PIN, LOW);
  digitalWrite(LED_YELLOW_PIN, LOW);
  digitalWrite(LED_RED_PIN, HIGH);
  int count3 = 10;
  for (int i = 0; i < 10; i++) {
    LCD.clear();
    for (int j = 0; j < 10; j++) {
      int LRDValue = analogRead(LDR_PIN);//
      LCD.setCursor(0, 0);
      LCD.print("TRAFFIC ");
      LCD.setCursor(8, 0);
      LCD.print("| ");
      LCD.setCursor(10, 0);
      LCD.print("STREET ");
      LCD.setCursor(0, 1);
      LCD.print(count3);
      LCD.setCursor(8, 1);
      LCD.print("| ");
      LCD.setCursor(10, 1);
      LCD.print((LRDValue));
      LCD.print(("  "));
      //
      if (LRDValue > 150) {
        digitalWrite(LED_STREET_PIN, HIGH);
      } else {
        digitalWrite(LED_STREET_PIN, LOW);
      }
      delay(100);
    }
    count3 -= 1;
  }
  count3 = 0;
  LCD.clear();
}
