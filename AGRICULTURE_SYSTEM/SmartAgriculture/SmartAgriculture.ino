// Include library
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"


// Define connected pin
// Dat ten chan cong ket noi
#define SOIL_SENSOR_PIN   A1
#define MOTOR_PIN         D11
#define LED_PIN           D10
#define DHTPIN            D9        // Digital pin connected to the DHT sensor
#define DHTTYPE           DHT11     // DHT 11

DHT dht(DHTPIN, DHTTYPE);           // Set DHT11
// Set the LCD address to 0x27 for a 16 chars and 2 line display
// Thiet lap dia chi LCD 0x27 de hien thi 16 ky tu tren hai dong
LiquidCrystal_I2C lcd(0x27, 20, 4); 

// Declare variables 
// Khai bao bien
float Soil_Limit = 380;             // Set soil limit
unsigned long compareTime = 0;      // Set compare time for Led display
int runningFlag = 0;                // Set running flag for Led display

// Check Led whether it is running in cycle or not
// Ham kiem tra trang thai LED
int ledIsRunning() {
  if ((runningFlag == 0) && (digitalRead(LED_PIN) == 0)) {
    compareTime = millis();  // Update compare time
    return 0;
  }
  if ((runningFlag == 1) && (digitalRead(LED_PIN) == 1)) {
    return 0;
  }
  if ((runningFlag == 2) && (digitalRead(LED_PIN) == 0)) {
    return 0;
  }
  return 1;
}

// Write Led ON/OFF in cycle
// Bat tat LED theo chu ky
void writeLed(int delayTime1, int delayTime2) {
  if ((millis() - compareTime) < delayTime1) {
    digitalWrite(LED_PIN, HIGH);
    runningFlag = 1;
  } else {
      if ((millis() - compareTime) < delayTime2) {
        digitalWrite(LED_PIN, LOW);
        runningFlag = 2;
     }
  }
  if ((millis() - compareTime) > (delayTime1 + delayTime2)) {
    runningFlag = 0;
    digitalWrite(LED_PIN, LOW);
  }
}

void setup() {
  // We initialize serial connection so that we could print values from sensor
  // Khoi tao cong ket noi noi tiep
  Serial.begin(9600);
  // Initialize LCD 1602 to display
  // Khoi tao LCD 1602 de hien thi
  lcd.init(); 
  // Turn on LCD backlight   
  // Bat den nen LCD 1602  
  lcd.backlight();   
  // Start DHT11         
  dht.begin();         
  // Thiet lap chan ket noi o trang thai OUTPUT      
  pinMode(LED_PIN, OUTPUT);   // Pinmode led as output pin
  pinMode(MOTOR_PIN, OUTPUT); // Pinmode motor as output pin
}

void loop() {
  // Read soil sensor value 10 times and take average value
  // Lay gia tri trung binh sau moi 10 lan cam bien doc gia tri
  float analogValue = 0;
  for (int i = 0; i < 10; i++) {
    analogValue = analogValue + analogRead(SOIL_SENSOR_PIN);
    delay(100);
  }
  analogValue = analogValue / 10;
  float Soil_Value = round(analogValue);

  // Compare soil value to soil limit to display Led
  // So sanh gia tri doc duoc voi gia tri nguong de bat tat LED canh bao
  if (Soil_Value > Soil_Limit) {
    if (!ledIsRunning()) {
      writeLed(1000, 5000);
    }
  } else {
    digitalWrite(LED_PIN, LOW);   // Led is not running
  }

  // Print Soil value at column 1 and row 2
  // Hien thi gia tri o cot 1 hang 2
  lcd.setCursor(0, 1);           
  lcd.print("Soil: ");
  lcd.print(Soil_Value);
  // Print temperature value and humidity value from DHT11 at column 1 and row 1
  // Hien thi gia tri nhiet do va do am o cot 1 hang 1
  lcd.setCursor(0, 0);           
  int humidity = dht.readHumidity();
  int temperature = dht.readTemperature();
  lcd.print("Air: ");
  lcd.print(temperature);
  char specialChar = 223;         // Special char is degree Celcius character with ASCII value 223
  lcd.print(specialChar);
  lcd.print("C  ");
  lcd.print(humidity);
  lcd.print("%");
}
