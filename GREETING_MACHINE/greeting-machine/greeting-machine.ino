/*
  
*/
#include "Wire.h"
#include "LiquidCrystal_I2C.h"
#include "SoftwareSerial.h"
#include "MKL_DFRobotDFPlayerMini.h"

// Declare input Digital pin
#define  SENSOR1_PIN    D11
#define  SENSOR2_PIN    D10

SoftwareSerial mySoftwareSerial(13, 12); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

LiquidCrystal_I2C LCD(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int soKhach = 0;
int checkin = 0;

void setup(){
  LCD.init();         // Initialize LCD 1602 to display
  LCD.backlight();    // Turn on LCD backlight
  Serial.begin(9600);
  mySoftwareSerial.begin(9600);
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    while(true);
  }
  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms
  pinMode(SENSOR1_PIN, INPUT);
  pinMode(SENSOR2_PIN, INPUT);
}

void loop() {
  int valueSensor1 = digitalRead(SENSOR1_PIN);
  int valueSensor2 = digitalRead(SENSOR2_PIN);
  for(int i = 0; i < 10; i++){
    LCD.setCursor(0, 0);
    LCD.print("Capacity");
    LCD.setCursor(9, 0);
    LCD.print("Checkin");
    LCD.setCursor(0, 1);
    LCD.print(soKhach);
    LCD.print("/40");
    LCD.print("   ");
    LCD.setCursor(10, 1);
    LCD.print(checkin);
    
    if((valueSensor1 = digitalRead(SENSOR1_PIN)) == 0){
      while(!((valueSensor2 == 0) && (valueSensor1  == 1))){
        // Wait
        valueSensor1 = digitalRead(SENSOR1_PIN);
        valueSensor2 = digitalRead(SENSOR2_PIN);
      }
      myDFPlayer.playMp3Folder(1);  
      soKhach += 1;
      checkin += 1;
      LCD.setCursor(0, 0);
      LCD.print("MakerLab Welcome");
      delay(1000);
      while(!((valueSensor2 == 1) && (valueSensor1  == 1))){
        // Wait
        valueSensor1 = digitalRead(SENSOR1_PIN);
        valueSensor2 = digitalRead(SENSOR2_PIN);
      } 
    }
    
    if((valueSensor2 = digitalRead(SENSOR2_PIN)) == 0){
      while(!((valueSensor2 == 1) && (valueSensor1  == 0))){
        // Wait
        valueSensor1 = digitalRead(SENSOR1_PIN);
        valueSensor2 = digitalRead(SENSOR2_PIN);
      }
      myDFPlayer.playMp3Folder(2);
      if(soKhach > 0){
        soKhach -= 1;
      }
      LCD.setCursor(0, 0);
      LCD.print("MakerLab Goodbye"); 
      delay(1000);      
      while(!!((valueSensor2 == 1) && (valueSensor1  == 0))){
         // Wait
        valueSensor1 = digitalRead(SENSOR1_PIN);
        valueSensor2 = digitalRead(SENSOR2_PIN);
      }
    }
  }
}
