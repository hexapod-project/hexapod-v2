#pragma once

#include <BLEService.h>
#include <BLECharacteristic.h>
#include <BLEDevice.h>

class HexapodBLE
{
private:
    BLEServer *bleServer;

public:
    void initBLE(BLEServerCallbacks *bleServerCallbacks,
                 BLECharacteristicCallbacks *moveCharacteristicCallbacks,
                 BLECharacteristicCallbacks *rotateCharacteristicCallbacks,
                 BLECharacteristicCallbacks *rollPitchCharacteristicCallbacks,
                 BLECharacteristicCallbacks *pwmPulseCharacteristicCallbacks,
                 BLECharacteristicCallbacks *moveServoCharacteristicCallbacks,
                 BLECharacteristicCallbacks *hexapodModeCharacteristicCallbacks);
};