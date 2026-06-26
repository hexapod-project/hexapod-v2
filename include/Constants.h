#pragma once

#include <BLECharacteristic.h>
#include <BLEUtils.h>
#include <string>

#define SERVO_COUNT 18

#define DATA_DELIMITER '|'

#define NAME "HEXBOTv2"
#define PRODUCT_CODE "01"

#define CONCAT(x, y) x##y
#define STR(x) #x
#define SKU NAME "-" PRODUCT_CODE

#define HEXAPOD_SERVICE_UUID "a9b02c9e-1b0b-4b97-8b68-80af4a3bc6c4"
extern BLECharacteristic HEXAPOD_MODE_CHARACTERISTIC;
extern BLECharacteristic HEXAPOD_REST_CHARACTERISTIC;

// Motion service
#define MOTION_SERVICE_UUID "42e91a79-610e-40b3-8873-fd65d2c0d581"
extern BLECharacteristic MOVE_CHARACTERISTIC;
extern BLECharacteristic ROTATE_CHARACTERISTIC;
extern BLECharacteristic ROLLPITCH_CHARACTERISTIC;

// Calibrate service
#define CALIBRATE_SERVICE_UUID "2f35a75b-1a6c-481d-b781-22f5d3c17420"
extern BLECharacteristic PWM_PULSE_CHARACTERISTIC;
extern BLECharacteristic MOVE_SERVO_CHARACTERISTIC;

#define SERVO_PULSE_INTERVAL 750

#define MIN_PWM 500
#define MAX_PWM 2500

#define CLK_PIN 25 // ESP32 pin GPIO25 connected to the rotary encoder's CLK pin
#define DT_PIN 26  // ESP32 pin GPIO26 connected to the rotary encoder's DT pin
#define SW_PIN 27  // ESP32 pin GPIO27 connected to the rotary encoder's SW pin

#define SLEEP_DELAY 5000