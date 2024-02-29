#include "ServoCalibrator.h"
#include <Arduino.h>
#include <algorithm>

void ServoCalibrator::setup()
{
    driverLeft->begin();
    driverLeft->setPWMFreq(PWM_FREQ);

    driverRight->begin();
    driverRight->setPWMFreq(PWM_FREQ);
    
    Serial.println("Servo Calibrator Started.");
}

void ServoCalibrator::loop()
{
    // Turns off all servos
    for (int i = 0; i < 16; i++)
    {
        driverLeft->setPWM(i, 0, 0);
        driverRight->setPWM(i, 0, 0);
    }

    selectSides();
    selectPinNo();
    setPWMPeriod();
}

void ServoCalibrator::selectSides()
{
    Serial.println("Enter sides (0=left, 1=right):");

    while (Serial.available() == 0)
    {
    }

    int input = Serial.readString().toInt();

    if (input == 0)
    {
        selectedDriver = driverLeft;

        Serial.println("Selected LEFT driver");
    }
    else
    {
        selectedDriver = driverRight;

        Serial.println("Selected RIGHT driver");
    }
}

void ServoCalibrator::selectPinNo()
{
    Serial.println("Enter pinNo (0-15):");

    while (Serial.available() == 0)
    {
    }

    int input = Serial.readString().toInt();
    pinNo = std::clamp(input, 0, 15);

    Serial.print("Selected pin ");
    Serial.println(pinNo);
}

void ServoCalibrator::setPWMPeriod()
{
    while (true)
    {
        Serial.print("Enter PWM period (");
        Serial.print(MIN_PULSE);
        Serial.print("-");
        Serial.print(MAX_PULSE);
        Serial.println(") or\"r(restart)\":");

        while (Serial.available() == 0)
        {
        }

        String input = Serial.readString();
        input.toLowerCase();
        input.trim();

        if (input[0] == 'r')
        {
            Serial.println("Restarting calibration...");
            return;
        }
        else
        {
            int inputPeriod = input.toInt();
            int period = std::clamp(inputPeriod, MIN_PULSE, MAX_PULSE);
            selectedDriver->writeMicroseconds(pinNo, period);

            Serial.print("PWM Period set to ");
            Serial.println(period);            
        }
    }
}