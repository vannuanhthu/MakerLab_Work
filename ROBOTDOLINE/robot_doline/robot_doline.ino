// Include libraries
// Cai dat thu vien
#include <Arduino.h>
#include "Wire.h"
#include "SoftwareSerial.h"
#include "UltraSonicDistanceSensor.h"
#include "Makerlabvn_I2C_Motor_Driver.h"

// Initialize robot driver 
// Khai bao thiet bi dieu khien
Makerlabvn_I2C_Motor_Driver myDriver(0);

// Define connected pin
// Dat ten chan cong ket noi
#define ECHO_PIN          12
#define TRIG_PIN          13
#define LEFT_SENSOR       A1
#define RIGHT_SENSOR      A2

// Initialize sensor that uses digital pins 13 and 12
// Khoi tao chan ket noi digital 12 va 13 cho cam bien sieu am
UltraSonicDistanceSensor distanceSensor(TRIG_PIN, ECHO_PIN);  

// Declare Variables 
// Khai bao bien
float int_dist = 0; 
float offset = 100;
float speed = 50;

void setup() {
  // Initialize myDriver connection 
  // Khoi tao cong ket noi cho myDriver
  myDriver.begin();
}

void loop() {
  // Check obtacle appearance in front of robot
  // Kiem tra vat can phia truoc
  if (distanceSensor.available() == true) {
    if ((int_dist =  floor(distanceSensor.getcm())) < 20) {
      // Stop now
      // Dung xe ngay khi gap vat can
      myDriver.writeMB(1, 0);
      myDriver.writeMA(1, 0); 
      // Wait until read distance value 
      // Doi den khi doc duoc gia tri khoang cach moi
      while(!( int_dist = floor(distanceSensor.getcm()) > 25)){}
    }
  }
  // Go backward 
  // Di lui
  if ((analogRead(LEFT_SENSOR) < offset) && (analogRead(RIGHT_SENSOR) < offset)) {
    myDriver.writeMB(0, speed);
    myDriver.writeMA(0, speed); 
  }
  // Go forward
  // Di thang
  if ((analogRead(LEFT_SENSOR) > offset) && (analogRead(RIGHT_SENSOR) > offset)) {
    myDriver.writeMB(1, speed);
    myDriver.writeMA(1, speed);
  }
  // Turn Clockwise
  // Quay sang trai
  if ((analogRead(LEFT_SENSOR) < offset) && (analogRead(RIGHT_SENSOR) > offset)) {
    while (!(analogRead(LEFT_SENSOR) > offset)) {
      myDriver.writeMB(1, speed);
      myDriver.writeMA(0, speed);
    }
  }
  // Turn CounterClockwise
  // Quay sang phai
  if ((analogRead(LEFT_SENSOR) > offset) && (analogRead(RIGHT_SENSOR) < offset)) {
    while (!(analogRead(RIGHT_SENSOR) > offset)) {
      myDriver.writeMB(0, speed);
      myDriver.writeMA(1, speed); 
    }
  }
  delay(50);
}
