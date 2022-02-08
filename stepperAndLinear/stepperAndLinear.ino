
#include <Arduino.h>
#include "BasicStepperDriver.h"
//#include <ezButton.h>

#define MOTOR_STEPS 200
#define RPM 120
#define RPM_L 300


const byte interruptPin = 17;


#define MICROSTEPS_L 16
int whiskPos;
int stepperAngle = 1;
//int resetPin = 12;

#define DIR_L 15
#define STEP_L 16
BasicStepperDriver linnear(MOTOR_STEPS, DIR_L, STEP_L);

#define MICROSTEPS 32

#define DIR 8
#define STEP 9
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP);



//Uncomment line to use enable/disable functionality
//BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP, SLEEP);

void setup() {
  
    linnear.begin(RPM_L, MICROSTEPS_L);
    stepper.begin(RPM, MICROSTEPS);
    // if using enable/disable on ENABLE pin (active LOW) instead of SLEEP uncomment next line
    // stepper.setEnableActiveState(LOW);
    
    Serial.begin(57600);
    pinMode(interruptPin, INPUT_PULLUP);
    pinMode(11,INPUT_PULLDOWN);
    
    pinMode(2,OUTPUT);
    randomSeed(analogRead(0));
    while (! Serial); // Wait until Serial is ready - Leonardo
   
   attachInterrupt(digitalPinToInterrupt(interruptPin), advancemotor, FALLING);
   Serial.println("a - aluminum foil m - muted n - non");
//   
   linnear.rotate(-36000);
}

void loop() {

  int mm = 0;

  int bt;
     if (Serial.available())
      {
          mm = Serial.parseInt();
          Serial.println(mm);
          linnear.rotate(mm);
          bt = mm;
          whiskPos += bt;
          Serial.println(whiskPos);
          
      }

      
       char ch = "n";
      digitalWrite(2,LOW);
      digitalWrite(11,LOW);

    if (Serial.available())
      {
        ch = Serial.read();
           
        if (ch == 'a')
        {
          linnear.rotate(-whiskPos);
          stepper.rotate(360-stepperAngle);
          stepper.rotate(60);
          stepperAngle = 60;
          Serial.println("aluminum");
          delay(1000);
          linnear.rotate(whiskPos);
          delay(500);
          digitalWrite(2,HIGH);
          delay(100);
          digitalWrite(2,LOW);
          
          
          
        }
        if (ch == 'm')
        {
          linnear.rotate(-whiskPos);
          stepper.rotate(360-stepperAngle);
          stepper.rotate(120);
          stepperAngle = 120;
          Serial.println("aluminum silenced");
          delay(1000);
          linnear.rotate(whiskPos);
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
          linnear.rotate(-whiskPos);
          stepper.rotate(360-stepperAngle);
          stepperAngle = 0;
          Serial.println("non");
          delay(1000);
          linnear.rotate(whiskPos);
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
        linnear.rotate(-whiskPos);
        stepper.rotate(360-stepperAngle);
          stepper.rotate(60);
          stepperAngle = 60;
          Serial.println("aluminum");
          delay(1000);
          linnear.rotate(whiskPos);
          delay(500);
          digitalWrite(2,HIGH);
          delay(100);
          digitalWrite(2,LOW);
        i++;
        break;
        
        
        
        case 2:
        linnear.rotate(-whiskPos);
          stepper.rotate(360-stepperAngle);
          stepper.rotate(120);
          stepperAngle = 120;
          Serial.println("aluminum silenced");
          delay(1000);
          linnear.rotate(whiskPos);
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
        linnear.rotate(-whiskPos);
        stepper.rotate(360-stepperAngle);
          stepperAngle = 0;
          Serial.println("non");
          delay(1000);
          linnear.rotate(whiskPos);
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
//        digitalWrite(resetPin,LOW);
//        digitalWrite(11,LOW);
      }
      delay(10000);
  }

}   
   
    
}


void advancemotor() {
  linnear.startBrake();
  linnear.rotate(180);
  Serial.println("stopped");
  
  
  
}
