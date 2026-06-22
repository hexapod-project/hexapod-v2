#include <Wire.h>
#include "Configuration.h"
#include "FaceAnimator.h"
#include <Adafruit_SH110X.h>

enum DisplayMode
{
    NONE,
    LOADING,
    SETTINGS_MENU
};

class DisplayManager
{
private:
    static DisplayManager *instance;
    Adafruit_SH1106G *display = new Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
    TaskHandle_t loadingTaskHandle;
    DisplayMode currentDisplayMode = DisplayMode::NONE;

    void loop();
    void runAnim(int16_t screen_w, int16_t screen_h, int16_t screen_x_offset, int16_t screen_y_offset, const unsigned char *frames[], int frameCount, uint16_t color = SH110X_WHITE, uint8_t fps = 25, uint16_t maxDelay = 0);

public:
    FaceAnimator *faceAnimator;

    DisplayManager();
    static DisplayManager *getInstance();
    void init();
    void startLoading();
    void stopLoading();    
    void displayMenu();
};