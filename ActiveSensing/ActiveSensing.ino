
#include <Servo.h>                    // Servo Library
#include <PID_v1.h>                   // PID Library

/***************************************
* Select pins
***************************************/
int PIN_SERVOCONTROL = 22;   // Select pin that controls the servo
int PIN_FEEDBACK = 24;   // Select pin to which the servo feedback goes
int PIN_LINEAR = 26;     // Select pin which controls the linear motor that moves the servo into place
/**************************************/
/**************************************/


/***************************************
* Variables - play with the below to adjust how the servo arrives at the target angle
***************************************/
double Kp = 0.05;  // Proportional gain - 0 means no proportional term
double Ki = 0; // Integral gain - 0 means no integral term
double Kd = 0; // Differential gain - 0 means no differential term
double MAXTIME = 3000;  // Adjust how long, in milliseconds, the servo must not move before ending the loop and waiting for the next command
int MINROT = 3; // Minimum number of rotations
int MAXROT = 6; // Maximum number of rotations
/**************************************/
/**************************************/


// Initializing other variables - do not change unless you have to
double TARGET_ANGLE;              // Target angle to achieve - varies depending on the trial type
double ANGLE = 0.0;               // Current angle read from the feedback pin (0 to 360)
double FULLANGLE = 0.0;           // Current angle read from the feedback pin, but taking into account number of rotations (0 to inf)
double SERVO_VAL = 93;            // Initial setpoint is the servo value that maintains zero motion (93 for current servo)
double OUTPUT_VAL = 0;            // Output value of the PID loop when it executes the Compute() function
int RESULT = 0;                   // Result of PID calculation
unsigned long T_HIGH = 0; // Time in which the angle encoder pulse is on high
unsigned long T_LOW = 0; // Time in which the angle encoder pulse is on low
unsigned long T_CYCLE = 0; // Time of the entire angle encoder pulse cycle
float DC = 0;           // Measure from which the servo angle is calculated
float DC_MIN = 2.9;           // From Parallax spec sheet
float DC_MAX = 97.1;          // From Parallax spec sheet
float ANGLELAST;         // The last angle detected from the servo
int TURNS ;            // The number of turns the servo has gone through
int DIRECTION ;         // The direction of servo turning
int ROTATION ;          // The number of rotations the servo should go through, in terms of angle
int q2min = 360 / 4;                      // For checking if in 1st quadrant
int q3max = q2min * 3;                      // For checking if in 4th quadrant
unsigned long TIME_STOPPED;    // Total time that the servo has not been moving
unsigned long LAST_MOVED;  // Last time the servo moved
String commandfull("undefined");  //Initialize the full command string
String command("undefined");  // Initialize the last command string

// Instantiate the PID and Servo instances
Servo CAM_CONTROL;
PID PID_LOOP(&FULLANGLE,&OUTPUT_VAL,&TARGET_ANGLE,Kp,Ki,Kd,DIRECT);

void setup()
{
  Serial.begin (9600);
  Serial.setTimeout(5);
  randomSeed(analogRead(0));              // Seed the randomizers that determine which direction/angle the servo ends up in
  // Servo initialization
  CAM_CONTROL.attach(PIN_SERVOCONTROL);                    // Set the servo control pin
  pinMode(PIN_FEEDBACK, INPUT);                        // Sets PWM pin as the feedback input pin
  pinMode(PIN_LINEAR, INPUT);                          // Sets the pin that controls the linear actuator


  // PID initialization 
  PID_LOOP.SetMode(AUTOMATIC);              // Turns the PID loop on
  PID_LOOP.SetOutputLimits(-30,30);         // Sets the PID output to a range usable by the Parallax 360 Servo
  PID_LOOP.SetSampleTime(5);              // Set the PID to actually compute every 10 ms.

}
 
void loop()
{

// The below attempts to read the latest command telling this program which trial type it is. A command of 0 received over serial means it is a no-stimulus trial, while a command of 1 means it is a stimulus trial.

   while(1)
 {

if (Serial.available() > 0)
{
  commandfull = Serial.readString();
  command=commandfull.substring(commandfull.length()-1);  // In a situation where several commands are received at once, take only the last command
  
  if(command=="0"||command=="1") // Check if the command was valid - either a 0 or 1 string
  {
    break;
  }
}
 }


// Randomize the direction
if (random(0, 2)>0.5)
{
DIRECTION=1;
}
else
{
DIRECTION=-1;  
}

// Randomize the number of rotations
ROTATION=360*round(random(MINROT, MAXROT));

// If command is 1, do full rotations, and if it is 0, do full rotations plus another half a rotation
if(command=="1")
{
TARGET_ANGLE = ROTATION*DIRECTION;
}
else
{
TARGET_ANGLE = ROTATION*DIRECTION+180*DIRECTION;
}


// Reinitialize variables
TURNS = 0;
ANGLELAST = 1000;
OUTPUT_VAL = 30;
TIME_STOPPED = 0;
LAST_MOVED = 0;


// The below loop continues until the the servo has been stopped for longer than the set time
while(TIME_STOPPED<MAXTIME)
{
  
  while(1)
  {


// The below formulas read the current angle from the feedback pin of the servo 
    T_HIGH = pulseIn(PIN_FEEDBACK, HIGH);
    T_LOW = pulseIn(PIN_FEEDBACK, LOW);
    T_CYCLE = T_HIGH + T_LOW;
    if ( T_CYCLE > 1000 && T_CYCLE < 1200)
    {
      break;              //valid T_CYCLE;
    }
  }
  DC = (100 * T_HIGH) / T_CYCLE;
  ANGLE = ((DC - DC_MIN) * 360) / (DC_MAX - DC_MIN + 1);


  if (ANGLELAST != 1000) // If ANGLELAST is 1000, it means the loop is in its first iteration so do not run. Othewise, check if the angle has passed from the 0-90 to the 270-360 quadrand or vice versa 
  // so to keep count of the full rotations.
  {
  if((ANGLE < q2min) && (ANGLELAST > q3max))
  {
      TURNS++;
  }
    // If transition from quadrant 1 to 
    // quadrant 4, decrease turns count.
    else if((ANGLELAST < q2min) && (ANGLE > q3max))
    {
      TURNS--;
    }
  }

  ANGLELAST = ANGLE;

  FULLANGLE = ANGLE + TURNS*360; // Keep track of the full angle, including rotations
/********************************************************************************/
/********************************************************************************/

  RESULT = PID_LOOP.Compute(); // Computes OUTPUT_VAL, which is the correction term for the servo movement. Result == 1 just means that the computation was completed
  
  if (RESULT == 1)
  {
    SERVO_VAL = 93 - OUTPUT_VAL; // Applies the correction term

   if (SERVO_VAL > 180) 
   {
    SERVO_VAL = 180; // Sets a limit to the input value to the servo
   }
   else if ((SERVO_VAL > 93) && (TARGET_ANGLE <0))
   {
   SERVO_VAL = SERVO_VAL + 3; // If servo overshot, ignore the PID calculation and push it back (?)
   }
    else if ((SERVO_VAL < 93)  && (TARGET_ANGLE >0))
   {
   SERVO_VAL = SERVO_VAL - 3; // If servo undershot, ignore the PID calculation and push it forward (?)
   }
    
    CAM_CONTROL.write(SERVO_VAL); //Move the servo
    
  }

if (abs(OUTPUT_VAL)<3) // If OUTPUT_VAL is below 3, the servo is still
{
  
TIME_STOPPED=TIME_STOPPED+millis()-LAST_MOVED; // Count up the time stopped

}
else
{
TIME_STOPPED=0; // Reset the time stopped
LAST_MOVED=millis();
}


}

CAM_CONTROL.write(93); // Inserted to prevent the servo from continuing to move after the end of the loop

  
}
