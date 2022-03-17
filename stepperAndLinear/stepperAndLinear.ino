
#include <Arduino.h>
#include "BasicStepperDriver.h"
//#include <ezButton.h>

#define MOTOR_STEPS 200
#define RPM 30
#define RPM_L 300
#define SLEEP_L 13
#define SLEEP 2


const byte interruptPin = 17;


#define MICROSTEPS_L 16
int whiskPos;
int stepperAngle = 0;

//int resetPin = 12; 

#define DIR_L 15
#define STEP_L 14
BasicStepperDriver linnear(MOTOR_STEPS, DIR_L, STEP_L,SLEEP_L);

#define MICROSTEPS 1

#define DIR 0
#define STEP 1
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP,SLEEP);
int randAr[6] = {1,2,3,1,2,3};
int countAll = 0;


//Uncomment line to use enable/disable functionality
//BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP, SLEEP);


void setup() {
    
    linnear.begin(RPM_L, MICROSTEPS_L);
    linnear.setEnableActiveState(LOW);
    stepper.begin(RPM, MICROSTEPS);
    stepper.setEnableActiveState(LOW);
    // if using enable/disable on ENABLE pin (active LOW) instead of SLEEP uncomment next line
    // stepper.setEnableActiveState(LOW);
    stepper.enable();
    Serial.begin(115200);
    pinMode(interruptPin, INPUT_PULLUP);
    pinMode(11,INPUT_PULLDOWN);
    
    pinMode(3,OUTPUT);
    randomSeed(analogRead(0));
    while (! Serial); // Wait until Serial is ready - Leonardo
   
   attachInterrupt(digitalPinToInterrupt(interruptPin), advancemotor, FALLING);
   Serial.println("l - aluminum foil m - muted n - non");
//   
   linnear.rotate(-36000);
   linnear.disable();
//   stepper.rotate(1.8);
}

void loop() {
        
  
  int mm = 0;
  char jj;
  int rot;

  int bt;
     if (Serial.available())
      {   
        jj = Serial.peek();
        if(isDigit(jj) || jj == '-'){
      
          linnear.enable();
          mm = Serial.parseInt();
          Serial.println(mm);
          
          bt = mm * 180;
          linnear.rotate(bt);
          whiskPos += bt;
          Serial.println(whiskPos);
          linnear.disable();
        }
        else if(jj=='r')
        {
          String rr = Serial.readString();
          rr.remove(0,1);
          Serial.print("Rotating stepper  ");
          Serial.println(rr);
          rot = rr.toInt();
          stepper.move(rot);
          stepperAngle = 0;
        }
      
      

      
       char ch = "n";
      digitalWrite(2,LOW);
      digitalWrite(11,LOW);

    
      
        ch = Serial.read();
           
        if (ch == 'l')
        {
          
          linnear.enable();
          linnear.rotate(-whiskPos);
          stepper.move(-stepperAngle);
          delay(100);
          stepper.move(32*MICROSTEPS);
          stepperAngle = 32*MICROSTEPS;
//          stepper.rotate(-stepperAngle);
//          delay(100);
//          stepper.rotate(60);
//          stepperAngle = 60;
          Serial.println("aluminum");
          delay(1000);
          linnear.rotate(whiskPos);
          linnear.disable();
//          stepper.disable();
          delay(500);
          digitalWrite(3,HIGH);
          delay(100);
          digitalWrite(3,LOW);
          
          
          
        }
        if (ch == 'm')
        {
          
          linnear.enable();
          linnear.rotate(-whiskPos);
          
          stepper.move(-stepperAngle);
          delay(100);
          stepper.move(64*MICROSTEPS);
          stepperAngle = 64*MICROSTEPS;
//          stepper.rotate(-stepperAngle);
//          delay(100);
//          stepper.rotate(120);
//          stepperAngle = 120;
          Serial.println("aluminum silenced");
          delay(1000);
          linnear.rotate(whiskPos);
//          stepper.disable();
          linnear.disable();
          digitalWrite(3,HIGH);
          delay(100);
          digitalWrite(3,LOW);
          delay(100);
          digitalWrite(3,HIGH);
          delay(100);
          digitalWrite(3,LOW);
         
          
        }
        if (ch == 'n')
        {
          
          linnear.enable();
          linnear.rotate(-whiskPos);
          stepper.move(-stepperAngle);
          delay(100);
          
          stepperAngle = 0;
          Serial.println("non");
          delay(1000);
          linnear.rotate(whiskPos);
//          stepper.disable();
          linnear.disable();
          digitalWrite(3,HIGH);
          delay(100);
          digitalWrite(3,LOW);
          delay(100);
          digitalWrite(3,HIGH);
          delay(100);
          digitalWrite(3,LOW);
          delay(100);
          digitalWrite(3,HIGH);
          delay(100);
          digitalWrite(3,LOW);
         
          
          
        }
      }

      
if (digitalRead(11) == HIGH)
  {
        
        randomSeed(micros() +  Serial.read());
        for (int j =0;j<5;j++)
        {
          int pos = random(6);
          int t = randAr[j];
          randAr[j] = randAr[pos];
          randAr[pos] = t;
          
          
        }
        
        for (int i=0;i<6;i++)
        {
          
          int chRND = randAr[i];
          Serial.print(chRND);
        
        switch (chRND){
        case 1:
        
          linnear.enable();
        linnear.rotate(-whiskPos);
        stepper.move(-stepperAngle);
          delay(100);
          stepper.move(32*MICROSTEPS);
          stepperAngle = 32*MICROSTEPS;
          Serial.println(": aluminum");
          delay(1000);
          linnear.rotate(whiskPos);
//          stepper.disable();
          linnear.disable();
          delay(500);
          digitalWrite(3,HIGH);
          delay(100);
          digitalWrite(3,LOW);
          countAll++;
        break;
        
        
        
        
        case 2:
        
          linnear.enable();
        linnear.rotate(-whiskPos);
          stepper.move(-stepperAngle);
          delay(100);
          stepper.move(64*MICROSTEPS);
          stepperAngle = 64*MICROSTEPS;
          Serial.println(": aluminum silenced");
          delay(1000);
          linnear.rotate(whiskPos);
//          stepper.disable();
          linnear.disable();
          digitalWrite(3,HIGH);
          delay(100);
          digitalWrite(3,LOW);
          delay(100);
          digitalWrite(3,HIGH);
          delay(100);
          digitalWrite(3,LOW);
          countAll++;
        break;
        
        
        
        case 3:
        
          linnear.enable();
        linnear.rotate(-whiskPos);
        stepper.move(-stepperAngle);
          delay(100);
          
          stepperAngle = 0;
          Serial.println(": non");
          delay(1000);
          linnear.rotate(whiskPos);
//          stepper.disable();
          linnear.disable();
          digitalWrite(3,HIGH);
          delay(100);
          digitalWrite(3,LOW);
          delay(100);
          digitalWrite(3,HIGH);
          delay(100);
          digitalWrite(3,LOW);
          delay(100);
          digitalWrite(3,HIGH);
          delay(100);
          digitalWrite(3,LOW);
          countAll++;
        break;
        
        
      }
      Serial.print("countAll = ");
      Serial.println(countAll);
      
      delay(30000);
  }

}   
   
    
}


void advancemotor() {
  
  linnear.startBrake();
  linnear.rotate(180);
  Serial.println("stopped");
  
  
  
  
}
