#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

const int potMeterX = A0;
const int potMeterY = A1;

const int pins[] = {4, 3, 2}; 
const int numPins = sizeof(pins) / sizeof(pins[0]); // Number of pins

int potValueX = 0;
int potValueY = 0;

bool blackMode = false;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void writePixels(bool colorSwitch)
{
  potValueX = map(analogRead(potMeterX), 0, 1023, 0, 127);
  potValueY = map(analogRead(potMeterY), 0, 1023, 0, 63);
  if (colorSwitch)
  {
    display.writePixel(potValueX, potValueY, WHITE);
  }
  else
  {
    display.writePixel(potValueX, potValueY, BLACK);
  }
  
  display.display();
}

void setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  Serial.begin(9600);

  for (int i = 0; i < numPins; i++)
  {
    pinMode(pins[i], INPUT);
  }
}

void loop()
{
  static int lastActivePin = -1; //Need to be static, so it doesn't reset its value each loop

  int activePin = -1; //Each loop sets to -1 to prevent execution switch state when you don't need to
  
  for (int i = 0; i < numPins; i++)
   {
      if (digitalRead(pins[i]) == HIGH)
      {
          activePin = pins[i]; //If one of the pins was detected as HIGH, we will set activePin with detected pin
          break;
      }
  }

  if (activePin != lastActivePin)
  {
    switch (activePin)
    {
    case 4: // Pin 4 clears display
      display.clearDisplay();
      break;
    case 3: // Pin 3 toggles white and black pixel write color
      blackMode = !blackMode;
      break;
    case 2: // Pin 2 draws circle
      display.drawCircle(potValueX, potValueY, 5, WHITE);
      break;
    default:
      Serial.println("Not initialized pin!");
      break;
    }

    lastActivePin = activePin;
  }

  writePixels(blackMode);
  delay(10);
}