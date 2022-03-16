#include <Arduino.h>
#include "BasicStepperDriver.h"
#define MOTOR_STEPS 200
#define RPM 120
#define MICROSTEPS 32

#define DIR 8
#define STEP 9
//#define SLEEP 13
int stepperAngle = 1;
int resetPin = 12;
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP);
void setup() {
    stepper.begin(RPM, MICROSTEPS);
    // if using enable/disable on ENABLE pin (active LOW) instead of SLEEP uncomment next line
    // stepper.setEnableActiveState(LOW);
    Serial.begin(9600);
    pinMode(11,INPUT);
    pinMode(2,OUTPUT);
    randomSeed(analogRead(0));
    while (! Serial); // Wait until Serial is ready - Leonardo
    Serial.println("a - aluminum foil m - muted n - non");
    }


    void loop() {
      char ch = "n";
      digitalWrite(2,LOW);
      digitalWrite(11,LOW);

    if (Serial.available())
      {
        ch = Serial.read();
           
        if (ch == 'a')
        {
          stepper.rotate(360-stepperAngle);
          stepper.rotate(60);
          stepperAngle = 60;
          Serial.println("aluminum");
          delay(1000);
          
          
          delay(500);
          
          digitalWrite(2,HIGH);
          delay(100);
          digitalWrite(2,LOW);
          
          
          
        }
        if (ch == 'm')
        {
          stepper.rotate(360-stepperAngle);
          stepper.rotate(120);
          stepperAngle = 120;
          Serial.println("aluminum silenced");
          delay(1000);
          
          
          
          digitalWrite(2,HIGH);
          delay(100);
          digitalWrite(2,LOW);
          delay(100);
          digitalWrite(2,HIGH);
          delay(100);
          digitalWrite(2,LOW);
         
          
        }
        if (ch == 'n')
        {
          stepper.rotate(360-stepperAngle);
          stepperAngle = 0;
          Serial.println("non");
          delay(1000);
          
          digitalWrite(2,HIGH);
          delay(100);
          digitalWrite(2,LOW);
          delay(100);
          digitalWrite(2,HIGH);
          delay(100);
          digitalWrite(2,LOW);
          delay(100);
          digitalWrite(2,HIGH);
          delay(100);
          digitalWrite(2,LOW);
         
          
          
        }

      }
if (digitalRead(11) == HIGH)
  {
        int randAr[15] = {1,2,3,1,3,2,1,1,2,2,1,3,2,1,3};
        for (int j =0;j<15;j++)
        {
          int pos = random(15);
          int t = randAr[j];
          randAr[j];
          randAr[pos] = t;
          
        }
        
        for (int i=0;i<15;i++)
        {
          int chRND = randAr[i];
          Serial.println(chRND);
        switch (chRND){
        case 1:
        stepper.rotate(360-stepperAngle);
          stepper.rotate(60);
          stepperAngle = 60;
          Serial.println("aluminum");
          delay(1000);
          
          
          delay(500);
          
          digitalWrite(2,HIGH);
          delay(100);
          digitalWrite(2,LOW);
        i++;
        break;
        
        
        
        case 2:
          stepper.rotate(360-stepperAngle);
          stepper.rotate(120);
          stepperAngle = 120;
          Serial.println("aluminum silenced");
          delay(1000);
          
          
          
          digitalWrite(2,HIGH);
          delay(100);
          digitalWrite(2,LOW);
          delay(100);
          digitalWrite(2,HIGH);
          delay(100);
          digitalWrite(2,LOW);
        i++;
        break;
        
        
        
        case 3:
        stepper.rotate(360-stepperAngle);
          stepperAngle = 0;
          Serial.println("non");
          delay(1000);
          
          digitalWrite(2,HIGH);
          delay(100);
          digitalWrite(2,LOW);
          delay(100);
          digitalWrite(2,HIGH);
          delay(100);
          digitalWrite(2,LOW);
          delay(100);
          digitalWrite(2,HIGH);
          delay(100);
          digitalWrite(2,LOW);
        i++;
        break;
        
        
      }
      if (digitalRead(11) == LOW)
      {
        break;
        digitalWrite(resetPin,LOW);
        digitalWrite(11,LOW);
      }
      delay(60000);
  }

}
    }
