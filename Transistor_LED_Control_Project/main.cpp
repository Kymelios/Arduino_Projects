#include <Arduino.h>

const int buttonPin = 7;
const int transPin = 8;

int currLightButtonState = LOW;
int prevLightButtonState = LOW;
int lightState = LOW;

void setup()
{
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(transPin, OUTPUT);
}

void loop() 
{
  currLightButtonState = digitalRead(buttonPin); // It reads the state of the pushbutton value
  Serial.println(currLightButtonState);        

  if (currLightButtonState != prevLightButtonState) 
  {
    if (currLightButtonState == HIGH) 
    {
      lightState = !lightState; 
    }
  }

  if (lightState == HIGH) 
  {
    digitalWrite(transPin, HIGH);
  } 
  else
  {
    digitalWrite(transPin, LOW);
  }
  
  prevLightButtonState = currLightButtonState; // Saving the current state of the last state each loop passed
  delay(10);
}