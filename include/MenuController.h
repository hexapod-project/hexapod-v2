#pragma once

#include "DisplayManager.h"

#define CLK_PIN 25 // ESP32 pin GPIO25 connected to the rotary encoder's CLK pin
#define DT_PIN 26  // ESP32 pin GPIO26 connected to the rotary encoder's DT pin
#define SW_PIN 27  // ESP32 pin GPIO27 connected to the rotary encoder's SW pin

enum MenuScreen
{
    MENU_MAIN,
    MENU_MOOD,
    MENU_CALIBRATE,
    MENU_SLEEP,
    MENU_EXIT,
    MENU_BACK,

    // Mood sub-menus
    MENU_MOOD_NEUTRAL,
    MENU_MOOD_HAPPY,
    MENU_MOOD_SAD,
    MENU_MOOD_ANGRY,
    MENU_MOOD_TIRED,

    // Calibrate sub-menus
    MENU_CALIBRATE_LF,
    MENU_CALIBRATE_LM,
    MENU_CALIBRATE_LB,
    MENU_CALIBRATE_RF,
    MENU_CALIBRATE_RM,
    MENU_CALIBRATE_RB,
};

class MenuOption
{
public:
    MenuScreen screen;
    MenuScreen prevScreen = MenuScreen::MENU_MAIN;

    std::function<void()> onPress;

    MenuOption();

    MenuOption(MenuScreen _screen, MenuScreen _prevScreen): screen(_screen), prevScreen(_prevScreen) {}    

    MenuOption(MenuScreen _screen): screen(_screen) {}    
    MenuOption(MenuScreen _screen, std::function<void()> _onPress): screen(_screen), onPress(_onPress) {}    
};

class MenuController
{
private:
    static MenuController *instance;
    DisplayManager *displayManager;
    ulong swDebouncedCooldown = 0;

    std::vector<String> subMenuLabels = {};
    MenuScreen currMenuScreen = MenuScreen::MENU_EXIT;
    unsigned int submenuCursor = 0;
    int clkState = 0;
    int dtState = 0;

    void onKnobPress();
    void onKnobTurn(bool clockwise);

public:
    MenuController(DisplayManager *displayManager);
    void init();
    void reset();
    int getMenuIndex();
    void loop();
};