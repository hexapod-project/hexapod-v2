#include "ServoTester.h"
#include "Configuration.h"

void ServoTester::setup()
{
    servoDriverLeft->begin();
    servoDriverLeft->setPWMFreq(PWM_FREQ);

    servoDriverRight->begin();
    servoDriverRight->setPWMFreq(PWM_FREQ);
    
    Serial.println("Servo Tester Started.");
}

void ServoTester::loop()
{
    // Turns off all servos
    for (int i = 0; i < 16; i++)
    {
        servoDriverLeft->setPWM(i, 0, 0);
        servoDriverRight->setPWM(i, 0, 0);
    }

    selectServoNo();
    setAngle();
}

void ServoTester::selectServoNo()
{
    Serial.println("Enter servo number (1-18):");

    while (Serial.available() == 0)
    {
    }

    int input = Serial.readString().toInt();
    int servoNo = std::clamp(input, 1, 18);

    selectedServo = SERVOS[servoNo];

    Serial.print("Selected servo");
    Serial.println(servoNo);
}

void ServoTester::setAngle()
{
    while (true)
    {
        Serial.print("Enter Angle (");
        Serial.print(SERVO_ANGLES_MIN);
        Serial.print("-");
        Serial.print(SERVO_ANGLES_MAX);
        Serial.println(") or\"r(restart)\":");

        while (Serial.available() == 0)
        {
        }

        String input = Serial.readString();
        input.toLowerCase();
        input.trim();

        if (input[0] == 'r')
        {
            Serial.println("Restarting test...");
            return;
        }
        else
        {
            int inputAngle = input.toInt();
            int angle = std::clamp(inputAngle, SERVO_ANGLES_MIN, SERVO_ANGLES_MAX);
            selectedServo->setAngle(angle);

            Serial.print("Angle set to ");
            Serial.println(angle);
        }
    }
}