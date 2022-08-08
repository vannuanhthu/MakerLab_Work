
// Include library
#include "UltraSonicDistanceSensor.h"
#include "Wire.h"
#include "LiquidCrystal_I2C.h"

// Define connected pin
// Dat ten chan cong ket noi
#define TRIG_PIN          13
#define ECHO_PIN          12
#define LED_RED_PIN       A1
#define LED_YELLOW_PIN    A2
#define LED_GREEN_PIN     A3
#define BUZZER_PIN        D9

// Set distance range
// Thiet lap gia tri cho cac khoang cach
#define int_safe_dist     40
#define int_danger_dist   25
#define int_crash_dist    10

UltraSonicDistanceSensor distanceSensor(TRIG_PIN, ECHO_PIN);  // Initialize sensor that uses digital pins 13 and 12 // Khoi tao chan ket noi digital 12 va 13 cho cam bien sieu am

LiquidCrystal_I2C LCD(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// Khai bao bien
int int_dist = 0;

void setup() {
  // We initialize serial connection so that we could print values from sensor
  Serial.begin(9600); 
  // Initialize LCD 1602 to display
  // Khoi tao LCD 1602 de hien thi
  LCD.init();    
  // Turn on LCD backlight  
  // Bat den nen LCD 1602    
  LCD.backlight();    
  // Set LED and Buzzer as output pin
  // Thiet lap LED va BUZZER o trang thai OUTPUT
  pinMode(LED_RED_PIN, OUTPUT); 
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // Every 500 miliseconds, do a measurement using the sensor and print the distance in centimeters
  // Moi 500ms tien hanh do va hien thi khoang cach 1 lan
  delay(500);
  if (distanceSensor.available() == true) {
    // Print distance measured by sensor at column 1 and row 1
    LCD.setCursor(0, 0);
    int_dist = floor(distanceSensor.getcm());
    LCD.print("Distance: ");
    LCD.print(int_dist);
    LCD.print("cm");
    LCD.setCursor(0, 1);
  }
  // Print status of distance
  if (int_dist > int_safe_dist) {
    LCD.print("AN TOAN      "); 
    SafeDist();
  }

  if ((int_dist <= int_safe_dist) && (int_dist > int_danger_dist)) {
    //LCD.setCursor(0, 1);
    LCD.print("CO VAT CAN  ");
    DangerDist1();
  }

  if ((int_dist <= int_danger_dist) && (int_dist > int_crash_dist)) {
    LCD.print("SAP VA CHAM  ");
    DangerDist2();
  }

  if (int_dist <= int_crash_dist) {
    LCD.print("VA CHAM      ");
    CrashDist();
  }
}

void SafeDist() {
  // Turn off warning Led
  //Tat cac canh bao
  digitalWrite(LED_GREEN_PIN, LOW);
  digitalWrite(LED_YELLOW_PIN, LOW);
  digitalWrite(LED_RED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
}

void DangerDist1() {
  // Turn on warning Led
  //Bat cac canh bao
  digitalWrite(LED_GREEN_PIN, HIGH);
  digitalWrite(LED_YELLOW_PIN, LOW);
  digitalWrite(LED_RED_PIN, LOW);
  // Set PWM value
  // Dat gia tri PWM de dieu chinh am luong BUZZER 60%
  analogWrite(BUZZER_PIN, 153); 
  delay(300);

  // Turn off warning Led
  //Tat cac canh bao
  digitalWrite(LED_GREEN_PIN, LOW);
  // Set PWM value
  // Dat gia tri PWM de dieu chinh am luong BUZZER 0%
  analogWrite(BUZZER_PIN, 0);
  // delay(50);
}

void DangerDist2() {
  // Turn on warning Led
  //Bat cac canh bao
  digitalWrite(LED_GREEN_PIN, HIGH);
  digitalWrite(LED_YELLOW_PIN, HIGH);
  digitalWrite(LED_RED_PIN, LOW);
  // Set PWM value
  // Dat gia tri PWM de dieu chinh am luong BUZZER 80%
  analogWrite(BUZZER_PIN, 204); 
  delay(100);

  // Turn off warning Led
  //Tat cac canh bao
  digitalWrite(LED_GREEN_PIN, LOW);
  digitalWrite(LED_YELLOW_PIN, LOW);
  // Set PWM value
  // Dat gia tri PWM de dieu chinh am luong BUZZER 0%
  analogWrite(BUZZER_PIN, 0); 
  // delay(50);
}

void CrashDist() {
  // Turn on warning Led
  //Bat cac canh bao
  digitalWrite(LED_GREEN_PIN, HIGH);
  digitalWrite(LED_YELLOW_PIN, HIGH);
  digitalWrite(LED_RED_PIN, HIGH);
  // Set PWM value
  // Dat gia tri PWM de dieu chinh am luong BUZZER 100%
  analogWrite(BUZZER_PIN, 255); 
}
