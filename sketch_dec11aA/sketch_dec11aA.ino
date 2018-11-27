/*
Line Follower Robot code(proportional term used only among the three term of PID)
By MD ANWARUL KAWCHAR
METROPOLITAN UNIVERSITY, SYLHET, BANGLADESH
*/
#include <QTRSensors.h>//you must have to include this library

#define Kp .06// you can change it little bit but not more
#define rightMaxSpeed 200
#define leftMaxSpeed 200
#define basespeed 150
#define minimum_speed 0
#define NUM_SENSORS  6 
#define TIMEOUT    2500
#define rightMotorPWM1 10 //give front speed and connected to D10
#define rightMotorPWM2 11 //give back speed connected to D11
#define leftMotorPWM1 3 //give front speed and connected to D3
#define leftMotorPWM2 9 //give back speed connected to D9


int rightMotorSpeed;
int leftMotorSpeed;
int rightMotorSpeed2 = 0;
int leftMotorSpeed2 = 0;

QTRSensorsRC qtrrc((unsigned char[]) {A0,A1,A2,A3,A4,A5}, NUM_SENSORS, TIMEOUT, QTR_NO_EMITTER_PIN); //total 8 sensor connected to D2, D4, D5, D6, D7, D8, D12, D13(remember D2 is leftmost sensor and D13 is rightmost sensor)
unsigned int sensorValues[NUM_SENSORS];



void setup()
{
  Serial.begin(9600);
  pinMode(rightMotorPWM1, OUTPUT);
  pinMode(rightMotorPWM2, OUTPUT);
  pinMode(leftMotorPWM1, OUTPUT);
  pinMode(leftMotorPWM2, OUTPUT);







  delay(500);
  int i;
  for (int i = 0; i < 200; i++) // calibrate for sometime by sliding the sensors across the line, or you may use auto-calibration instead
  {
    qtrrc.calibrate();
  }
  wait();
  delay(2000); // wait for 2s to position the bot before entering the main loop

}

void loop()
{
     //unsigned int position = qtrrc.readLine(sensorValues);              //black line
     
    unsigned int position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON, 1);                //white line
    int error = -(position - 2500);
    //sum_of_sensors_value = sensorValues[0] + sensorValues[1] + sensorValues[2] + sensorValues[3] + sensorValues[4] + sensorValues[5] + sensorValues[6] + sensorValues[7];


    {
      {
        int motorSpeed = error * Kp;

        rightMotorSpeed = basespeed + motorSpeed;
        leftMotorSpeed = basespeed - motorSpeed;
//        rightMotorSpeed2 = 0;
//        leftMotorSpeed2 = 0;

        if (rightMotorSpeed > rightMaxSpeed) rightMotorSpeed = rightMaxSpeed;
        if (leftMotorSpeed > leftMaxSpeed ) leftMotorSpeed = leftMaxSpeed;
        if (rightMotorSpeed < minimum_speed) rightMotorSpeed = minimum_speed;
        if (leftMotorSpeed < minimum_speed) leftMotorSpeed = minimum_speed;
      }


      {
        motor();
      }
    }







        {//for sensor read//see ==============Serial.Begin
          // print the sensor values as numbers from 0 to 1000, where 0 means maximum reflectance and
          // 1000 means minimum reflectance, followed by the line position
          for (unsigned char i = 0; i < NUM_SENSORS; i++)
          {
            Serial.print(sensorValues[i]);
            Serial.print('\t');
          }

          Serial.print('\t');
          Serial.print(error); // comment this line out if you are using raw values
          Serial.println(); // uncomment this line if you are using raw values
    //      Serial.print('\t');
    //      Serial.print(leftMotorSpeed);
    //      Serial.print('\t');
    //      Serial.println(rightMotorSpeed);
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
