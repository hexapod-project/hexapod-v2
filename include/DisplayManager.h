#include <Wire.h>
#include "Configuration.h"
#include "FaceAnimator.h"
#include <Adafruit_SH110X.h>

enum DisplayMode
{
    NONE,
    LOADING,
    IDLE_FACE,
    HAPPY,
    SAD,
    ANGRY,
    SLEEP,
    SETTINGS_MENU
};

class DisplayManager
{
private:
    static DisplayManager *instance;
    Adafruit_SH1106G *display = new Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
    FaceAnimator *faceAnimator;
    TaskHandle_t faceAnimationTaskHandle;
    DisplayMode currentDisplayMode = DisplayMode::NONE;

    void clearFaceAnimationTask();
    void loop();
    void runAnim(int16_t screen_w, int16_t screen_h, int16_t screen_x_offset, int16_t screen_y_offset, const unsigned char *frames[], int frameCount, uint16_t color = SH110X_WHITE, uint8_t fps = 25, uint16_t maxDelay = 0);

public:

    DisplayManager();
    static DisplayManager *getInstance();
    void init();
    void displayLoadingAnim();
    void displayIdleAnim();
    void displayHappyAnim();
    void displaySadAnim();
    void displayAngryAnim();
    void displaySleepAnim();
    void displayMenu();
};