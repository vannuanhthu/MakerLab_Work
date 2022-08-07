// Include library
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

// Define connected pin
#define SOIL_SENSOR_PIN   A1
#define MOTOR_PIN         D11
#define LED_PIN           D10
#define DHTPIN            D9        // Digital pin connected to the DHT sensor
#define DHTTYPE           DHT11     // DHT 11

DHT dht(DHTPIN, DHTTYPE);           // Set DHT11
LiquidCrystal_I2C lcd(0x27, 20, 4); // Set the LCD address to 0x27 for a 20 chars and 4 line display

float Soil_Limit = 380;             // Set soil limit
unsigned long compareTime = 0;      // Set compare time for Led display
int runningFlag = 0;                // Set running flag for Led display

// Check Led whether it is running in cycle or not
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
  Serial.begin(9600);
  lcd.init();                 // Initialize the lcd
  lcd.backlight();            // Turn on LCD backlight
  dht.begin();                // Start DHT11
  pinMode(LED_PIN, OUTPUT);   // Pinmode led as output pin
  pinMode(MOTOR_PIN, OUTPUT); // Pinmode motor as output pin
}

void loop() {
  // Read soil sensor value 10 times and take average value
  float analogValue = 0;
  for (int i = 0; i < 10; i++) {
    analogValue = analogValue + analogRead(SOIL_SENSOR_PIN);
    delay(100);
  }
  analogValue = analogValue / 10;
  float Soil_Value = round(analogValue);

  // Compare soil value to soil limit to display Led
  if (Soil_Value > Soil_Limit) {
    if (!ledIsRunning()) {
      writeLed(1000, 5000);
    }
  } else {
    digitalWrite(LED_PIN, LOW);   // Led is not running
  }

  // Print Soil value at column 1 and row 2
  lcd.setCursor(0, 1);           
  lcd.print("Soil: ");
  lcd.print(Soil_Value);
  // Print temperature value and humidity value from DHT11 at column 1 and row 1
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
