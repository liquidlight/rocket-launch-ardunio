/*
  Rocket Launcher

  // Board pen colourings:
  Red:    Power
  Green:  Control
  Blue:   Ground

  // Cable colourings
  Green:  Firing Pin        2
  Blue:   Rocket Presence   3
  Purple: Button            4
  White:  LEDs              5

  // Screen
  Brown: A4 SDA
  White: A5 SCL

  // Pseudo code:
  -> If the rocket is in
    -> If the button is pressed
      -> Start count down.
      -> Launch
*/

// Screen set ups
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET A4
Adafruit_SSD1306 display(OLED_RESET);

// Pin setup
int firingPin = 2; // Pin which triggers the motor
int rocketPin = 3; // If the rocket is in
int buttonPin = 4; // Launch button
int lightsPin = 5; // Trigger the lights

boolean testingMode = false;

// Setup - runs when the arudio turns on
void setup() {

  Serial.begin(9600); // Start serial monitor

  // Outputs
  pinMode(firingPin, OUTPUT);
  pinMode(lightsPin, OUTPUT);

  // Inputs
  pinMode(rocketPin, INPUT);
  pinMode(buttonPin, INPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)

  display.setRotation(2);
  display.display();

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Rocket");
  display.println("Launcher!");
  display.display();
  delay(2000);
  display.clearDisplay();

}

// Loop - runs forever
void loop() {

  // Read binary values - will return 1 or 0
  int buttonValue = digitalRead(buttonPin);
  int rocketValue = digitalRead(rocketPin);

  Serial.print("Button:");
  Serial.print(buttonValue);
  Serial.print("\t");

  Serial.print("Rocket:");
  Serial.print(rocketValue);
  Serial.println("\t");

  display.setTextSize(1);

  if (rocketValue == 0) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Please load rocket.");
    display.display();
    display.display();
  }

  if (rocketValue == 1) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Rocket loaded");
    display.println("Ready to launch");
    if (testingMode == true) {
      display.println("");
      display.println("TESTING MODE");
    }
    display.display();


    // check if the pushbutton is pressed.
    // if it is, the buttonState is HIGH:
    if (buttonValue == 1) {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println("Rocket launching");
      display.display();

      Serial.println("Launching...");

      delay(1000);

      display.println("Standby");
      display.display();

      delay(1000);

      // Countdown from 5 - output is used to pad number
      String output = "";
      for (int countdown = 5; countdown >= 1; countdown--) {
        Serial.println(countdown);
        display.clearDisplay();
        display.setTextSize(4);
        display.setCursor(0, 0);

        display.print(output);
        display.print(countdown);

        display.display();
        digitalWrite(lightsPin, HIGH);
        delay(250);
        digitalWrite(lightsPin, LOW);
        delay(750);

        output += " ";
      }


      if (testingMode == false) {
        // Fire the rocket
        digitalWrite(firingPin, HIGH);
        delay(30);
        digitalWrite(firingPin, LOW);
      }

      Serial.println("Rocket Fired");

      display.clearDisplay();
      display.setTextSize(1);
      display.display();

      display.setTextSize(3);

      // Lights and "fire" after launch
      for (int postlaunch = 0; postlaunch <= 9; postlaunch++) {

        display.setCursor(0, 0);
        display.print(" FIRE");
        display.display();
        digitalWrite(lightsPin, HIGH);
        delay(250);

        display.clearDisplay();
        display.display();
        digitalWrite(lightsPin, LOW);
        delay(250);
      }
    }
  }
}
