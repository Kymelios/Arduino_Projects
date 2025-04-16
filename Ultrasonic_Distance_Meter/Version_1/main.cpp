#include <Arduino.h>
#include <SD.h>

 //SD card module pin
const int chipSelect = 10;

//Ultrasonic sensor pins
const int echoPin = 9; 
const int trigPin = 8;

const int greenLed = 7;
const int redLed = 6;

const int lazerSwitch = 5;

const int saveButton = 4;

float duration, distance; 

void setup() 
{
  Serial.begin(9600);

  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(lazerSwitch, OUTPUT);

  digitalWrite(lazerSwitch, HIGH);

  Serial.println("Initializing SD card...");

  if (!SD.begin(chipSelect)) 
  {
    Serial.println("Card failed, or not present.");
    digitalWrite(redLed, HIGH);
    delay(300);
    digitalWrite(redLed, LOW);
    return;
  }

  Serial.println("Card initialized.");
}

void loop() 
{
  if (digitalRead(saveButton) == HIGH) 
  {
    File dataFile = SD.open("text.txt", FILE_WRITE);

    if (dataFile) 
    {
      dataFile.println(distance);
      dataFile.close();
      Serial.println("Data written to file.");

      digitalWrite(greenLed, HIGH);
      delay(300);
      digitalWrite(greenLed, LOW);
    }
    else
    {
      digitalWrite(redLed, HIGH);
      delay(300);
      digitalWrite(redLed, LOW);
    }

    delay(500);
  }

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.0343) / 2;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(100);
}