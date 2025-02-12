#include <Arduino.h>
#include <Servo.h>

Servo myServo;

const int servoPin = 9;
const int controlButtons[3] = {6, 5 ,4}; //6 = Floor zero, 5 = Floor one, 4 = Floor two;
const int enablePin = 11; // Pin for H bridge 
const int rotateLeft = 3;
const int rotateRight = 2; 

int motorSpeed = 0;

int servoAngle = myServo.read();
int servoDirection = 0;
int servoActive = 0;

void setup()
{
    for (int i = 0; i < 3; i++)
    {
        pinMode(controlButtons[i], INPUT);
    }

    pinMode(enablePin, OUTPUT);    
    pinMode(rotateLeft, OUTPUT);
    pinMode(rotateRight, OUTPUT);

    digitalWrite(enablePin, LOW);
    
    digitalWrite(rotateLeft, LOW);
    digitalWrite(rotateRight, HIGH);

    myServo.attach(servoPin);
}

void loop()
{
    if (digitalRead(controlButtons[0]) == HIGH) { //Mode 1 normal fan speed
        motorSpeed = 50;
        servoActive = 1;
    }
    if (digitalRead(controlButtons[1]) == HIGH) { //Mode 2 high fan speed
        motorSpeed = 100;
        servoActive = 1;
    }
    if (digitalRead(controlButtons[2]) == HIGH) { //Mode 3 turns off fan
        motorSpeed = 0;
        servoActive = 0;
    }

    if (motorSpeed > 0)
    {
        analogWrite(enablePin, motorSpeed);
    }
    else
    {
        analogWrite(enablePin, 0);
    }

     if (servoDirection == 0 && servoActive == 1) //Servo spins till it reaches 180 degree
     {
         if (servoAngle != 180)
         {
             servoAngle++;
             myServo.write(servoAngle);
             delay(100);
         }
         else
         {
             servoDirection = 1;
         }
     }

    if (servoDirection == 1 && servoActive == 1) //Servo spins till it reaches 0 degree
     {
         if (servoAngle != 0)
         {
             servoAngle--;
             myServo.write(servoAngle);
             delay(100);
         }
         else
         {
             servoDirection = 0;
         }
     }

     delay(10);
}