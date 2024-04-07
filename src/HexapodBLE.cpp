#include "HexapodBLE.h"
#include "Configuration.h"
#include "Constants.h"

void HexapodBLE::initBLE(BLEServerCallbacks *bleServerCallbacks,
                         BLECharacteristicCallbacks *moveCharacteristicCallbacks,
                         BLECharacteristicCallbacks *rotateCharacteristicCallbacks,
                         BLECharacteristicCallbacks *rollPitchCharacteristicCallbacks,
                         BLECharacteristicCallbacks *pwmPulseCharacteristicCallbacks,
                         BLECharacteristicCallbacks *moveServoCharacteristicCallbacks,
                         BLECharacteristicCallbacks *hexapodModeCharacteristicCallbacks)
{
    BLEDevice::init(SKU);

    bleServer = BLEDevice::createServer();

    bleServer->setCallbacks(bleServerCallbacks);

    BLEService *motionService = bleServer->createService(MOTION_SERVICE_UUID);
    motionService->addCharacteristic(&MOVE_CHARACTERISTIC);
    motionService->addCharacteristic(&ROTATE_CHARACTERISTIC);
    motionService->addCharacteristic(&ROLLPITCH_CHARACTERISTIC);

    MOVE_CHARACTERISTIC.setCallbacks(moveCharacteristicCallbacks);
    ROTATE_CHARACTERISTIC.setCallbacks(rotateCharacteristicCallbacks);
    ROLLPITCH_CHARACTERISTIC.setCallbacks(rollPitchCharacteristicCallbacks);

    BLEService *calibrateService = bleServer->createService(CALIBRATE_SERVICE_UUID);
    calibrateService->addCharacteristic(&PWM_PULSE_CHARACTERISTIC);
    calibrateService->addCharacteristic(&MOVE_SERVO_CHARACTERISTIC);

    PWM_PULSE_CHARACTERISTIC.setCallbacks(pwmPulseCharacteristicCallbacks);
    MOVE_SERVO_CHARACTERISTIC.setCallbacks(moveServoCharacteristicCallbacks);

    BLEService *hexapodService = bleServer->createService(HEXAPOD_SERVICE_UUID);
    hexapodService->addCharacteristic(&HEXAPOD_MODE_CHARACTERISTIC);

    HEXAPOD_MODE_CHARACTERISTIC.setCallbacks(hexapodModeCharacteristicCallbacks);

    motionService->start();
    calibrateService->start();
    hexapodService->start();

    BLEAdvertising *advertising = BLEDevice::getAdvertising();
    advertising->addServiceUUID(MOTION_SERVICE_UUID);
    advertising->addServiceUUID(CALIBRATE_SERVICE_UUID);

    bleServer->startAdvertising();
}