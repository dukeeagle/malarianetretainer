#include <Time.h>
#include <TimeLib.h>

#include <Servo.h>;
int servoTopPin = 11;
int servoBottomPin = 10;
int potPin = A0;
int brightnessRaw;
int brightnessScaled;
int buzzerPin = 8;
unsigned long timerStart;
unsigned long timerEnd;
unsigned long lastUpdate;
int updateInterval = 10;
int pos;
int increment = 1;
bool doSweep;

Servo servoTop;
Servo servoBottom;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servoBottom.attach(servoBottomPin, 1000, 2000);
  servoTop.attach(servoTopPin, 1000, 2000);

  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  //int pos = 1;
  //tone(buzzerPin, 1200);
  /*delay(1000);
  noTone(buzzerPin);
  delay(1000);*/
  brightnessRaw = analogRead(potPin);
  //Serial.println(brightnessRaw);
  brightnessScaled = map(brightnessRaw, 400, 900, 0, 100);
  
   if(brightnessScaled > 0){
   /*  doSweep = true;
     timerStart = millis();
    } else {
      timerStart = 0; */ 
    
   if(((millis() - lastUpdate) > updateInterval) /* && doSweep*/)  // time to update
    {
      
      timerStart++;
      lastUpdate = millis();
      pos += increment;
      if(brightnessScaled < 0){
      doSweep = false;   
      }
      servoTop.write(pos);
      servoBottom.write(pos + 6);
      //Serial.println(pos);
      if ((pos >= 180) || (pos <= 0)) // end of sweep
      {
        // reverse direction
        increment = -increment;
      }
      
    }
   } else {
    timerStart = 0;
    }
  int timeSinceTest = millis() - timerStart;
  Serial.println(timerStart);
  if((timerStart  >= 1000)){
        tone(buzzerPin, 1200);
        } else {
          noTone(buzzerPin);
        }
  //Serial.println(brightnessScaled);
  //servoTop.write(150);
  
}
