//This sketch  triggers daily alarms at 8:30 am and 17:45 pm.
//A Timer is triggered every 15 seconds, another timer triggers once only after 10 seconds.

#include <Time.h>
#include <TimeAlarms.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int pinOut = 11;//RELAY PIN for DIP IRRIGATION
unsigned long millis1;         
unsigned long millis2;
int SensorPin = A0;
int duration=0;
 int durationtemp=0;
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
int time_cnt=1;

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 1);
  lcd.print("ITime#Set1:Cu12#");
  pinMode(pinOut,OUTPUT);
  pinMode(10,OUTPUT);
  digitalWrite(pinOut, HIGH);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(pinOut, LOW);
  setTime(1,00,0,1,1,10); // set time to 8:29:00am Jan 1 2010
  // create the alarms 
  lcd.setCursor(0, 0);
  lcd.print(String("Dur:   TAP: OFF"));
  Alarm.alarmRepeat(1,01,0, StartPump);
  Alarm.alarmRepeat(1,(analogRead(SensorPin)/10),0,StopPump);  
}

void  loop(){
 
  time_cnt=digitalClockDisplay();
  dur();
  lcd.setCursor(0, 1);
  lcd.print(String("ITime#Set1:Cu") + String(time_cnt) + String("#"));
  Alarm.delay(1000);

}

// functions to be called when an alarm triggers:
void StartPump(){
  Serial.println("Starting Pump");
  taponmsg(" ON ");
  digitalWrite(pinOut, HIGH);  
}

void StopPump(){
  Serial.println("Stopping Pump");
   taponmsg(" OFF");        
  digitalWrite(pinOut, LOW);    
}

int digitalClockDisplay()
{


//  printDigits(minute());
//  printDigits(second());
//  Serial.println(); 

  return hour();
  
}

//void printDigits(int digits)
//{
//  Serial.print(":");
//  if(digits < 10)
//    Serial.print('0');
//  Serial.print(digits);
//
//  
//}
//


void taponmsg (String msg)
{
  lcd.setCursor(11, 0);
  lcd.print(msg);
  delay(500);
}

void dur ()
{
  lcd.setCursor(4, 0);
  if((analogRead(SensorPin)/10)< 60)
  {
   duration=(analogRead(SensorPin)/10);
  }
  else
  {
  duration=60;
  }
  lcd.print(duration);
  delay(500);
  if(duration!=durationtemp)
  {
    durationtemp=duration;
   }
}
