#include <Arduino.h>
#include <IRremote.hpp>
#include "Wire.h"
#include "LiquidCrystal_I2C.h"
LiquidCrystal_I2C LCD(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

#define TRIG_PIN  13
#define ECHO_PIN  12

//Dat ten cong ket noi chan LED va BUZZER
#define LED_RED_PIN       A1
#define LED_YELLOW_PIN    A2
#define LED_GREEN_PIN     A3
#define FAN_PIN           D9

/*
    Infrared Radiation received signal on pin D10
    Chan do tin hieu hong ngoai D10
*/
const int IR_RECEIVE_PIN = D10;

void setup()
{
  Serial.begin(9600);
  // Just to know which program is running on my Arduino
  Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));
  /*
     Start the receiver, enable feedback LED and take LED feedback pin from the internal boards definition
  */
  IrReceiver.begin(IR_RECEIVE_PIN);
  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols(&Serial);
  Serial.print(F("at pin "));
  Serial.println(IR_RECEIVE_PIN);

  LCD.init();         // Initialize LCD 1602 to display
  LCD.backlight();    // Turn on LCD backlight
  // Set LED and Buzzer as output pin
  // Thiet lap LED va BUZZER la chan tin hieu ra
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_YELLOW_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
}

void loop()
{
  /*
     Check if received data is available and if yes, try to decode it.
     Decoded result is in the IrReceiver.decodedIRData structure.

     E.g. command is in IrReceiver.decodedIRData.command
     address is in command is in IrReceiver.decodedIRData.address
     and up to 32 bit raw data in IrReceiver.decodedIRData.decodedRawData
  */
  if (IrReceiver.decode())
  {
    // Print a short summary of received data
    // IrReceiver.printIRResultShort(&Serial);
    if (IrReceiver.decodedIRData.protocol == UNKNOWN)
    {
      // We have an unknown protocol here, print more info
      // IrReceiver.printIRResultRawFormatted(&Serial, true);
    }
    // Serial.println();
    /*
       !!!Important!!! Enable receiving of the next value,
       since receiving has stopped after the end of the current received data packet.
    */
    IrReceiver.resume(); // Enable receiving of the next value

    /*
       Finally, check the received data and perform actions according to the received command
    */
    if (IrReceiver.decodedIRData.command == 0x0c)
    {
      // do something
      Serial.println("Detect button 1");
      analogWrite(FAN_PIN, 64); // Dat gia tri PWM de dieu chinh toc do quat la 25%
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
      // do something
      Serial.println("Detect button 2");
      analogWrite(FAN_PIN, 123); // Dat gia tri PWM de dieu chinh toc do quat la 50%
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
      // do something else
      Serial.println("Detect button 3");
      analogWrite(FAN_PIN, 255); // Dat gia tri PWM de dieu chinh toc do quat la 100%
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
      // do something else
      Serial.println("Detect button 0");
      analogWrite(FAN_PIN, 0); // Tat quat
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