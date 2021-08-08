// Chapter 5 - Motor Control
// Controlling Speed
// By Cornel Amariei for Packt Publishing

// Include the Servo library
#include <Servo.h>

// Declare the Servo pin
int servoPin = 9;
int resetPin = 46;
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
}

void(*resetFunc)(void) = 0;

void loop() {
  char ch = "3";
  digitalWrite(2,LOW);
  if (digitalRead(11) == HIGH)
  {
        int randAr[15] = {1,1,1,1,1,2,2,2,2,2,3,3,3,3,3};
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
        Servo1.attach(servoPin);
        Servo1.write(180);
        Serial.println("aluminum");
        delay(1000);
        Servo1.detach();
        digitalWrite(2,HIGH);
        delay(100);
        digitalWrite(2,LOW);
        i++;
        break;
        
        
        
        case 2:
        Servo1.attach(servoPin);
        Servo1.write(25);
        Serial.println("aluminum silenced");
        delay(1000);
        Servo1.detach();
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
        Servo1.attach(servoPin);
        Servo1.write(90);
        Serial.println("non");
        delay(1000);
        Servo1.detach();
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
      Servo1.attach(servoPin);
      Servo1.write(180);
      Serial.println("aluminum");
      delay(1000);
      Servo1.detach();
      digitalWrite(2,HIGH);
      delay(100);
      digitalWrite(2,LOW);
      
      
    }
    if (ch == '2')
    {
      Servo1.attach(servoPin);
      Servo1.write(25);
      Serial.println("aluminum silenced");
      delay(1000);
      Servo1.detach();
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
      Servo1.attach(servoPin);
      Servo1.write(90);
      Serial.println("non");
      delay(1000);
      Servo1.detach();
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
