#pragma once

#include <Wire.h>
#include "Configuration.h"
#include "FaceAnimator.h"
#include <Adafruit_SH110X.h>

#define TEXT_PIXELS_PER_UNIT 8

class DisplayManager
{
private:
    static DisplayManager *instance;
    Adafruit_SH1106G *display = new Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
    TaskHandle_t loadingTaskHandle, animTaskHandle;
    
    int currCursorValue = 0;
    ulong startTime = 0;
    String currTitle = "";
    bool flipFlop = false;

    void startAnim(int16_t screen_w, int16_t screen_h, int16_t screen_x_offset, int16_t screen_y_offset, const unsigned char *frames[], int frameCount, uint16_t color = SH110X_WHITE, uint8_t fps = 25, uint16_t maxDelay = 0);
    void runAnimTask(int16_t screen_w, int16_t screen_h, int16_t screen_x_offset, int16_t screen_y_offset, const unsigned char *frames[], int frameCount, uint16_t color = SH110X_WHITE, uint8_t fps = 25, uint16_t maxDelay = 0);
    void stopAnim();
    void writeMenuTitle(String title);

public:
    DisplayMode currentDisplayMode = DisplayMode::HOME;
    FaceAnimator *faceAnimator;

    DisplayManager();
    static DisplayManager *getInstance();
    void loop();
    void init();
    void startLoading();
    void stopLoading();
    void showMenu(String title, std::vector<String> options, int submenuCursor);
    void exitMenu();
    void showIdle();
    void changeMood(FaceExpression expression);
    void showCalibratorSelector(String title, int cursor, bool blink = false);
    void showCalibratorSetter(String title, int pwm);
    void clearDisplay();
    Adafruit_SH1106G *getDisplay();
};