#include <Arduino.h>

const int floorButtons[3] = {6, 5 ,4}; //6 = Floor zero, 5 = Floor one, 4 = Floor two;
const int enablePin = 9;
const int rotateLeft = 3;
const int rotateRight = 2; 

int motorEnabled = 0;
int motorSpeed = 30;
int motorDirection = 1;

int currentFloor = 2;
int floorSet = currentFloor;

void setup()
{
    Serial.begin(9600);

    for (int i = 0; i < 3; i++)
    {
        pinMode(floorButtons[i], INPUT);
    }

    pinMode(enablePin, OUTPUT);    
    pinMode(rotateLeft, OUTPUT);
    pinMode(rotateRight, OUTPUT);

    digitalWrite(enablePin, LOW);
}

void loop()
{
    for (int i = 0; i < 3; i++)
    {
        if (digitalRead(floorButtons[i]) == HIGH)
        {
           currentFloor = i;
        }
    }

    delay(1);

    if (currentFloor > floorSet) //Lower the elevator
    {
        digitalWrite(rotateLeft, HIGH);
        digitalWrite(rotateRight, LOW);

        digitalWrite(enablePin, HIGH);
    }
    else if(currentFloor < floorSet) //Lift up the elevator
    {
        digitalWrite(rotateLeft, LOW);
        digitalWrite(rotateRight, HIGH);

        digitalWrite(enablePin, HIGH);
    }
    else // When reached the floor, stops the motor
    {
        digitalWrite(enablePin, LOW);
        analogWrite(enablePin, 0);
    }
    
    if (currentFloor != floorSet) // Moves the elevator, but not too fast (Gonna be fixed soon)
    {
        for (int i = 20; i < 40; i++)
        {
            analogWrite(enablePin, i);
            delay(100);
        }
    }
    
    Serial.print("currentfloor: ");
    Serial.print(currentFloor);
    Serial.print(" floorSet: ");
    Serial.println(floorSet);

    floorSet = currentFloor;

    delay(100);
}