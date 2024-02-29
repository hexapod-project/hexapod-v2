#include "Hexapod.h"
#include "Configuration.h"
#include "Utils.h"

Hexapod::Hexapod()
{
}

void Hexapod::init()
{
    servoDriverLeft->begin();
    servoDriverLeft->setPWMFreq(PWM_FREQ);

    servoDriverRight->begin();
    servoDriverRight->setPWMFreq(PWM_FREQ);

    this->legs[LegType::LEFT_FRONT] = LEGS[LegType::LEFT_FRONT];
    this->legs[LegType::LEFT_MID] = LEGS[LegType::LEFT_MID];
    this->legs[LegType::LEFT_BACK] = LEGS[LegType::LEFT_BACK];
    this->legs[LegType::RIGHT_FRONT] = LEGS[LegType::RIGHT_FRONT];
    this->legs[LegType::RIGHT_MID] = LEGS[LegType::RIGHT_MID];
    this->legs[LegType::RIGHT_BACK] = LEGS[LegType::RIGHT_BACK];

    Vec3 baseBodyPosition = Vec3(0, 0, BODY_OFFSET_Z);
    matrix = matrix.translate(baseBodyPosition);
    originalMatrix.set(matrix);

    for (int i = 0; i < LEGS_COUNT; i++)
    {
        this->legs[i]->setRoot(&matrix);
    }

    rest();
    delay(1000);
    stand();

    Serial.println("Initialized.");
    Serial.print("Clock Frequency:");
    Serial.print("Delta Time:");
    Serial.println(getDeltaTime());

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    delay(1000);
}

void Hexapod::resetMatrix()
{
    matrix.set(originalMatrix);
}

void Hexapod::rest()
{
    resetMatrix();

    Vec3 bodyPosition = Vec3(0, 0, REST_HEIGHT);
    matrix = matrix.translate(bodyPosition);

    for (int i = 0; i < LEGS_COUNT; i++)
    {
        this->legs[i]->setFeetPosition(*FEET_POSITIONS_REST[i]);
    }
}

void Hexapod::stand()
{
    resetMatrix();

    Vec3 bodyPosition = Vec3(0, 0, STAND_HEIGHT);
    matrix = matrix.translate(bodyPosition);

    for (int i = 0; i < LEGS_COUNT; i++)
    {
        this->legs[i]->setFeetPosition(*FEET_POSITIONS_STANDING[i]);
    }
}

void Hexapod::update()
{
    
}

void Hexapod::updateLegs()
{
    for (int i = 0; i < LEGS_COUNT; i++)
    {
        this->legs[i]->update();
    }
}

void Hexapod::walk(double walkDirection)
{
}