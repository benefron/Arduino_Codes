// Chapter 5 - Motor Control
// Controlling Speed
// By Cornel Amariei for Packt Publishing

// Include the Servo library
#include <Servo.h>

// Declare the Servo pin
int servoPin = 9;
// Create a servo object
Servo Servo1;

void setup() {
  // We need to attach the servo to the used pin number
  Servo1.attach(servoPin);
  Serial.begin(9600);
  pinMode(A8,INPUT);
  randomSeed(analogRead(0));
  while (! Serial); // Wait until Serial is ready - Leonardo
  Serial.println("1- aluminum foil 2-paper 3- empty");
}


void loop() {
  
  if (Serial.available());
  {
    char ch = Serial.read();
    int waitMin = 0;
    if (digitalRead(A8) == HIGH)
    {
      Serial.println("Starting experiment");
      int chInt = random(1,3);
      char ch = chInt;
      Serial.println(ch);
      int waitMin = random(3, 6);
      Serial.println(waitMin);
    }
    
    if (ch == '1')
    {
      Servo1.attach(servoPin);
      Servo1.write(180);
      Serial.println("aluminum");
      delay(1000);
      Servo1.detach();
      
      
    }
    if (ch == '2')
    {
      Servo1.attach(servoPin);
      Servo1.write(25);
      Serial.println("aluminum silenced");
      delay(1000);
      Servo1.detach();
      
      
    }
    if (ch == '3')
    {
      Servo1.attach(servoPin);
      Servo1.write(90);
      Serial.println("non");
      delay(1000);
      Servo1.detach();
      
      
    }
    delay(60000*waitMin)
    
  ;}
}
