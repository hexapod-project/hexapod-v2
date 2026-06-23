#include <Adafruit_SH110X.h>
#include "Vec2.h"

#define EYE_WIDTH 30.0
#define EYE_HEIGHT 30.0
#define CLOSED_EYE_HEIGHT 3.0
#define EYE_RADIUS 10
#define EYE_GAP 15
#define EYE_LID_HEIGHT EYE_HEIGHT * 0.5
#define SLEEP_Z_OFFSET_X 5
#define SLEEP_Z_OFFSET_Y 15

#define FPS 25
#define MAX_BLINK_INTERVAL_S 10
#define MIN_POS_CHANGE_INTERVAL_S 5
#define MAX_POS_CHANGE_INTERVAL_S 30
#define MAX_X_OFFSET 20.0
#define MAX_Y_OFFSET 10.0

#define TWEEN_MULTIPLIER 0.5
#define SLEEP_TWEEN_MULTIPLIER 0.2
#define TEXT_SIZE 1
#define DEBUG_FACE false

enum FaceExpression
{
    FACE_NEUTRAL,
    FACE_HAPPY,
    FACE_SAD,
    FACE_ANGRY,
    FACE_TIRED,
    FACE_SLEEP
};

enum FaceState
{
    FACE_NONE,    
    FACE_IDLE,
    FACE_STILL
};

class FaceAnimator
{
private:
    static FaceAnimator *instance;
    static const int taskDelay = pdMS_TO_TICKS(1000 / FPS);
    Adafruit_SH1106G *display;

    FaceState currentState = FaceState::FACE_NONE;
    FaceExpression currentExpression = FaceExpression::FACE_NEUTRAL;

    ulong nextBlinkMS = 0;
    ulong expressionStartMS = 0;
    ulong nextPosChangeMS = millis() + MIN_POS_CHANGE_INTERVAL_S * 1000;
    double currEyeHeight = EYE_HEIGHT;
    float nextEyeHeight = EYE_HEIGHT;
    Vec2 currEyeOffset = Vec2(0, 0);
    Vec2 nextEyeOffset = Vec2(0, 0);
    float tweenMultiplier = TWEEN_MULTIPLIER;
    bool isHidden = false;

    void drawFace();
    
    public:
    FaceAnimator(Adafruit_SH1106G *display);
    void loop();
    void setExpression(FaceExpression expression);
    void setState(FaceState state);
    void hide();
    void show();
};