#include <Adafruit_SH110X.h>

class FaceAnimator
{
private:    
    Adafruit_SH1106G *display;

public:
    FaceAnimator(Adafruit_SH1106G *display);
    void drawFace();
    const int EYE_WIDTH = 20;
    const int EYE_HEIGHT = 20;
};