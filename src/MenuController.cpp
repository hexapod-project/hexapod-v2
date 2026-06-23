#include "MenuController.h"
#include <Arduino.h>

std::map<MenuScreen, String> MENU_LABELS = {
    {MENU_MAIN, "Main"},
    {MENU_MOOD, "Change Mood"},
    {MENU_CALIBRATE, "Calibrate"},
    {MENU_EXIT, "Exit"},
    {MENU_BACK, "Back"},

    {MENU_MOOD_NEUTRAL, "Neutral"},
    {MENU_MOOD_HAPPY, "Happy"},
    {MENU_MOOD_SAD, "Sad"},
    {MENU_MOOD_ANGRY, "Angry"},
    {MENU_MOOD_TIRED, "Tired"},

    {MENU_CALIBRATE_LF, "Left Front"},
    {MENU_CALIBRATE_LM, "Left Mid"},
    {MENU_CALIBRATE_LB, "Left Back"},
    {MENU_CALIBRATE_RF, "Right Front"},
    {MENU_CALIBRATE_RM, "Right Mid"},
    {MENU_CALIBRATE_RB, "Right Back"},
};

std::map<MenuScreen, std::vector<MenuOption>> MENU_OPTIONS = {
    {MenuScreen::MENU_MAIN, {
                                MenuOption(MenuScreen::MENU_MOOD),
                                MenuOption(MenuScreen::MENU_CALIBRATE),
                                MenuOption(MenuScreen::MENU_EXIT),
                            }},
    {MenuScreen::MENU_MOOD, {
                                MenuOption(MenuScreen::MENU_MOOD_NEUTRAL),
                                MenuOption(MenuScreen::MENU_MOOD_HAPPY),
                                MenuOption(MenuScreen::MENU_MOOD_SAD),
                                MenuOption(MenuScreen::MENU_MOOD_ANGRY),
                                MenuOption(MenuScreen::MENU_MOOD_TIRED),
                                MenuOption(MenuScreen::MENU_BACK, MenuScreen::MENU_MAIN),
                            }},
    {MenuScreen::MENU_CALIBRATE, {
                                     MenuOption(MenuScreen::MENU_CALIBRATE_LF),
                                     MenuOption(MenuScreen::MENU_CALIBRATE_LM),
                                     MenuOption(MenuScreen::MENU_CALIBRATE_LB),
                                     MenuOption(MenuScreen::MENU_CALIBRATE_RF),
                                     MenuOption(MenuScreen::MENU_CALIBRATE_RM),
                                     MenuOption(MenuScreen::MENU_CALIBRATE_RB),
                                     MenuOption(MenuScreen::MENU_BACK, MenuScreen::MENU_MAIN),
                                 }},
};

MenuController *MenuController::instance = NULL;

MenuController::MenuController(DisplayManager *displayManager)
{
    if (this->instance == NULL)
    {
        this->instance = this;
    }

    this->displayManager = displayManager;
}

void MenuController::init()
{
    pinMode(CLK_PIN, INPUT);
    pinMode(DT_PIN, INPUT);
    pinMode(SW_PIN, INPUT_PULLUP);
}

void MenuController::reset()
{
    submenuCursor = 0;
}

int MenuController::getMenuIndex()
{
    return submenuCursor;
}

void MenuController::onKnobPress()
{
    std::vector<MenuOption> currSubMenus = MENU_OPTIONS[currMenuScreen];

    if (displayManager->currentDisplayMode != DisplayMode::MENU)
    {
        // Set to main menu as the first menu screen
        currMenuScreen = MenuScreen::MENU_MAIN;
    }
    else
    {
        MenuOption selectedSubMenu = currSubMenus[submenuCursor];
        if (selectedSubMenu.screen == MenuScreen::MENU_EXIT)
        {
            displayManager->exitMenu();
            return;
        }
        else if (selectedSubMenu.screen == MenuScreen::MENU_BACK)
        {
            // Go back to the prev screen
            currMenuScreen = currSubMenus[submenuCursor].prevScreen;
        }
        else
        {
            // Get new menu screen
            currMenuScreen = selectedSubMenu.screen;
        }
    }
    
    submenuCursor = 0;
    currSubMenus = MENU_OPTIONS[currMenuScreen];
    subMenuLabels.clear();
    int subMenusSize = currSubMenus.size();
    short subMenuIndex = 0;

    for (subMenuIndex = 0; subMenuIndex < subMenusSize; subMenuIndex++)
    {
        subMenuLabels.push_back(MENU_LABELS[currSubMenus.at(subMenuIndex).screen]);
    }

    this->displayManager->showMenu(MENU_LABELS[currMenuScreen], subMenuLabels, submenuCursor);
}

void MenuController::onKnobTurn(bool clockwise)
{
    if (displayManager->currentDisplayMode != DisplayMode::MENU)
    {
        return;
    }

    if (clockwise)
    {
        if (submenuCursor < subMenuLabels.size() - 1)
        {
            submenuCursor++;
        }
    }
    else
    {
        if (submenuCursor > 0)
        {
            submenuCursor--;
        }
    }

    this->displayManager->showMenu(MENU_LABELS[currMenuScreen], subMenuLabels, submenuCursor);
}

void MenuController::loop()
{
    dtState = digitalRead(DT_PIN);
    int newCLKState = digitalRead(CLK_PIN);

    if (newCLKState != clkState)
    {
        clkState = newCLKState;
        onKnobTurn(clkState != dtState);
    }

    if (millis() - swDebouncedCooldown > 500)
    {
        int swState = digitalRead(SW_PIN);
        if (swState == 0)
        {
            onKnobPress();
            swDebouncedCooldown = millis();
        }
    }
}