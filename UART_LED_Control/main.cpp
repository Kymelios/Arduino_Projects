#include <Arduino.h>

const int redLedPin = 13;
const int greenLedPin = 12;
String incomingString = "";

void setup()
{
  Serial.begin(9600);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
}

void loop()
{
  if (Serial.available() > 0)
  {
    incomingString = Serial.readString();
    incomingString.trim();
    if (incomingString == "ON")
    {
      digitalWrite(redLedPin, HIGH);
      digitalWrite(greenLedPin, HIGH);

      Serial.println("LEDs are ON");
    }
    else if (incomingString == "OFF")
    {
      digitalWrite(redLedPin, LOW);
      digitalWrite(greenLedPin, LOW);

      Serial.println("LEDs are OFF");
    }
    else if(incomingString == "BLINK")
    {
      Serial.println("LEDs are blinking!");

      for (int i = 0; i < 3; i++)
      {
        digitalWrite(redLedPin, HIGH);
        digitalWrite(greenLedPin, LOW);
        delay(500);
        digitalWrite(redLedPin, LOW);
        digitalWrite(greenLedPin, HIGH);
        delay(500);
      }
      
        digitalWrite(redLedPin, LOW);
        digitalWrite(greenLedPin, LOW);
    }
    else
    {
      Serial.println("Invalid command");
    }
  }

  delay(100);
}