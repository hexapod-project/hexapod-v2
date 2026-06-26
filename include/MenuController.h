#pragma once

#include "DisplayManager.h"
#include "Calibrator.h"

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
    MENU_MOOD_SLEEP,

    // Calibrate sub-menus
    MENU_CALIBRATE_LF_COXA,
    MENU_CALIBRATE_LM_COXA,
    MENU_CALIBRATE_LB_COXA,
    MENU_CALIBRATE_RF_COXA,
    MENU_CALIBRATE_RM_COXA,
    MENU_CALIBRATE_RB_COXA,

    MENU_CALIBRATE_LF_FEMUR,
    MENU_CALIBRATE_LM_FEMUR,
    MENU_CALIBRATE_LB_FEMUR,
    MENU_CALIBRATE_RF_FEMUR,
    MENU_CALIBRATE_RM_FEMUR,
    MENU_CALIBRATE_RB_FEMUR,

    MENU_CALIBRATE_LF_TIBIA,
    MENU_CALIBRATE_LM_TIBIA,
    MENU_CALIBRATE_LB_TIBIA,
    MENU_CALIBRATE_RF_TIBIA,
    MENU_CALIBRATE_RM_TIBIA,
    MENU_CALIBRATE_RB_TIBIA,
};

class MenuOption
{
public:
    MenuScreen screen;
    MenuScreen prevScreen = MenuScreen::MENU_MAIN;

    std::function<void()> onPress;

    MenuOption();

    MenuOption(MenuScreen _screen, MenuScreen _prevScreen) : screen(_screen), prevScreen(_prevScreen) {}

    MenuOption(MenuScreen _screen) : screen(_screen) {}
    MenuOption(MenuScreen _screen, std::function<void()> _onPress) : screen(_screen), onPress(_onPress) {}
};

class MenuController
{
private:
    static MenuController *instance;
    DisplayManager *displayManager;
    Calibrator *calibrator;
    ulong swDebouncedCooldown = 0;

    std::vector<String> subMenuLabels = {};
    MenuScreen currMenuScreen = MenuScreen::MENU_EXIT;
    unsigned int cursorValue = 0;
    int clkState = 0;
    int dtState = 0;
    ulong sleepStart = 0;
    bool isSleep = false;

    Joint selectedJoint;

    void onKnobPress();
    void onKnobTurn(bool clockwise);

public:
    MenuController(DisplayManager *displayManager, Calibrator *calibrator);
    static MenuController *getInstance();
    void init();
    void reset();
    int getMenuIndex();
    void loop();
    void setScreen(MenuScreen screen);
    void setCursorValue(int value);
    void setSelectedJoint(Joint joint);
    void sleep();
};