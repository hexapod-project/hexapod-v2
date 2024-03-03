#include "Hexapod.h"
#include "Configuration.h"
#include "Utils.h"

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

    gaitsManager.init(this);
    gaitsManager.selectGait(GaitType::TRIPOD);

    rest();
    delay(1000);
    stand();

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    delay(250);
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

void Hexapod::startWalk(double walkDirection)
{
    gaitsManager.startWalk(toRadians(walkDirection));
}

void Hexapod::stop()
{
    gaitsManager.stop();
}

void Hexapod::walk(WalkTranslations stepTranslations)
{
    matrix = matrix.translate(stepTranslations.bodyTranslation);

    for (int i = 0; i < LEGS_COUNT; i++)
    {
        if (std::find(stepTranslations.legs.begin(), stepTranslations.legs.end(), i) != stepTranslations.legs.end())
        {
            this->legs[i]->translateFeetPosition(stepTranslations.feetTranslation);
        }
        else
        {
            this->legs[i]->updateFeetPosition();
        }
    }
}

void Hexapod::startRotate(RotateDirection rotateDirection)
{
    gaitsManager.startRotate(rotateDirection);
}

void Hexapod::rotate(Rotations rotations)
{
    matrix = matrix.rotate(Vec3(0, 0, rotations.bodyDeltaAngle));

    for (int i = 0; i < LEGS_COUNT; i++)
    {
        if (std::find(rotations.legs.begin(), rotations.legs.end(), i) != rotations.legs.end())
        {
            this->legs[i]->rotateFeetPosition(rotations.feetDeltaAngle, Vec3(0, 0, rotations.feetZ));
        }
        else
        {
            this->legs[i]->updateFeetPosition();
        }
    }
}