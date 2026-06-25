#include "MenuController.h"
#include "Constants.h"
#include <Arduino.h>

std::map<MenuScreen, String> MENU_LABELS = {
    {MENU_MAIN, "Main"},
    {MENU_MOOD, "Change Mood"},
    {MENU_CALIBRATE, "Calibrate"},
    {MENU_SLEEP, "Sleep"},
    {MENU_EXIT, "Exit"},
    {MENU_BACK, "Back"},

    {MENU_MOOD_NEUTRAL, "Neutral"},
    {MENU_MOOD_HAPPY, "Happy"},
    {MENU_MOOD_SAD, "Sad"},
    {MENU_MOOD_ANGRY, "Angry"},
    {MENU_MOOD_TIRED, "Tired"},

    {MENU_CALIBRATE_LF_COXA, "Left Front Coxa"},
    {MENU_CALIBRATE_LM_COXA, "Left Mid Coxa"},
    {MENU_CALIBRATE_LB_COXA, "Left Back Coxa"},
    {MENU_CALIBRATE_RF_COXA, "Right Front Coxa"},
    {MENU_CALIBRATE_RM_COXA, "Right Mid Coxa"},
    {MENU_CALIBRATE_RB_COXA, "Right Back Coxa"},

    {MENU_CALIBRATE_LF_FEMUR, "Left Front Femur"},
    {MENU_CALIBRATE_LM_FEMUR, "Left Mid Femur"},
    {MENU_CALIBRATE_LB_FEMUR, "Left Back Femur"},
    {MENU_CALIBRATE_RF_FEMUR, "Right Front Femur"},
    {MENU_CALIBRATE_RM_FEMUR, "Right Mid Femur"},
    {MENU_CALIBRATE_RB_FEMUR, "Right Back Femur"},

    {MENU_CALIBRATE_LF_TIBIA, "Left Front Tibia"},
    {MENU_CALIBRATE_LM_TIBIA, "Left Mid Tibia"},
    {MENU_CALIBRATE_LB_TIBIA, "Left Back Tibia"},
    {MENU_CALIBRATE_RF_TIBIA, "Right Front Tibia"},
    {MENU_CALIBRATE_RM_TIBIA, "Right Mid Tibia"},
    {MENU_CALIBRATE_RB_TIBIA, "Right Back Tibia"},
};

void changeMood(FaceExpression expression)
{
    DisplayManager *displayManager = DisplayManager::getInstance();
    displayManager->changeMood(expression);
    displayManager->exitMenu();
}

void openCalibratorSetter(MenuScreen screen, Joint joint)
{
    MenuController *menuController = MenuController::getInstance();
    DisplayManager *displayManager = DisplayManager::getInstance();
    Calibrator *calibrator = Calibrator::getInstance();
    Hexapod *hexapod = Hexapod::getInstance();

    hexapod->switchMode(HexapodMode::CALIBRATE);
    menuController->setScreen(screen);
    uint16_t pwm = calibrator->getPWMPulse(joint - 1);
    menuController->setSelectedJoint(joint);
    menuController->setCursorValue(pwm);
    displayManager->showCalibratorSetter(MENU_LABELS[screen], pwm);
}

std::map<MenuScreen, std::vector<MenuOption>> MENU_OPTIONS = {
    {
        MenuScreen::MENU_MAIN,
        {
            MenuOption(MenuScreen::MENU_MOOD),
            MenuOption(MenuScreen::MENU_CALIBRATE),
            MenuOption(MenuScreen::MENU_SLEEP, []()
                       { changeMood(FaceExpression::FACE_SLEEP); }),
            MenuOption(MenuScreen::MENU_EXIT),
        },
    },
    {
        MenuScreen::MENU_MOOD,
        {
            MenuOption(MenuScreen::MENU_MOOD_NEUTRAL, []()
                       { changeMood(FaceExpression::FACE_NEUTRAL); }),
            MenuOption(MenuScreen::MENU_MOOD_HAPPY, []()
                       { changeMood(FaceExpression::FACE_HAPPY); }),
            MenuOption(MenuScreen::MENU_MOOD_SAD, []()
                       { changeMood(FaceExpression::FACE_SAD); }),
            MenuOption(MenuScreen::MENU_MOOD_ANGRY, []()
                       { changeMood(FaceExpression::FACE_ANGRY); }),
            MenuOption(MenuScreen::MENU_MOOD_TIRED, []()
                       { changeMood(FaceExpression::FACE_TIRED); }),
            MenuOption(MenuScreen::MENU_BACK, MenuScreen::MENU_MAIN),
        },
    },
    {
        MenuScreen::MENU_CALIBRATE,
        {// Left
         MenuOption(MenuScreen::MENU_CALIBRATE_LF_COXA, []()
                    { openCalibratorSetter(MenuScreen::MENU_CALIBRATE_LF_COXA, Joint::LEFT_FRONT_COXA); }),
         MenuOption(MenuScreen::MENU_CALIBRATE_LF_FEMUR, []()
                    { openCalibratorSetter(MenuScreen::MENU_CALIBRATE_LF_FEMUR, Joint::LEFT_FRONT_FEMUR); }),
         MenuOption(MenuScreen::MENU_CALIBRATE_LF_TIBIA, []()
                    { openCalibratorSetter(MenuScreen::MENU_CALIBRATE_LF_TIBIA, Joint::LEFT_FRONT_TIBIA); }),

         MenuOption(MenuScreen::MENU_CALIBRATE_LM_COXA, []()
                    { openCalibratorSetter(MenuScreen::MENU_CALIBRATE_LM_COXA, Joint::LEFT_MID_COXA); }),
         MenuOption(MenuScreen::MENU_CALIBRATE_LM_FEMUR, []()
                    { openCalibratorSetter(MenuScreen::MENU_CALIBRATE_LM_FEMUR, Joint::LEFT_MID_FEMUR); }),
         MenuOption(MenuScreen::MENU_CALIBRATE_LM_TIBIA, []()
                    { openCalibratorSetter(MenuScreen::MENU_CALIBRATE_LM_TIBIA, Joint::LEFT_MID_TIBIA); }),

         MenuOption(MenuScreen::MENU_CALIBRATE_LB_COXA, []()
                    { openCalibratorSetter(MenuScreen::MENU_CALIBRATE_LB_COXA, Joint::LEFT_BACK_COXA); }),
         MenuOption(MenuScreen::MENU_CALIBRATE_LB_FEMUR, []()
                    { openCalibratorSetter(MenuScreen::MENU_CALIBRATE_LB_FEMUR, Joint::LEFT_BACK_FEMUR); }),
         MenuOption(MenuScreen::MENU_CALIBRATE_LB_TIBIA, []()
                    { openCalibratorSetter(MenuScreen::MENU_CALIBRATE_LB_TIBIA, Joint::LEFT_BACK_TIBIA); }),

         // Right
         MenuOption(MenuScreen::MENU_CALIBRATE_RF_COXA, []()
                    { openCalibratorSetter(MenuScreen::MENU_CALIBRATE_RF_COXA, Joint::RIGHT_FRONT_COXA); }),
         MenuOption(MenuScreen::MENU_CALIBRATE_RF_FEMUR, []()
                    { openCalibratorSetter(MenuScreen::MENU_CALIBRATE_RF_FEMUR, Joint::RIGHT_FRONT_FEMUR); }),
         MenuOption(MenuScreen::MENU_CALIBRATE_RF_TIBIA, []()
                    { openCalibratorSetter(MenuScreen::MENU_CALIBRATE_RF_TIBIA, Joint::RIGHT_FRONT_TIBIA); }),

         MenuOption(MenuScreen::MENU_CALIBRATE_RM_COXA, []()
                    { openCalibratorSetter(MenuScreen::MENU_CALIBRATE_RM_COXA, Joint::RIGHT_MID_COXA); }),
         MenuOption(MenuScreen::MENU_CALIBRATE_RM_FEMUR, []()
                    { openCalibratorSetter(MenuScreen::MENU_CALIBRATE_RM_FEMUR, Joint::RIGHT_MID_FEMUR); }),
         MenuOption(MenuScreen::MENU_CALIBRATE_RM_TIBIA, []()
                    { openCalibratorSetter(MenuScreen::MENU_CALIBRATE_RM_TIBIA, Joint::RIGHT_MID_TIBIA); }),

         MenuOption(MenuScreen::MENU_CALIBRATE_RB_COXA, []()
                    { openCalibratorSetter(MenuScreen::MENU_CALIBRATE_RB_COXA, Joint::RIGHT_BACK_COXA); }),
         MenuOption(MenuScreen::MENU_CALIBRATE_RB_FEMUR, []()
                    { openCalibratorSetter(MenuScreen::MENU_CALIBRATE_RB_FEMUR, Joint::RIGHT_BACK_FEMUR); }),
         MenuOption(MenuScreen::MENU_CALIBRATE_RB_TIBIA, []()
                    { openCalibratorSetter(MenuScreen::MENU_CALIBRATE_RB_TIBIA, Joint::RIGHT_BACK_TIBIA); }),
         MenuOption(MenuScreen::MENU_BACK)},
    },
};

MenuController *MenuController::instance = NULL;

MenuController::MenuController(DisplayManager *displayManager, Calibrator *calibrator)
{
    if (this->instance == NULL)
    {
        this->instance = this;
    }

    this->displayManager = displayManager;
    this->calibrator = calibrator;
}

MenuController *MenuController::getInstance()
{
    return MenuController::instance;
};

void MenuController::init()
{
    pinMode(CLK_PIN, INPUT);
    pinMode(DT_PIN, INPUT);
    pinMode(SW_PIN, INPUT_PULLUP);
}

void MenuController::reset()
{
    cursorValue = 0;
}

void MenuController::setCursorValue(int value)
{
    cursorValue = value;
}

void MenuController::setSelectedJoint(Joint joint)
{
    selectedJoint = joint;
}

int MenuController::getMenuIndex()
{
    return cursorValue;
}

void MenuController::onKnobPress()
{
    std::vector<MenuOption> currSubMenus = MENU_OPTIONS[currMenuScreen];

    if (displayManager->currentDisplayMode == DisplayMode::HOME)
    {
        // Set to main menu as the first menu screen
        currMenuScreen = MenuScreen::MENU_MAIN;
    }
    else if (displayManager->currentDisplayMode == DisplayMode::CALIBRATOR_SETTER)
    {
        currMenuScreen = MenuScreen::MENU_CALIBRATE;
    }
    else
    {
        MenuOption selectedSubMenu = currSubMenus[cursorValue];
        if (selectedSubMenu.onPress != NULL)
        {
            selectedSubMenu.onPress();
            return;
        }
        else if (selectedSubMenu.screen == MenuScreen::MENU_EXIT)
        {
            displayManager->exitMenu();
            return;
        }
        else if (selectedSubMenu.screen == MenuScreen::MENU_BACK)
        {
            if (currMenuScreen == MenuScreen::MENU_CALIBRATE)
            {
                if (Hexapod::getInstance()->getMode() == HexapodMode::CALIBRATE)
                {
                    Hexapod::getInstance()->switchMode(HexapodMode::CONTROLLER);
                }
            }

            // Go back to the prev screen
            currMenuScreen = currSubMenus[cursorValue].prevScreen;
        }
        else
        {
            // Get new menu screen
            currMenuScreen = selectedSubMenu.screen;
        }
    }

    cursorValue = 0;
    currSubMenus = MENU_OPTIONS[currMenuScreen];
    subMenuLabels.clear();
    int subMenusSize = currSubMenus.size();
    short subMenuIndex = 0;

    for (subMenuIndex = 0; subMenuIndex < subMenusSize; subMenuIndex++)
    {
        subMenuLabels.push_back(MENU_LABELS[currSubMenus.at(subMenuIndex).screen]);
    }

    this->displayManager->showMenu(MENU_LABELS[currMenuScreen], subMenuLabels, cursorValue);
}

void MenuController::onKnobTurn(bool clockwise)
{
    if (displayManager->currentDisplayMode == DisplayMode::HOME || displayManager->currentDisplayMode == DisplayMode::LOADING)
    {
        return;
    }

    if (clockwise)
    {
        cursorValue++;
    }
    else
    {
        if (cursorValue > 0)
        {
            cursorValue--;
        }
    }

    switch (displayManager->currentDisplayMode)
    {
    case DisplayMode::CALIBRATOR_SETTER:
        cursorValue = min(max(cursorValue, (unsigned int)MIN_PWM), (unsigned int)MAX_PWM);
        calibrator->setPWMPulse(selectedJoint - 1, cursorValue);
        displayManager->showCalibratorSetter(MENU_LABELS[currMenuScreen], cursorValue);
        break;
    case DisplayMode::MENU:
    default:
        cursorValue = min(cursorValue, subMenuLabels.size() - 1);
        displayManager->showMenu(MENU_LABELS[currMenuScreen], subMenuLabels, cursorValue);
        break;
    }
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

void MenuController::setScreen(MenuScreen screen)
{
    currMenuScreen = screen;
}