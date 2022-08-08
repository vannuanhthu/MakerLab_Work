// Include library
#include <Arduino.h>
#include <IRremote.hpp>
#include "Wire.h"
#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C LCD(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// Define connected pin
// Dat ten cong ket noi chan LED va BUZZER
#define LED_RED_PIN       A1
#define LED_YELLOW_PIN    A2
#define LED_GREEN_PIN     A3
#define FAN_PIN           D9


// Infrared Radiation received signal on pin D10
// Chan do tin hieu hong ngoai D10
const int IR_RECEIVE_PIN = D10;

void setup()
{
  Serial.begin(9600);
  LCD.init();         // Initialize LCD 1602 to display
  LCD.backlight();    // Turn on LCD backlight
  // Set LED and Buzzer as output pin
  // Thiet lap LED va BUZZER la chan tin hieu ra
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_YELLOW_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  
  // Start the receiver
  // Nhan tin hieu hong ngoai va kiem tra tin hieu
  IrReceiver.begin(IR_RECEIVE_PIN);
  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols(&Serial);
  Serial.print(F("at pin "));
  Serial.println(IR_RECEIVE_PIN);
}

void loop()
{
  if (IrReceiver.decode())
  {
    // Print a short summary of received data
    // IrReceiver.printIRResultShort(&Serial);
    if (IrReceiver.decodedIRData.protocol == UNKNOWN)
    {
      // We have an unknown protocol here, print more info
      // IrReceiver.printIRResultRawFormatted(&Serial, true);
    }
    IrReceiver.resume(); // Enable receiving of the next value

      // Finally, check the received data and perform actions according to the received command
    if (IrReceiver.decodedIRData.command == 0x0c)
    {
       // Set PWM 25%
       // Dat gia tri PWM de dieu chinh toc do quat la 25%
      analogWrite(FAN_PIN, 64);
      digitalWrite(LED_GREEN_PIN, HIGH);
      digitalWrite(LED_YELLOW_PIN, LOW);
      digitalWrite(LED_RED_PIN, LOW);
      LCD.clear();
      LCD.setCursor(0, 0);
      LCD.print("Level 1 ^^");
      LCD.setCursor(0, 1);
      LCD.print("Mat khong?");
    }

    delay(100);

    if (IrReceiver.decodedIRData.command == 0x18)
    {
       // Set PWM 50%
       // Dat gia tri PWM de dieu chinh toc do quat la 50%
      analogWrite(FAN_PIN, 123);
      digitalWrite(LED_GREEN_PIN, LOW);
      digitalWrite(LED_RED_PIN, LOW);
      digitalWrite(LED_YELLOW_PIN, HIGH);
      LCD.clear();
      LCD.setCursor(0, 0);
      LCD.print("Level 2 :)");
      LCD.setCursor(0, 1);
      LCD.print("Mat khong?");
    }
    if (IrReceiver.decodedIRData.command == 0x5e)
    {
      // Set PWM 100%
      // Dat gia tri PWM de dieu chinh toc do quat la 100%
      analogWrite(FAN_PIN, 255); 
      digitalWrite(LED_GREEN_PIN, LOW);
      digitalWrite(LED_YELLOW_PIN, LOW);
      digitalWrite(LED_RED_PIN, HIGH);
      LCD.clear();
      LCD.setCursor(0, 0);
      LCD.print("Level 3 :\">");
      LCD.setCursor(0, 1);
      LCD.print("Cho tui nghi diii");
    }
    if (IrReceiver.decodedIRData.command == 0x16)
    {
      // Set PWM 0% to turn off fan
      // Tat quat
      analogWrite(FAN_PIN, 0); 
      digitalWrite(LED_GREEN_PIN, LOW);
      digitalWrite(LED_YELLOW_PIN, LOW);
      digitalWrite(LED_RED_PIN, LOW);
      LCD.clear();
      LCD.setCursor(0, 0);
      LCD.print("Cam on ban");
      LCD.setCursor(0, 1);
      LCD.print("Iu ban lam <3");
    }
  }
}
