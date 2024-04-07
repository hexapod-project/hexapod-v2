#include "Constants.h"

BLECharacteristic HEXAPOD_MODE_CHARACTERISTIC("e87e1c16-1a8d-4e0e-b6af-6c4a22bbd1ae", BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);

BLECharacteristic MOVE_CHARACTERISTIC("7e3b9a17-44bb-4f39-9ff7-d2e8c1e4aa62", BLECharacteristic::PROPERTY_WRITE_NR | BLECharacteristic::PROPERTY_WRITE);
BLECharacteristic ROTATE_CHARACTERISTIC("a57dcdea-ef1f-43ae-b7b6-76dcd5c4f0e4", BLECharacteristic::PROPERTY_WRITE_NR | BLECharacteristic::PROPERTY_WRITE);
BLECharacteristic ROLLPITCH_CHARACTERISTIC("e8207c3d-4d25-494f-8b3d-b2c2af7e96e9", BLECharacteristic::PROPERTY_WRITE_NR | BLECharacteristic::PROPERTY_WRITE);

BLECharacteristic PWM_PULSE_CHARACTERISTIC("9e31f7cb-82d7-45e2-9484-78aef34d4a7a", BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE_NR);
BLECharacteristic MOVE_SERVO_CHARACTERISTIC("c4d6a3b7-5b22-4ec0-9bc3-e1194cb9782d", BLECharacteristic::PROPERTY_WRITE_NR);