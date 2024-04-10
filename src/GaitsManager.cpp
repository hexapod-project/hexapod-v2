#include "GaitsManager.h"
#include "Configuration.h"
#include "Hexapod.h"
#include "Utils.h"

GaitsManager *GaitsManager::instance = NULL;

GaitsManager::GaitsManager()
{
    this->instance = this;
}

void GaitsManager::init(Hexapod *hexapod)
{
    this->hexapod = hexapod;
}

void GaitsManager::stop()
{
    if (state == GaitsManagerStates::STOP_QUEUED || state == GaitsManagerStates::STOPPING || state == GaitsManagerStates::STOPPED)
    {
        return;
    }

    state = GaitsManagerStates::STOP_QUEUED;
}

void GaitsManager::onStopped()
{
    hexapod->stand();
    stepsCount = 0;

    vTaskDelete(NULL);
}

void GaitsManager::checkStepState()
{
    switch (state)
    {
    case GaitsManagerStates::STOP_QUEUED:
        state = GaitsManagerStates::STOPPING;
        break;
    case GaitsManagerStates::STOPPING:
        state = GaitsManagerStates::STOPPED;
        break;
    }
}

// Walk functions
void GaitsManager::updateWalkStep(void *parameter)
{
    while (true)
    {
        switch (instance->state)
        {
        case GaitsManagerStates::STOPPED:
            instance->onStopped();
            break;
        default:
            instance->_updateWalkStep();
            break;
        }

        vTaskDelay((double)1000 / STEP_FRAMERATE);
    }
}

void GaitsManager::_updateWalkStep()
{
    int maxStepsCount = selectedGait.size();

    double stepDistance = STEP_DISTANCE;

    if (stepsCount == 0 || state == GaitsManagerStates::STOP_TO_CHANGE_DIRECTION || state == GaitsManagerStates::CHANGE_DIRECTION || state == GaitsManagerStates::STOPPING)
    {
        stepDistance /= 2;
    }

    int totalFrames = STEP_FRAMERATE * STEP_DURATION;

    double interpolator = (double)stepFrame / totalFrames;
    double feetZ = sin(interpolator * M_PI) * STEP_HEIGHT;
    double feetDistance = stepDistance * interpolator;
    double bodyDistance = feetDistance / 2;

    double cosWalkDirection = cos(walkDirection);
    double sinWalkDirection = sin(walkDirection);

    Vec3 bodyPosition = Vec3(cosWalkDirection * bodyDistance, sinWalkDirection * bodyDistance, 0);
    Vec3 feetPosition = Vec3(cosWalkDirection * feetDistance, sinWalkDirection * feetDistance, feetZ);

    hexapod->walk(WalkPositions(selectedGait[stepsCount % maxStepsCount],
                                feetPosition,
                                bodyPosition,
                                stepFrame == totalFrames));

    stepFrame++;

    if (stepFrame > totalFrames)
    {
        stepFrame = 0;
        stepsCount++;

        checkWalkDirection();
        checkStepState();
    }
}

void GaitsManager::checkWalkDirection()
{
    if (newWalkDirection != -1)
    {
        switch (state)
        {
        case GaitsManagerStates::MOVING:
            state = GaitsManagerStates::STOP_TO_CHANGE_DIRECTION;
            break;
        case GaitsManagerStates::STOP_TO_CHANGE_DIRECTION:
            walkDirection = newWalkDirection;
            state = GaitsManagerStates::CHANGE_DIRECTION;
            break;
        case GaitsManagerStates::CHANGE_DIRECTION:
            newWalkDirection = -1;
            state = GaitsManagerStates::MOVING;
            break;
        }
    }
}

void GaitsManager::startWalk(double walkDirection)
{
    if (state == GaitsManagerStates::STOPPED)
    {
        this->walkDirection = walkDirection;

        state = GaitsManagerStates::MOVING;

        xTaskCreatePinnedToCore(
            updateWalkStep,
            "Update Walk Step",
            4096,
            NULL,
            1,
            NULL,
            0);
    }
    else if (state == GaitsManagerStates::MOVING && !compare(this->walkDirection, walkDirection))
    {
        this->newWalkDirection = walkDirection;
    }
}

// Rotate functions
void GaitsManager::updateRotateStep(void *parameter)
{
    while (true)
    {
        switch (instance->state)
        {
        case GaitsManagerStates::STOPPED:
            instance->onStopped();
            break;
        default:
            instance->_updateRotateStep();
            break;
        }

        vTaskDelay((double)1000 / STEP_FRAMERATE);
    }
}

void GaitsManager::_updateRotateStep()
{
    int maxStepsCount = selectedGait.size();

    double rotateAngle = -toRadians(ROTATE_ANGLE_PER_STEP);

    if (rotateDirection == RotateDirection::ROTATE_RIGHT)
    {
        rotateAngle = -rotateAngle;
    }

    int totalFrames = STEP_FRAMERATE * STEP_DURATION;

    double interpolator = (double)stepFrame / totalFrames;
    double feetZ = sin(interpolator * M_PI) * STEP_HEIGHT;
    double deltaAngle = rotateAngle / totalFrames;

    double bodyDeltaAngle = deltaAngle;
    double feetDeltaAngle = deltaAngle * 2;

    if (state == GaitsManagerStates::STOP_TO_CHANGE_DIRECTION || state == GaitsManagerStates::STOPPING)
    {
        if (stepsCount % maxStepsCount == 0)
        {
            bodyDeltaAngle = 0;
            feetDeltaAngle = 0;
            stepFrame = totalFrames;
        }
    }

    hexapod->rotate(Rotations(selectedGait[stepsCount % maxStepsCount],
                              bodyDeltaAngle,
                              feetDeltaAngle,
                              feetZ));

    stepFrame++;

    if (stepFrame > totalFrames)
    {
        stepFrame = 0;
        stepsCount++;

        checkRotateDirection();
        checkStepState();
    }
}

void GaitsManager::checkRotateDirection()
{
    if (rotateDirection != newRotateDirection)
    {
        if (state != GaitsManagerStates::STOP_TO_CHANGE_DIRECTION)
        {
            state = GaitsManagerStates::STOP_TO_CHANGE_DIRECTION;
        }
        else
        {
            state = GaitsManagerStates::MOVING;

            rotateDirection = newRotateDirection;
        }
    }
}

void GaitsManager::startRotate(RotateDirection rotateDirection)
{
    if (state == GaitsManagerStates::STOPPED)
    {
        this->rotateDirection = rotateDirection;
        this->newRotateDirection = rotateDirection;

        state = GaitsManagerStates::MOVING;

        xTaskCreatePinnedToCore(
            updateRotateStep,
            "Update Rotate Step",
            4096,
            NULL,
            1,
            NULL,
            0);
    }
    else if (this->rotateDirection != rotateDirection)
    {
        this->newRotateDirection = rotateDirection;
    }
}

void GaitsManager::selectGait(GaitType gaitType)
{
    selectedGait = GAITS[gaitType];
}

GaitsManagerStates GaitsManager::getState()
{
    return this->state;
}