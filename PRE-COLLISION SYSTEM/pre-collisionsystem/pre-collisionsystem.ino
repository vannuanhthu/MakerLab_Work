/*

*/
#include "UltraSonicDistanceSensor.h"
#include "Wire.h"
#include "LiquidCrystal_I2C.h"

const int PIN_TRIG = 13;
const int PIN_ECHO = 12;

UltraSonicDistanceSensor distanceSensor(PIN_TRIG, PIN_ECHO);  // Initialize sensor that uses digital pins 13 and 12.

// LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//Dat ten cong ket noi chan LED va BUZZER
int LedRED_Pin = A1;
int LedYELLOW_Pin = A2;
int LedGREEN_Pin = A3;
int Buzzer_Pin = D9;

//Dat gia tri cho cac khoang cach
int safeDis = 40;
int dangerDis = 25;
int crashDis = 13;

double valueDiscm = 0;

void setup() {
  Serial.begin(9600);  // We initialize serial connection so that we could print values from sensor.
  lcd.init();
  lcd.backlight();
  //Thiet lap LED va BUZZER o trang thai OUTPUT
  pinMode(LedRED_Pin, OUTPUT); // pinMode(A1, OUTPUT);
  pinMode(LedYELLOW_Pin, OUTPUT);
  pinMode(LedGREEN_Pin, OUTPUT);
  pinMode(Buzzer_Pin, OUTPUT);
}

void loop() {
  // Every 500 miliseconds, do a measurement using the sensor and print the distance in centimeters.
  if (distanceSensor.available() == true) {
    valueDiscm = distanceSensor.getcm();
    Serial.println(valueDiscm);
    lcd.setCursor(1, 1);
    lcd.print(String(valueDiscm)); //Hien thi gia tri khoang cach sau khi cam bien nhan duoc gia tri
    lcd.print(" cm"); 
    delay(500);
  }
  if (valueDiscm > safeDis) {
    lcd.clear();
    lcd.setCursor(1, 2);
    lcd.print("SafeDist"); //Hien thi trang thai khoang cach
    delay(500);
  }
   if (valueDiscm < safeDis && valueDiscm > dangerDis) {
     //
    lcd.clear();
    lcd.(1, 2);
    lcd.print("Dangerous"); //There is an obstacle? //Hien thi trang thai khoang cach
    delay(500);
    
    //Bat cac canh bao
    digitalWrite(LedGREEN_Pin, HIGH);
    analogWrite(D9, 153); //Dat gia tri PWM de dieu chinh am luong BUZZER 60%
    delay(1500);
    
    //Tat cac canh bao
    digitalWrite(LedGREEN_Pin, LOW);
    analogWrite(D9, 0);
    delay(500);
  }
   if (valueDiscm < dangerDis && valueDiscm > crashDis) {
     //
    lcd.clear();
    lcd.setCursor(1, 2);
    lcd.print("Dangerous"); //Hien thi trang thai khoang cach
    delay(500);
    
    //Bat cac canh bao
    digitalWrite(LedGREEN_Pin, HIGH);
    digitalWrite(LedYELLOW_Pin, HIGH);
    analogWrite(D9, 204); //Dat gia tri PWM de dieu chinh am luong BUZZER 80%
    delay(500);
    
    //Tat cac canh bao
    digitalWrite(LedGREEN_Pin, LOW);
    digitalWrite(LedYELLOW_Pin, LOW); 
    analogWrite(D9, 0); //Dat gia tri PWM de dieu chinh am luong BUZZER 0%
    delay(500);
  }
  if (valueDiscm < crashDis) {
     //
    lcd.clear();
    lcd.setCursor(1, 2);
    lcd.print("Crash"); //Hien thi trang thai khoang cach
    delay(500);
    
    //Bat cac canh bao
    digitalWrite(LedGREEN_Pin, HIGH);
    digitalWrite(LedYELLOW_Pin, HIGH);
    digitalWrite(LedRED_Pin, HIGH);
    analogWrite(D9, 255); //Dat gia tri PWM de dieu chinh am luong BUZZER 100%
    
    //Tat cac canh bao
    digitalWrite(LedGREEN_Pin, LOW);
    digitalWrite(LedYELLOW_Pin, LOW);
    digitalWrite(LedRED_Pin, LOW);
    analogWrite(D9, 0); //Dat gia tri PWM de dieu chinh am luong BUZZER 0%
    delay(2500);
    lcd.clear();
  } 
}
