// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
// Xac dinh thoi gian ngay va gio su dung thu vien DS3231 RTC ket noi thong qua I2C va Wire
#include "RTClib.h"
// Note music for Buzzer
// Thu vien Note cho Buzzer
#include "Note.h"
#include "Wire.h"
#include "LiquidCrystal_I2C.h"
#include "DHT.h"

// Set the LCD address to 0x27 for a 16 chars and 2 line display
// Thiet lap dia chi LCD 0x27 de hien thi 16 ky tu tren hai dong
LiquidCrystal_I2C LCD(0x27, 16, 2); 
 
// Define connected pin
// Dat ten chan cong ket noi
#define AIR_SENSOR_PIN  A1
#define BUTTON_PIN      A2
#define BUZZER_PIN      D9
#define FAN_PIN         D10

 // Digital pin connected to the DHT sensor
 // Ket noi chan tin hieu Digital cho cam bien DHT
#define DHTPIN          D11     
#define DHTTYPE         DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);
RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
unsigned int rtcDay, rtcMonth, rtcYear;
unsigned int rtcSecond, rtcMinute, rtcHour;
unsigned int alarmSecond, alarmcMinute, alarmHour;
// Set value state for push button
// Dat gia tri cho nut nhan
int Display = 0;       
float AirValue = 0;
// Set air quality limit
// Dat gia tri nguong
float Air_Limit = 20;   
float temperature;
float humidity;

void setup () {
  // We initialize serial connection so that we could print values from sensor
  // Khoi tao cong ket noi noi tiep
  Serial.begin(9600);
  dht.begin();
  // Initialize LCD 1602 to display
  // Khoi tao LCD 1602 de hien thi
  LCD.init();        
  // Turn on LCD backlight   
  // Bat den nen LCD 1602  
  LCD.backlight();    
   // Set Pin as Output pin or Input pin
  // Thiet lap trang thai cac chan ket noi
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, 
    // the following line sets the RTC to the date & time this sketch was compiled
    // Thiet lap thoi gian cho RTC tai thoi diem nap chuong trinh
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  rtc.clearAlarm(1);
  // stop oscillating signals at SQW Pin
  // otherwise setAlarm1 will fail
  // Dung tin hieu dao dong tai chan SQW, neu khong se khong setAlarm1 duoc 
  rtc.writeSqwPinMode(DS3231_OFF);
  if (!rtc.setAlarm1(
        rtc.now() + TimeSpan(20),
        DS3231_A1_Second 
        // This mode triggers the alarm when the seconds match. See Doxygen for other options
        // Che do nay se kich hoat bao thuc khi da dung thoi gian. Xem Doxygen de biet cac lua chon khac 
      )) {
    // Do nothing
  }
}

void loop () {
  // Doc gia tri cam bien
  AirValue = analogRead(AIR_SENSOR_PIN);
  if (AirValue > Air_Limit) {
    // 50% duty cycle of PWM
    // Dat gia tri PWM 50%
    analogWrite(FAN_PIN, 50 * 255 / 100); 
  }
  else {
    // Turn off fan
    // Tat quat
    analogWrite(FAN_PIN, 0);    
  }

  int btnState = digitalRead(BUTTON_PIN); 
  // Button was clicked
  // Khi nhan nut Button
  if (btnState == 0) { 
    if (Display == 0) {
      Display = 1;
      LCD.clear();
    }
    else {
      if (Display == 1) { 
      Display = 2;
      LCD.clear();
      }
      else {
      Display = 0;
      LCD.clear();
      }
    }
  }

  DateTime now = rtc.now();
  rtcYear = now.year();
  rtcMonth = now.month();
  rtcDay = now.day();
  rtcSecond = now.second();
  rtcMinute = now.minute();
  rtcHour = now.hour();
  if (Display == 0) {
    // Print RTC Time at column 5 and row 1
    // Hien thi thoi gian tai cot 5 hang 1
    LCD.setCursor(4, 0);
    if (rtcHour < 10) {
      LCD.print("0");
      LCD.print(rtcHour);
    } else {
      LCD.print(rtcHour);
    }
    LCD.print(":");

    if (rtcMinute < 10) {
      LCD.print("0");
      LCD.print(rtcMinute);
    } else {
      LCD.print(rtcMinute);
    }
    LCD.print(":");

    if (rtcSecond < 10) {
      LCD.print("0");
      LCD.print(rtcSecond);
    } else {
      LCD.print(rtcSecond);
    }

    // Print RTC Date at column 2 and row 2
    // Hien thi ngay tai cot 2 hang 2
    LCD.setCursor(1, 1);
    LCD.print(daysOfTheWeek[now.dayOfTheWeek()]);
    LCD.print(",");
    if (rtcDay < 10) {
      LCD.print("0");
      LCD.print(rtcDay);
    } else {
      LCD.print(rtcDay);
    }
    LCD.print("/");

    if (rtcMonth < 10) {
      LCD.print("0");
      LCD.print(rtcMonth);
    } else {
      LCD.print(rtcMonth);
    }
    LCD.print("/");

    LCD.print(rtcYear);
  } else {
    if (Display == 1) {
      // Print RTC Time at column 5 and row 1
      // Hien thi thoi gian tai cot 5 hang 1
      LCD.setCursor(4, 0);
      if (rtcHour < 10) {
        LCD.print("0");
        LCD.print(rtcHour);
      } else {
        LCD.print(rtcHour);
      }
      LCD.print(":");

      if (rtcMinute < 10) {
        LCD.print("0");
        LCD.print(rtcMinute);
      } else {
        LCD.print(rtcMinute);
      }
      LCD.print(":");

      if (rtcSecond < 10) {
        LCD.print("0");
        LCD.print(rtcSecond);
      } else {
        LCD.print(rtcSecond);
      }

      // Print Air quality at column 2 and row 2
      // Hien thi gia tri cam bien khong khi tai cot 2 hang 2
      LCD.setCursor(1, 1);
      LCD.print("Air: ");
      LCD.print(AirValue);
    } else {
      // Print RTC Time at column 5 and row 1
      // Hien thi thoi gian tai cot 5 hang 1
      LCD.setCursor(4, 0);
      if (rtcHour < 10) {
        LCD.print("0");
        LCD.print(rtcHour);
      } else {
        LCD.print(rtcHour);
      }
      LCD.print(":");

      if (rtcMinute < 10) {
        LCD.print("0");
        LCD.print(rtcMinute);
      } else {
        LCD.print(rtcMinute);
      }
      LCD.print(":");

      if (rtcSecond < 10) {
        LCD.print("0");
        LCD.print(rtcSecond);
      } else {
        LCD.print(rtcSecond);
      }

      temperature = dht.readTemperature();
      humidity = dht.readHumidity();
      // Print Air quality at column 2 and row 2
      // Hien thi gia tri cam bien khong khi tai cot 2 hang 2
      LCD.setCursor(1, 1);
      LCD.print(temperature);
      char degreeChar = 223;
      LCD.print(degreeChar);
      LCD.print("C ");
      LCD.print(humidity);
      LCD.print("%");
    }
  }
  // Alarm
  if (rtc.alarmFired(1)) {
    LCD.clear();
    LCD.setCursor(4, 0);
    LCD.print("Wake up!");
    //delay(1000);
    for (int i = 0; i < 2; i++) {
      tone(BUZZER_PIN, NOTE_E7, 83);
      tone(BUZZER_PIN, NOTE_E7, 83);
      delay(83);
      tone(BUZZER_PIN, NOTE_E7, 83);
      delay(83);
      tone(BUZZER_PIN, NOTE_C7, 83);
      tone(BUZZER_PIN, NOTE_E7, 83);
      delay(83);
      tone(BUZZER_PIN, NOTE_G7, 83);
      delay(83);
      delay(83);
      delay(83);
      tone(BUZZER_PIN, NOTE_G6, 83);
      delay(83);
      delay(83);
      delay(83);
      for (int i = 0; i < 2; i++) {
        tone(BUZZER_PIN, NOTE_C7, 83);
        delay(83);
        delay(83);
        tone(BUZZER_PIN, NOTE_G6, 83);
        delay(83);
        delay(83);
        tone(BUZZER_PIN, NOTE_E6, 83);
        delay(83);
        delay(83);
        tone(BUZZER_PIN, NOTE_A6, 83);
        delay(83);
        tone(BUZZER_PIN, NOTE_B6, 83);
        delay(83);
        tone(BUZZER_PIN, NOTE_AS6, 83);
        tone(BUZZER_PIN, NOTE_A6, 83);
        delay(83);
        tone(BUZZER_PIN, NOTE_G6, 83);
        tone(BUZZER_PIN, NOTE_E7, 83);
        tone(BUZZER_PIN, NOTE_A7, 83);
        delay(83);
        tone(BUZZER_PIN, NOTE_F7, 83);
        tone(BUZZER_PIN, NOTE_G7, 83);
        delay(83);
        tone(BUZZER_PIN, NOTE_E7, 83);
        delay(83);
        tone(BUZZER_PIN, NOTE_C7, 83);
        tone(BUZZER_PIN, NOTE_D7, 83);
        tone(BUZZER_PIN, NOTE_B6, 83);
        delay(83);
        delay(83);
      }
      delay(1000);
    }
    digitalWrite(BUZZER_PIN, LOW);
    rtc.clearAlarm(1);
  }
  delay(1000);
}
