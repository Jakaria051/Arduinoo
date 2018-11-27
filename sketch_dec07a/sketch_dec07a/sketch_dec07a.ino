#include <QTRSensors.h>

void calculateIntegral(); void calculateProportional(); void readValues();

#define NUM_SENSORS 8 #define TIMEOUT 2500 #define EMITTER_PIN 0 #define avgSpeed 255

int time = 0;

int pwmA = 3; int pwmB = 11; int dirA = 12; int dirB = 13;

int kp = 1; int kd = 1; int ki = 1;

int error = 0; int lastError = 0;

int proportional = 0; int derivative = 0; int integral = 0;

QTRSensorsRC qtrrc((unsigned char[]) {
  2, 4, 5, 6, 7, 8, 9, 10
},   NUM_SENSORS, TIMEOUT, EMITTER_PIN);  unsigned int sensorValues[NUM_SENSORS];


void setup() {
  Serial.begin(9600);      pinMode(pwmA, OUTPUT);     pinMode(pwmB, OUTPUT);   pinMode(dirA, OUTPUT);   pinMode(dirB, OUTPUT);      pinMode(1, OUTPUT);   for (int i = 0; i < 5; i++) {
    digitalWrite(1, HIGH);
    delay(50);
    digitalWrite(1, LOW);
    delay(950);
  }

  analogWrite(pwmA, avgSpeed);             analogWrite(pwmB, avgSpeed);
}

void loop() {
  readValues();   calculateProportional();
