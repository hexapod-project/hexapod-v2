#include "FaceAnimator.h"

FaceAnimator::FaceAnimator(Adafruit_SH1106G *display)
{
    this->display = display;
}

void FaceAnimator::drawFace()
{
    // This function can be used to draw a static face if needed
    // For now, all animations are handled in DisplayManager
    this->display->clearDisplay();
    // this->display->drawRoundRect(0, 0, this->EYE_WIDTH, this->EYE_HEIGHT, 5, SH110X_WHITE);
    this->display->display();
}

