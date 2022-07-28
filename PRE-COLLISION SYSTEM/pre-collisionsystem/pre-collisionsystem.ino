/*

*/
#include "UltraSonicDistanceSensor.h"
#include "Wire.h"
#include "LiquidCrystal_I2C.h"

//Xac dinh cong ket noi chan cam bien sieu am
#define TRIG_PIN  13
#define ECHO_PIN  12

//Xac dinh cong ket noi chan LED va BUZZER
#define LED_RED_PIN       A1
#define LED_YELLOW_PIN    A2
#define LED_GREEN_PIN     A3
#define BUZZER_PIN        D9

//Xac dinh gia tri cho cac khoang cach
#define int_safe_dist    40
#define int_danger_dist  25
#define int_crash_dist   10

UltraSonicDistanceSensor distanceSensor(TRIG_PIN, ECHO_PIN);  // Initialize sensor that uses digital pins 13 and 12.

LiquidCrystal_I2C LCD(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int int_dist = 0;

void setup() {
  Serial.begin(9600); // We initialize serial connection so that we could print values from sensor.
  LCD.init();         // Initialize LCD 1602 to display
  LCD.backlight();    // Turn on LCD backlight
  // Set LED and Buzzer as output pin
  //Thiet lap LED va BUZZER o trang thai OUTPUT
  pinMode(LED_RED_PIN, OUTPUT); // pinMode(A1, OUTPUT);
  pinMode(LED_YELLOW_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // Every 500 miliseconds, do a measurement using the sensor and print the distance in centimeters.
  delay(500);
  if (distanceSensor.available() == true) {
    // LCD.clear();
    LCD.setCursor(0, 0);
    int_dist = floor(distanceSensor.getcm());
    LCD.print("Distance: ");
    LCD.print(int_dist);
    LCD.print("cm");
    LCD.setCursor(0, 1);
  }
  if (int_dist > int_safe_dist) {
    // In trang thai khoang cach
   //LCD.setCursor(0, 1);
    LCD.print("AN TOAN      "); 
    //Ham trang thai cua LED va Buzzer
    SafeDist();
  }
  if ((int_dist <= int_safe_dist) && (int_dist > int_danger_dist)) {
    // In trang thai khoang cach
    //LCD.setCursor(0, 1);
    LCD.print("CO VAT CAN  ");
    //Ham trang thai cua LED va Buzzer
    DangerDist1();
  }
  if ((int_dist <= int_danger_dist) && (int_dist > int_crash_dist)) {
    // In trang thai khoang cach
    //LCD.setCursor(0, 1);
    LCD.print("SAP VA CHAM  ");
    //Ham trang thai cua LED va Buzzer
    DangerDist2();
  }
  if (int_dist <= int_crash_dist) {
    // In trang thai khoang cach
    //LCD.setCursor(0, 1);
    LCD.print("VA CHAM      ");
    //Ham trang thai cua LED va Buzzer
    CrashDist();
  }
}

void SafeDist() {
  //Tat cac canh bao
  digitalWrite(LED_GREEN_PIN, LOW);
  digitalWrite(LED_YELLOW_PIN, LOW);
  digitalWrite(LED_RED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
}

void DangerDist1() {
  //Bat cac canh bao
  digitalWrite(LED_GREEN_PIN, HIGH);
  digitalWrite(LED_YELLOW_PIN, LOW);
  digitalWrite(LED_RED_PIN, LOW);
  //digitalWrite(BUZZER_PIN, HIGH);
  analogWrite(BUZZER_PIN, 153); //Dat gia tri PWM de dieu chinh am luong BUZZER 60%
  delay(300);

  //Tat cac canh bao
  digitalWrite(LED_GREEN_PIN, LOW);
  //digitalWrite(BUZZER_PIN, LOW);
  analogWrite(BUZZER_PIN, 0);
  // delay(50);
}

void DangerDist2() {
  //Bat cac canh bao
  digitalWrite(LED_GREEN_PIN, HIGH);
  digitalWrite(LED_YELLOW_PIN, HIGH);
  digitalWrite(LED_RED_PIN, LOW);
  //digitalWrite(BUZZER_PIN, HIGH);
  analogWrite(BUZZER_PIN, 204); //Dat gia tri PWM de dieu chinh am luong BUZZER 80%
  delay(100);

  //Tat cac canh bao
  digitalWrite(LED_GREEN_PIN, LOW);
  digitalWrite(LED_YELLOW_PIN, LOW);
  //digitalWrite(BUZZER_PIN, LOW);
  analogWrite(BUZZER_PIN, 0); //Dat gia tri PWM de dieu chinh am luong BUZZER 0%
  // delay(50);
}

void CrashDist() {
  //Bat cac canh bao
  digitalWrite(LED_GREEN_PIN, HIGH);
  digitalWrite(LED_YELLOW_PIN, HIGH);
  digitalWrite(LED_RED_PIN, HIGH);
  //digitalWrite(BUZZER_PIN, HIGH);
  analogWrite(BUZZER_PIN, 255); //Dat gia tri PWM de dieu chinh am luong BUZZER 100%

  // digitalWrite(LED_GREEN_PIN, LOW);
  // digitalWrite(LED_YELLOW_PIN, LOW);
  // digitalWrite(LED_RED_PIN, LOW);
  // digitalWrite(BUZZER_PIN, LOW);
  // analogWrite(D9, 0); //Dat gia tri PWM de dieu chinh am luong BUZZER 0%
  // //delay(50);

}