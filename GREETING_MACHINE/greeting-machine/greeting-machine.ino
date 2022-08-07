// Include library
#include "Wire.h"
#include "LiquidCrystal_I2C.h"
#include "SoftwareSerial.h"
#include "MKL_DFRobotDFPlayerMini.h"

// Declare input Digital pin
// Dat ten cong ket noi cho cam bien
#define  SENSOR1_PIN    D11
#define  SENSOR2_PIN    D10

// Initialize DFPlayer Mini on the second serial port on RX and TX pins 
SoftwareSerial mySoftwareSerial(13, 12); 
DFRobotDFPlayerMini myDFPlayer; 
// set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C LCD(0x27, 16, 2);  

// Declare variables 
// Khai bao bien
int soKhach = 0;
int checkin = 0;

void setup(){
  // We initialize serial connection so that we could print values from sensor
  // Khoi tao cong ket noi noi tiep
  Serial.begin(9600);
  // Initialize LCD 1602 to display
  // Khoi tao LCD 1602 de hien thi
  LCD.init();  
  // Turn on LCD backlight   
  // Bat den nen LCD 1602    
  LCD.backlight();     
  mySoftwareSerial.begin(9600);
  //Use softwareSerial to communicate with mp3
  if (!myDFPlayer.begin(mySoftwareSerial)) {  
    while(true);
  }
  myDFPlayer.setTimeOut(500);  //Set serial communictaion time out 500ms
  // Set Sensor Pin as Output
  // Thiet lap chan SENSOR la Output
  pinMode(SENSOR1_PIN, INPUT); 
  pinMode(SENSOR2_PIN, INPUT); 
}

void loop() {
  // Read Sensor Value from digital pin
  // Doc gia tri cam bien
  int valueSensor1 = digitalRead(SENSOR1_PIN);
  int valueSensor2 = digitalRead(SENSOR2_PIN);
  for (int i = 0; i < 10; i++) {
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
    
    if ((valueSensor1 = digitalRead(SENSOR1_PIN)) == 0) {
      while (!((valueSensor2 == 0) && (valueSensor1  == 1))) { // Doi den khi doc duoc gia tri
        // Wait
        valueSensor1 = digitalRead(SENSOR1_PIN);
        valueSensor2 = digitalRead(SENSOR2_PIN);
      }

      myDFPlayer.playMp3Folder(1);  // Phat file am thanh thu nhat 
      soKhach += 1;
      checkin += 1;
      LCD.setCursor(0, 0);
      LCD.print("MakerLab Welcome");
      delay(1000);

      while (!((valueSensor2 == 1) && (valueSensor1  == 1))) { // Doi den khi doc duoc gia tri
        // Wait
        valueSensor1 = digitalRead(SENSOR1_PIN);
        valueSensor2 = digitalRead(SENSOR2_PIN);
      } 
    }
    
    if ((valueSensor2 = digitalRead(SENSOR2_PIN)) == 0) {
      while (!((valueSensor2 == 1) && (valueSensor1  == 0))) { // Doi den khi doc duoc gia tri
        // Wait
        valueSensor1 = digitalRead(SENSOR1_PIN);
        valueSensor2 = digitalRead(SENSOR2_PIN);
      }

      myDFPlayer.playMp3Folder(2); // Phat file am thanh thu hai

      if (soKhach > 0) {
        soKhach -= 1;
      }
      LCD.setCursor(0, 0);
      LCD.print("MakerLab Goodbye"); 
      delay(1000);      
      while (!!((valueSensor2 == 1) && (valueSensor1  == 0))) { // Doi den khi doc duoc gia tri
         // Wait
        valueSensor1 = digitalRead(SENSOR1_PIN);
        valueSensor2 = digitalRead(SENSOR2_PIN);
      }
    }
  }
}
