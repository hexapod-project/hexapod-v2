#include "MenuController.h"
#include "Constants.h"
#include <Arduino.h>

std::map<MenuScreen, String> MENU_LABELS = {
    {MENU_MAIN, "Main Menu"},
    {MENU_MOOD, "Change Mood"},
    {MENU_CALIBRATE, "Calibrate"},
    {MENU_SLEEP, "Sleep"},
    {MENU_OFF, "Power Off"},
    {MENU_EXIT, "Exit"},
    {MENU_BACK, "Back"},

    {MENU_MOOD_NEUTRAL, "Neutral"},
    {MENU_MOOD_HAPPY, "Happy"},
    {MENU_MOOD_SAD, "Sad"},
    {MENU_MOOD_ANGRY, "Angry"},
    {MENU_MOOD_TIRED, "Tired"},
    {MENU_MOOD_SLEEP, "Sleep"},

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

std::map<Joint, String> JOINT_LABELS = {
    {Joint::LEFT_FRONT_COXA, "Calibrate LF Coxa"},
    {Joint::LEFT_MID_COXA, "Calibrate LM Coxa"},
    {Joint::LEFT_BACK_COXA, "Calibrate LB Coxa"},
    {Joint::RIGHT_FRONT_COXA, "Calibrate RF Coxa"},
    {Joint::RIGHT_MID_COXA, "Calibrate RM Coxa"},
    {Joint::RIGHT_BACK_COXA, "Calibrate RB Coxa"},
    {Joint::LEFT_FRONT_FEMUR, "Calibrate LF Femur"},
    {Joint::LEFT_MID_FEMUR, "Calibrate LM Femur"},
    {Joint::LEFT_BACK_FEMUR, "Calibrate LB Femur"},
    {Joint::RIGHT_FRONT_FEMUR, "Calibrate RF Femur"},
    {Joint::RIGHT_MID_FEMUR, "Calibrate RM Femur"},
    {Joint::RIGHT_BACK_FEMUR, "Calibrate RB Femur"},
    {Joint::LEFT_FRONT_TIBIA, "Calibrate LF Tibia"},
    {Joint::LEFT_MID_TIBIA, "Calibrate LM Tibia"},
    {Joint::LEFT_BACK_TIBIA, "Calibrate LB Tibia"},
    {Joint::RIGHT_FRONT_TIBIA, "Calibrate RF Tibia"},
    {Joint::RIGHT_MID_TIBIA, "Calibrate RM Tibia"},
    {Joint::RIGHT_BACK_TIBIA, "Calibrate RB Tibia"},
};

const Joint CALIBRATE_JOINT_ORDERS[] = {
    Joint::RIGHT_FRONT_COXA,
    Joint::RIGHT_FRONT_FEMUR,
    Joint::RIGHT_FRONT_TIBIA,
    Joint::RIGHT_MID_COXA,
    Joint::RIGHT_MID_FEMUR,
    Joint::RIGHT_MID_TIBIA,
    Joint::RIGHT_BACK_COXA,
    Joint::RIGHT_BACK_FEMUR,
    Joint::RIGHT_BACK_TIBIA,
    Joint::LEFT_BACK_TIBIA,
    Joint::LEFT_BACK_FEMUR,
    Joint::LEFT_BACK_COXA,
    Joint::LEFT_MID_TIBIA,
    Joint::LEFT_MID_FEMUR,
    Joint::LEFT_MID_COXA,
    Joint::LEFT_FRONT_TIBIA,
    Joint::LEFT_FRONT_FEMUR,
    Joint::LEFT_FRONT_COXA,
};

void changeMood(FaceExpression expression)
{
    DisplayManager *displayManager = DisplayManager::getInstance();

    displayManager->changeMood(expression);
    displayManager->exitMenu();
}

void openCalibratorSelector(int jointIndex = 1)
{
    MenuController *menuController = MenuController::getInstance();
    DisplayManager *displayManager = DisplayManager::getInstance();

    menuController->setScreen(MENU_CALIBRATE);
    menuController->setCursorValue(jointIndex);

    if (jointIndex > 0)
    {
        Joint joint = CALIBRATE_JOINT_ORDERS[jointIndex - 1];
        displayManager->showCalibratorSelector(JOINT_LABELS[joint], joint);
    }
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

void onSleep()
{
    StateMachine *stateMachine = StateMachine::getInstance();
    DisplayManager *displayManager = DisplayManager::getInstance();
    
    stateMachine->sleep();
    displayManager->exitMenu();
}

void onTurnOff()
{
    MenuController *menuController = MenuController::getInstance();
    menuController->turnOff();
}

std::map<MenuScreen, std::vector<MenuOption>> MENU_OPTIONS = {
    {
        MenuScreen::MENU_MAIN,
        {
            MenuOption(MenuScreen::MENU_MOOD),
            MenuOption(MenuScreen::MENU_CALIBRATE, []()
                       { openCalibratorSelector(); }),
            MenuOption(MenuScreen::MENU_SLEEP, onSleep),
            MenuOption(MenuScreen::MENU_OFF, onTurnOff),
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
            MenuOption(MenuScreen::MENU_MOOD_SLEEP, []()
                       { changeMood(FaceExpression::FACE_SLEEP); }),
            MenuOption(MenuScreen::MENU_BACK, MenuScreen::MENU_MAIN),
        },
    },
    {
        MenuScreen::MENU_CALIBRATE,
        {// Left
         MenuOption(MenuScreen::MENU_BACK),
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

MenuController::MenuController(DisplayManager *displayManager, Calibrator *calibrator, StateMachine* stateMachine)
{
    if (this->instance == NULL)
    {
        this->instance = this;
    }

    this->displayManager = displayManager;
    this->calibrator = calibrator;
    this->stateMachine = stateMachine;
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
void MenuController::turnOff()
{
    displayManager->exitMenu();
    displayManager->getDisplay()->setCursor(HALF_SCREEN_WIDTH - 48, HALF_SCREEN_HEIGHT - TEXT_PIXELS_PER_UNIT/2);
    displayManager->getDisplay()->setTextColor(SH110X_WHITE);
    displayManager->getDisplay()->println("Shutting down...");
    displayManager->getDisplay()->display();

    Hexapod::getInstance()->rest();

    delay(1000);

    displayManager->clearDisplay();

    delay(300);
    
    esp_sleep_enable_ext0_wakeup((gpio_num_t)SW_PIN, 0);
    esp_deep_sleep_start();
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
    // Disable sleep if it was enabled
    if (stateMachine->getState() == State::STATE_SLEEP)
    {        
        stateMachine->idle();
        return;
    }

    std::vector<MenuOption> currSubMenus = MENU_OPTIONS[currMenuScreen];

    if (displayManager->currentDisplayMode == DisplayMode::HOME)
    {
        // Set to main menu as the first menu screen
        currMenuScreen = MenuScreen::MENU_MAIN;
    }
    else if (displayManager->currentDisplayMode == DisplayMode::CALIBRATOR_SETTER)
    {
        openCalibratorSelector((Joint)cursorValue);
        return;
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
            if (Hexapod::getInstance()->getMode() == HexapodMode::CALIBRATE)
            {
                Hexapod::getInstance()->switchMode(HexapodMode::CONTROLLER);
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

        if (displayManager->currentDisplayMode == DisplayMode::CALIBRATOR_SELECTOR)
        {
            if (cursorValue > 18)
            {
                cursorValue = 0;
            }
        }
    }
    else
    {
        if (cursorValue > 0)
        {
            cursorValue--;
        }
        else if (displayManager->currentDisplayMode == DisplayMode::CALIBRATOR_SELECTOR)
        {
            cursorValue = 18;
        }
    }

    switch (displayManager->currentDisplayMode)
    {
    case DisplayMode::CALIBRATOR_SELECTOR:
        if (cursorValue > 0)
        {
            Joint joint = CALIBRATE_JOINT_ORDERS[cursorValue - 1];
            displayManager->showCalibratorSelector(JOINT_LABELS[joint], joint);
        }
        else
        {
            displayManager->showCalibratorSelector("Back to Menu", 0);
        }
        break;
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