#include <Arduino.h>
#include <BluetoothSerial.h>
#include "Hexapod.h"
#include "ServoCalibrator.h"
#include "ServoTester.h"
#include "Configuration.h"

BluetoothSerial bluetooth;
int bluetoothMessage;
Hexapod *hexapod = new Hexapod();

ServoCalibrator servoCalibrator = ServoCalibrator();
ServoTester servoTester = ServoTester();

void setup()
{
  Serial.begin(115200);
  
  bluetooth.begin("Hexapod");

  switch (MODE)
  {
  case 1:
    servoCalibrator.setup();
    break;

  case 2:
    servoTester.setup();
    break;

  default:
    hexapod->init();
    break;
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
    if (bluetooth.available())
    {
      bluetoothMessage = bluetooth.read();
    }

    hexapod->update();
    break;
  }
}
