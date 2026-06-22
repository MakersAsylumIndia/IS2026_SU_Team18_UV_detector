#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Common OLED I2C address
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
);

int counter = 0;

void setup()
{
  Serial.begin(9600);

  // Start OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS))
  {
    Serial.println("OLED not found!");
    while (1);
  }

  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.println("OLED TEST");

  display.setTextSize(1);
  display.setCursor(0, 30);
  display.println("Arduino Nano");

  display.display();

  delay(2000);
}

void loop()
{
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.println("UV Meter");

  display.setTextSize(1);

  display.setCursor(0, 30);
  display.print("Count: ");
  display.println(counter);

  display.setCursor(0, 45);
  display.println("OLED OK");

  display.display();

  counter++;

  delay(1000);
}
