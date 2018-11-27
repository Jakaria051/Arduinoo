#include <QTRSensors.h>
#define Kp .06
#define rightMaxSpeed 200
#define leftMaxSpeed 200
#define basespeed 150
#define minimum_speed 0
#define NUM_SENSORS  6
#define TIMEOUT    2500
#define rightMotorPWM1 10
#define rightMotorPWM2 11
#define leftMotorPWM1 3
#define leftMotorPWM2 9


int rightMotorSpeed;
int leftMotorSpeed;
int rightMotorSpeed2 = 0;
int leftMotorSpeed2 = 0;


QTRSensorsRC qtrrc((unsigned char[]) {A0,A1,A2,A3,A4,A5}, NUM_SENSORS, TIMEOUT, QTR_NO_EMITTER_PIN); 
unsigned int sensorValues[NUM_SENSORS];



void setup()
{
  
  pinMode(rightMotorPWM1, OUTPUT);
  pinMode(rightMotorPWM2, OUTPUT);
  pinMode(leftMotorPWM1, OUTPUT);
  pinMode(leftMotorPWM2, OUTPUT);




  delay(500);
  int i;
  for (int i = 0; i < 200; i++) 
  {
    qtrrc.calibrate();
  }
  wait();
  delay(2000); 
}

void loop()
{
    
    unsigned int position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 1);                
    int error = -(position - 2500);
   


    {
      {
        int motorSpeed = error * Kp;

        rightMotorSpeed = basespeed + motorSpeed;
        leftMotorSpeed = basespeed - motorSpeed;

        if (rightMotorSpeed > rightMaxSpeed) rightMotorSpeed = rightMaxSpeed;
        if (leftMotorSpeed > leftMaxSpeed ) leftMotorSpeed = leftMaxSpeed;
        if (rightMotorSpeed < minimum_speed) rightMotorSpeed = minimum_speed;
        if (leftMotorSpeed < minimum_speed) leftMotorSpeed = minimum_speed;
      }


      {
        motor();
      }
    }







        {
          for (unsigned char i = 0; i < NUM_SENSORS; i++)
          {
            Serial.print(sensorValues[i]);
            Serial.print('\t');
          }

          Serial.print('\t');
          Serial.print(error); 
          Serial.println(); 
   
        }
  }


  void wait()
{
  analogWrite(rightMotorPWM1, 0);
  analogWrite(rightMotorPWM2, 0);
  analogWrite(leftMotorPWM1, 0);
  analogWrite(leftMotorPWM2, 0);
}

void motor() {
  analogWrite(rightMotorPWM1, rightMotorSpeed);
  analogWrite(rightMotorPWM2, rightMotorSpeed2);
  analogWrite(leftMotorPWM1, leftMotorSpeed);
  analogWrite(leftMotorPWM2, leftMotorSpeed2);
}
