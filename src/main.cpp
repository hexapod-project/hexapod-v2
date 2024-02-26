#include <Arduino.h>
#include <BluetoothSerial.h>
#include "hexapod.h"

BluetoothSerial bluetooth;
int bluetoothMessage;
Hexapod hexapod = Hexapod();

void setup()
{
  bluetooth.begin("Hexapod");
}

void loop()
{
  if (bluetooth.available())
  {
    bluetoothMessage = bluetooth.read();
  }

  hexapod.update();
}
