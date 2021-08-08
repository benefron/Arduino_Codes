// Chapter 5 - Motor Control
// Controlling Speed
// By Cornel Amariei for Packt Publishing

// Include the Servo library
#include <Servo.h>

// Declare the Servo pin
int servoPin = 9;
int resetPin = 11;
int linerPinFwd = 14;
int linerPinBack = 15;
// Create a servo object
Servo Servo1;

void setup() {
  // We need to attach the servo to the used pin number
  digitalWrite(resetPin,HIGH);
  delay(100);
  Servo1.attach(servoPin);
  Serial.begin(9600);
  pinMode(11,INPUT);
  pinMode(2,OUTPUT);
  randomSeed(analogRead(0));
  while (! Serial); // Wait until Serial is ready - Leonardo
  Serial.println("1- aluminum foil 2-paper 3- empty");
  pinMode(linerPinFwd,OUTPUT);
  pinMode(linerPinBack,OUTPUT);
  digitalWrite(linerPinBack,HIGH);
  delay(500);
  digitalWrite(linerPinBack,LOW);
  Servo1.detach();
  
}

void(*resetFunc)(void) = 0;

void loop() {
  char ch = "3";
  digitalWrite(2,LOW);
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
        digitalWrite(linerPinBack,HIGH);
        delay(500);
        digitalWrite(linerPinBack,LOW);
        Servo1.attach(servoPin);
        Servo1.write(180);
        Serial.println("aluminum");
        delay(1000);
        Servo1.detach();
        delay(500);
        digitalWrite(linerPinFwd,HIGH);
        delay(500);
        digitalWrite(linerPinFwd,LOW);
        digitalWrite(2,HIGH);
        delay(100);
        digitalWrite(2,LOW);
        i++;
        break;
        
        
        
        case 2:
        digitalWrite(linerPinBack,HIGH);
        delay(500);
        digitalWrite(linerPinBack,LOW);
        Servo1.attach(servoPin);
        Servo1.write(25);
        Serial.println("aluminum silenced");
        delay(1000);
        Servo1.detach();
        delay(500);
        digitalWrite(linerPinFwd,HIGH);
        delay(500);
        digitalWrite(linerPinFwd,LOW);
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
        digitalWrite(linerPinBack,HIGH);
        delay(500);
        digitalWrite(linerPinBack,LOW);
        Servo1.attach(servoPin);
        Servo1.write(90);
        Serial.println("non");
        delay(1000);
        Servo1.detach();
        delay(500);
        digitalWrite(linerPinFwd,HIGH);
        delay(500);
        digitalWrite(linerPinFwd,LOW);
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
      }
      delay(60000);
  }

}

 
if (Serial.available())
  {
    ch = Serial.read();
       
    if (ch == '1')
    {
      digitalWrite(linerPinBack,HIGH);
      delay(500);
      digitalWrite(linerPinBack,LOW);
      Servo1.attach(servoPin);
      Servo1.write(180);
      Serial.println("aluminum");
      delay(1000);
      Servo1.detach();
      delay(500);
      digitalWrite(linerPinFwd,HIGH);
      delay(500);
      digitalWrite(linerPinFwd,LOW);
      digitalWrite(2,HIGH);
      delay(100);
      digitalWrite(2,LOW);
      
      
      
    }
    if (ch == '2')
    {
      digitalWrite(linerPinBack,HIGH);
      delay(500);
      digitalWrite(linerPinBack,LOW);
      Servo1.attach(servoPin);
      Servo1.write(25);
      Serial.println("aluminum silenced");
      delay(1000);
      Servo1.detach();
      delay(500);
      digitalWrite(linerPinFwd,HIGH);
      delay(500);
      digitalWrite(linerPinFwd,LOW);
      digitalWrite(2,HIGH);
      delay(100);
      digitalWrite(2,LOW);
      delay(100);
      digitalWrite(2,HIGH);
      delay(100);
      digitalWrite(2,LOW);
     
      
    }
    if (ch == '3')
    {
      digitalWrite(linerPinBack,HIGH);
      delay(500);
      digitalWrite(linerPinBack,LOW);
      Servo1.attach(servoPin);
      Servo1.write(90);
      Serial.println("non");
      delay(1000);
      Servo1.detach();
      delay(500);
      digitalWrite(linerPinFwd,HIGH);
      delay(500);
      digitalWrite(linerPinFwd,LOW);
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

}
