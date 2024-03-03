#include <Arduino.h>
#include <BluetoothSerial.h>
#include "Hexapod.h"
#include "ServoCalibrator.h"
#include "ServoTester.h"
#include "Configuration.h"
#include <esp32/clk.h>

BluetoothSerial bluetooth;
int bluetoothMessage;
Hexapod hexapod = Hexapod();

ServoCalibrator servoCalibrator = ServoCalibrator();
ServoTester servoTester = ServoTester();

void setup()
{
  Serial.begin(115200);

  bluetooth.begin("Hexapod");

  pinMode(LED_BUILTIN, OUTPUT);

  switch (MODE)
  {
  case 1:
    servoCalibrator.setup();
    break;

  case 2:
    servoTester.setup();
    break;

  default:
    hexapod.init();
    break;
  }
}

void bluetoothController()
{

  if (bluetooth.available())
  {
    bluetoothMessage = bluetooth.read();
  }
}

void serialController()
{
  Serial.println("Enter 0-360 for walk direction, 'R' (Rotate CW), 'L' (Rotate CCW)  or 'S' (stop):");

  while (Serial.available() == 0)
  {
  }

  String input = Serial.readString();
  input.trim();
  input.toUpperCase();

  if (input[0] == 'S')
  {
    hexapod.stop();

    Serial.println("Stopping Hexapod.");
  }
  else if (input[0] == 'R')
  {
    hexapod.startRotate(RotateDirection::CW);
  }
  else if (input[0] == 'L')
  {
    hexapod.startRotate(RotateDirection::CCW);
  }
  else
  {
    int walkDirection = input.toInt();
    walkDirection = std::clamp(walkDirection, 0, 360);

    hexapod.startWalk(walkDirection);

    Serial.print("Walking towards ");
    Serial.println(walkDirection);
  }
}

void hexapodController()
{
  bluetoothController();

  if (SERIAL_CONTROL_MODE)
  {
    serialController();
  }
}

void loop()
{
  switch (MODE)
  {
  case 1:
    servoCalibrator.loop();
    break;

  case 2:
    servoTester.loop();
    break;

  default:
    hexapodController();
    break;
  }
}