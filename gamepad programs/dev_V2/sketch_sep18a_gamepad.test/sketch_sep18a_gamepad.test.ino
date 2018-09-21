/*
  Copyright (c) 2014-2015 NicoHood
  See the readme for credit to other people.

  Gamepad example
  Press a button and demonstrate Gamepad actions

  You can also use Gamepad1,2,3 and 4 as single report.
  This will use 1 endpoint for each gamepad.

  See HID Project documentation for more infos
  https://github.com/NicoHood/HID/wiki/Gamepad-API
*/

#include "HID-Project.h"

const int pinLed = LED_BUILTIN;
const int pinButton = 2;
static uint8_t count = 0;
int a = 0;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Sends a clean report to the host. This is important on any Arduino type.
  Gamepad.begin();
}

void loop() {
  byte swVal[31];
  /*
  static uint8_t sw,
                 sw_pin=0;
  sw = digitalRead(pinButton);
  Serial.println(sw);
    if(sw == 1){
      digitalWrite(pinLed, HIGH);
      Gamepad.press(sw_pin);
    }
    else{
      Gamepad.release(sw_pin);
      digitalWrite(pinLed, LOW);
    }
    */

    Serial.print(a);
    Serial.println(digitalRead(pinButton));
      if (a>digitalRead(pinButton)) {
        digitalWrite(pinLed, HIGH);
        Gamepad.release(1);
        Serial.print("release");
      }else{
        if(a<digitalRead(pinButton)){
          digitalWrite(pinLed, LOW);
          Gamepad.press(1);
          Serial.print("press");
        }
      }
    a = digitalRead(pinButton);

    Gamepad.xAxis(random(0xFFFF));
    Gamepad.yAxis(random(0xFFFF));
    
        Gamepad.write();
        delay(500);
}
