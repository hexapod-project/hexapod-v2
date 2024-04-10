#include <string>
#include <Arduino.h>
#include <Preferences.h>

#include "Hexapod.h"
#include "Configuration.h"
#include "HexapodBLE.h"
#include "Constants.h"
#include "Calibrator.h"
#include "Utils.h"

bool isConnected = false;

int bluetoothMessage;
Hexapod hexapod = Hexapod();
HexapodBLE hexapodBLE = HexapodBLE();
Calibrator calibrator = Calibrator(&hexapod);

class HexapodBLEServerCallbacks : public BLEServerCallbacks
{
  void onConnect(BLEServer *server)
  {
    Serial.println("Bluetooh Connected");
    server->getAdvertising()->stop();
  }

  void onDisconnect(BLEServer *server)
  {
    Serial.println("Bluetooth Disconnected");
    server->startAdvertising();
    hexapod.stop();
  }
};

class MoveCharacteristicCallbacks : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *characteristic)
  {
    std::string moveData = characteristic->getValue();
    int walkDirection = std::stoi(moveData);

    if (walkDirection >= 0)
    {
      hexapod.startWalk(walkDirection);
    }
    else
    {
      hexapod.stop();
    }
  }
};

class RotateCharacteristicCallbacks : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *characteristic)
  {
    std::string moveData = characteristic->getValue();
    RotateDirection rotateDirection = static_cast<RotateDirection>(std::stoi(moveData));

    switch (rotateDirection)
    {
    case RotateDirection::ROTATE_LEFT:
    case RotateDirection::ROTATE_RIGHT:
      hexapod.startRotate(rotateDirection);
      break;
    default:
      hexapod.stop();
    }
  }
};

class RollPitchCharacteristicCallbacks : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *characteristic)
  {
    std::string rollPitchData = characteristic->getValue();
    int rollPitchAngle = std::stoi(rollPitchData);

    if (rollPitchAngle >= 0)
    {
      hexapod.rollAndPitch(rollPitchAngle);
    }
    else
    {
      hexapod.stand();
    }
  }
};

class PWMPulseCharacteristicCallbacks : public BLECharacteristicCallbacks
{
  void onRead(BLECharacteristic *characteristic)
  {
    uint8_t *calibrationSettings = calibrator.getCalibrationSettings();
    std::string value = byteArrayToString(calibrationSettings, SERVO_COUNT * sizeof(u_int16_t));

    characteristic->setValue(value);
  }

  void onWrite(BLECharacteristic *characteristic)
  {
    std::string pwmPulseData = characteristic->getValue();

    uint8_t servoIndex = pwmPulseData[0];
    uint16_t pulse = (pwmPulseData[1] << 8) | pwmPulseData[2];

    calibrator.setPWMPulse(servoIndex, pulse);
  }
};

class MoveServoCharacteristicCallbacks : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *characteristic)
  {
    std::string pwmPulseData = characteristic->getValue();

    uint8_t servoIndex = pwmPulseData[0];
    short angle = pwmPulseData[1] + SERVO_ANGLES_MIN;

    calibrator.testServoAngle(servoIndex, angle);
  }
};

class HexapodModeCharacteristicCallbacks : public BLECharacteristicCallbacks
{
  void onRead(BLECharacteristic *characteristic)
  {
    HexapodMode mode = hexapod.getMode();

    characteristic->setValue(std::to_string(mode));
  }

  void onWrite(BLECharacteristic *characteristic)
  {
    std::string modeData = characteristic->getValue();
    HexapodMode mode = static_cast<HexapodMode>(std::stoi(modeData));

    hexapod.switchMode(mode);
  }
};

class HexapodRestCharacteristicCallbacks : public BLECharacteristicCallbacks
{
  void onRead(BLECharacteristic *characteristic)
  {
    bool isRest = hexapod.isRest();

    characteristic->setValue(std::to_string(isRest));
  }

  void onWrite(BLECharacteristic *characteristic)
  {
    std::string isRest = characteristic->getValue();

    if (isRest == "1")
    {
      hexapod.rest();
    }
    else
    {
      hexapod.stand();
    }
  }
};

void setup()
{
  Serial.begin(115200);

  hexapodBLE.initBLE(new HexapodBLEServerCallbacks(),
                     new MoveCharacteristicCallbacks(),
                     new RotateCharacteristicCallbacks(),
                     new RollPitchCharacteristicCallbacks(),
                     new PWMPulseCharacteristicCallbacks(),
                     new MoveServoCharacteristicCallbacks(),
                     new HexapodModeCharacteristicCallbacks(),
                     new HexapodRestCharacteristicCallbacks());

  pinMode(LED_BUILTIN, OUTPUT);

  calibrator.init();
  hexapod.init();
}

void loop()
{
}