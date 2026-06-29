#include "FaceAnimator.h"
#include "Configuration.h"

FaceAnimator *FaceAnimator::instance = NULL;

FaceAnimator::FaceAnimator(Adafruit_SH1106G *display)
{
    this->display = display;
    this->instance = this;
}

void FaceAnimator::loop()
{
    if (instance->isHidden)
    {
        return;
    }

    instance->display->clearDisplay();
    instance->display->setTextColor(SH110X_WHITE);
    instance->display->setTextSize(TEXT_SIZE);
    instance->display->setCursor(0, 0);
    ulong currMillis = millis();

    if (instance->currentState == FaceState::FACE_NONE)
    {
        instance->display->display();
        return;
    }

    bool isEyesOpen = instance->currEyeHeight >= EYE_HEIGHT - 1;
    bool isEyesClosed = instance->currEyeHeight <= CLOSED_EYE_HEIGHT + 1;
    bool isEyesCentered = instance->currEyeOffset.magnitude() <= 0.1;
    bool isEyesAtNextOffset = (instance->currEyeOffset - instance->nextEyeOffset).magnitude() <= 0.1;

    if (instance->currentExpression != FaceExpression::FACE_SLEEP)
    {
        instance->tweenMultiplier = TWEEN_MULTIPLIER;
        // Blinking
        if (isEyesOpen && currMillis >= instance->nextBlinkMS)
        {
            instance->nextEyeHeight = CLOSED_EYE_HEIGHT;
            instance->nextBlinkMS = currMillis + random(1, MAX_BLINK_INTERVAL_S) * 1000;
        }
        else if (isEyesClosed) // Instantly re-open eyes for the blinking effect
        {
            instance->nextEyeHeight = EYE_HEIGHT;
        }
    }
    else
    {
        // Sleep
        instance->tweenMultiplier = SLEEP_TWEEN_MULTIPLIER;
        instance->nextEyeHeight = CLOSED_EYE_HEIGHT;
        instance->nextEyeOffset.x = 0;

        if (abs(instance->currEyeOffset.y - instance->nextEyeOffset.y) <= 0.01)
        {
            if (instance->nextEyeOffset.y == 0)
            {
                instance->nextEyeOffset.y = 5;
            }
            else
            {
                instance->nextEyeOffset.y = 0;
            }
        }
    }

    switch (instance->currentState)
    {
    case FaceState::FACE_IDLE:
        // Moving eyes
        if (isEyesAtNextOffset && currMillis >= instance->nextPosChangeMS)
        {
            if (isEyesCentered)
            {
                instance->nextEyeOffset.x = random(-MAX_X_OFFSET, MAX_X_OFFSET);
                instance->nextEyeOffset.y = random(-MAX_Y_OFFSET, MAX_Y_OFFSET);
                instance->nextPosChangeMS = currMillis + MIN_POS_CHANGE_INTERVAL_S * 1000;
            }
            else
            {
                instance->nextEyeOffset.x = 0;
                instance->nextEyeOffset.y = 0;
                instance->nextPosChangeMS = currMillis + random(MIN_POS_CHANGE_INTERVAL_S, MAX_POS_CHANGE_INTERVAL_S) * 1000;
            }
        }
        break;
    }

    if (DEBUG_FACE)
    {
        instance->display->printf("ceh: %.3f,iseh: %d, x: %.2f, y: %.2f", instance->currEyeHeight, instance->currEyeHeight == instance->nextEyeHeight, instance->currEyeOffset.x, instance->currEyeOffset.y);
    }

    instance->drawFace();

    instance->display->display();
}

void FaceAnimator::drawFace()
{
    if (currEyeHeight != nextEyeHeight)
    {
        currEyeHeight += (nextEyeHeight - currEyeHeight) * TWEEN_MULTIPLIER; // Simple linear interpolation for blink animation
        currEyeHeight = roundf(currEyeHeight);
    }

    if (currEyeOffset.x != nextEyeOffset.x || currEyeOffset.y != nextEyeOffset.y)
    {
        currEyeOffset.x += (nextEyeOffset.x - currEyeOffset.x) * this->tweenMultiplier;
        currEyeOffset.y += (nextEyeOffset.y - currEyeOffset.y) * this->tweenMultiplier;
    }

    const double halfEyeHeight = currEyeHeight * 0.5;
    const int leftEyeYPos = SCREEN_HEIGHT * 0.5 - halfEyeHeight + currEyeOffset.y;
    const int rightEyeYPos = SCREEN_HEIGHT * 0.5 - halfEyeHeight + currEyeOffset.y;

    const int leftEyeXPos = SCREEN_WIDTH * 0.5 - EYE_WIDTH - EYE_GAP * 0.5 + currEyeOffset.x;
    const int rightEyeXPos = SCREEN_WIDTH * 0.5 + EYE_GAP * 0.5 + currEyeOffset.x;

    this->display->fillRoundRect(leftEyeXPos, leftEyeYPos, EYE_WIDTH, currEyeHeight, EYE_RADIUS, SH110X_WHITE);
    this->display->fillRoundRect(rightEyeXPos, rightEyeYPos, EYE_WIDTH, currEyeHeight, EYE_RADIUS, SH110X_WHITE);

    switch (this->currentExpression)
    {
    case FaceExpression::FACE_HAPPY:
        this->display->fillRect(leftEyeXPos, leftEyeYPos + currEyeHeight - halfEyeHeight, EYE_WIDTH, currEyeHeight, SH110X_BLACK);
        this->display->fillRect(rightEyeXPos, rightEyeYPos + currEyeHeight - halfEyeHeight, EYE_WIDTH, currEyeHeight, SH110X_BLACK);
        break;
    case FaceExpression::FACE_ANGRY:
        this->display->fillTriangle(leftEyeXPos, leftEyeYPos, leftEyeXPos + EYE_WIDTH, leftEyeYPos, leftEyeXPos + EYE_WIDTH, leftEyeYPos + halfEyeHeight, SH110X_BLACK);
        this->display->fillTriangle(rightEyeXPos, rightEyeYPos, rightEyeXPos + EYE_WIDTH, rightEyeYPos, rightEyeXPos, rightEyeYPos + halfEyeHeight, SH110X_BLACK);
        break;
    case FaceExpression::FACE_SAD:
        this->display->fillTriangle(leftEyeXPos, leftEyeYPos, leftEyeXPos + EYE_WIDTH, leftEyeYPos, leftEyeXPos, leftEyeYPos + halfEyeHeight, SH110X_BLACK);
        this->display->fillTriangle(rightEyeXPos, rightEyeYPos, rightEyeXPos + EYE_WIDTH, rightEyeYPos, rightEyeXPos + EYE_WIDTH, rightEyeYPos + halfEyeHeight, SH110X_BLACK);
        break;
    case FaceExpression::FACE_TIRED:
        this->display->fillRect(leftEyeXPos, leftEyeYPos, EYE_WIDTH, halfEyeHeight, SH110X_BLACK);
        this->display->fillRect(rightEyeXPos, rightEyeYPos, EYE_WIDTH, halfEyeHeight, SH110X_BLACK);
        break;
    case FaceExpression::FACE_SLEEP:
        this->display->fillRect(leftEyeXPos, leftEyeYPos - CLOSED_EYE_HEIGHT, EYE_WIDTH, currEyeHeight, SH110X_BLACK);
        this->display->fillRect(rightEyeXPos, rightEyeYPos - CLOSED_EYE_HEIGHT, EYE_WIDTH, currEyeHeight, SH110X_BLACK);

        const unsigned int elapsedDurationMS = millis() - expressionStartMS;
        // Delay showing 'Z's so that it doesn't appear in the middle of no where
        if (elapsedDurationMS >= 1500)
        {
            // Frames count at 25 FPS
            const unsigned int elapsedFrames = (millis() - expressionStartMS - 1500) / 40;
            // frame index of 100 frames for 4 seconds of animation (100/25fps = 4s)
            const unsigned int frameIndex = elapsedFrames % 100;
            const unsigned int sleepZOffsetY = frameIndex / 100.0 * SCREEN_HEIGHT * 1.2;
            const unsigned int sleepZOffsetX = (sin(frameIndex / 30.0 * PI * 2) + 1) * 5;

            // TODO: show Zs floating up
            this->display->drawChar(rightEyeXPos + EYE_WIDTH + SLEEP_Z_OFFSET_X - sleepZOffsetX, rightEyeYPos - SLEEP_Z_OFFSET_Y - sleepZOffsetY, 'z', SH110X_WHITE, SH110X_BLACK, 2);
        }
        break;
    }
}

void FaceAnimator::setExpression(FaceExpression expression)
{
    if (currentExpression == expression)
    {
        return; // No change in expression
    }

    currentExpression = expression; // Ensure the task knows to clear the face
    expressionStartMS = millis();
}

void FaceAnimator::setState(FaceState state)
{
    if (this->currentState == state)
    {
        return;
    }

    this->currentState = state;
}

void FaceAnimator::hide()
{
    display->clearDisplay();
    display->display();
    isHidden = true;
}

void FaceAnimator::show()
{
    isHidden = false;
}

void FaceAnimator::setEyePosition(Vec2 newPos) {
    this->nextEyeOffset = newPos;
}