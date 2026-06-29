#include "StateMachine.h"
#include "Constants.h"
#include "Hexapod.h"

StateMachine *StateMachine::instance = NULL;

StateMachine::StateMachine()
{
    instance = this;
}

StateMachine *StateMachine::getInstance()
{
    return instance;
}

void StateMachine::init()
{
    this->faceAnimator = DisplayManager::getInstance()->faceAnimator;
}

State StateMachine::getState()
{
    return this->state;
}

void StateMachine::idle()
{
    this->faceAnimator->setExpression(FACE_NEUTRAL);
    this->faceAnimator->setState(FACE_IDLE);
    this->faceAnimator->setEyePosition(Vec2(0, 0));

    Hexapod::getInstance()->stand();

    startIdleMS = millis();

    state = State::STATE_IDLE;
};

void StateMachine::sleep()
{
    this->faceAnimator->setExpression(FACE_SLEEP);
    this->faceAnimator->setState(FACE_STILL);
    this->faceAnimator->setEyePosition(Vec2(0, 0));

    Hexapod::getInstance()->rest();

    startSleepMS = millis();

    state = STATE_SLEEP;
}

void StateMachine::moving(int moveDir)
{
    this->faceAnimator->setExpression(FACE_NEUTRAL);
    this->faceAnimator->setState(FACE_STILL);

    if (moveDir >= -10 && moveDir <= 10 || moveDir >= 350)
    {
        this->faceAnimator->setEyePosition(Vec2(MAX_EYE_X_OFFSET, 0));
    }
    else if (moveDir >= 170 && moveDir <= 190)
    {
        this->faceAnimator->setEyePosition(Vec2(-(MAX_EYE_X_OFFSET), 0));
    }
    else
    {
        this->faceAnimator->setEyePosition(Vec2(0, 0));
    }

    state = State::SATE_MOVING;
}

void StateMachine::loop()
{
    switch (state)
    {
    case State::STATE_IDLE:
    {
        ulong elapsedIdleMS = millis() - startIdleMS;
        double elapsedNormalized = elapsedIdleMS / (double)STATE_DURATION_IDLE_TO_SLEEP;
        if (elapsedNormalized >= 1)
        {
            sleep();
        }
        else if (elapsedNormalized >= 0.5)
        {
            this->faceAnimator->setExpression(FACE_TIRED);
        }
        break;
    }
    case State::STATE_SLEEP:
        if (millis() - startSleepMS >= STATE_DURATION_SLEEP_TO_OFF)
        {
            DisplayManager::getInstance()->clearDisplay();
            Hexapod::getInstance()->sleep();
        }
        break;
    default:
        break;
    }
}