#include "DisplayManager.h"
#include "Utils.h"
#include <Adafruit_GFX.h>
#include <Wire.h>
#include "Animations/IdleAnim.h"
#include "Animations/HappyAnim.h"
#include "Animations/AngryAnim.h"
#include "Animations/SleepAnim.h"

DisplayManager *DisplayManager::instance = NULL;

DisplayManager::DisplayManager()
{
    this->instance = this;
}

DisplayManager *DisplayManager::getInstance()
{
    return instance;
}

void DisplayManager::init()
{
    this->display->begin(OLED_I2C_ADDRESS);
    this->display->clearDisplay();
    this->faceAnimator = new FaceAnimator(this->display);
}

void DisplayManager::runAnim(int16_t screen_w, int16_t screen_h, int16_t screen_x_offset, int16_t screen_y_offset, const unsigned char *frames[], int frameCount, uint16_t color, uint8_t fps, uint16_t maxDelay)
{
    if (frameCount == 1)
    {
        this->display->clearDisplay();
        this->display->drawBitmap(screen_x_offset, screen_y_offset, frames[0], screen_w, screen_h, SH110X_WHITE, SH110X_BLACK);
        this->display->display();
    }

    int frameIndex = 0;
    int delayTime = pdMS_TO_TICKS(1000 / fps); // Calculate delay time in milliseconds based on FPS
    while (true)
    {
        this->display->clearDisplay();
        this->display->drawBitmap(screen_x_offset, screen_y_offset, frames[frameIndex], screen_w, screen_h, color);
        this->display->display();
        frameIndex = (frameIndex + 1) % frameCount;

        if (frameIndex == 0)
        {
            int randomDelay = random(0, maxDelay);
            vTaskDelay(pdMS_TO_TICKS(randomDelay));
        }
        else
        {
            vTaskDelay(delayTime); // Delay for the specified FPS
        }
    }
}

void DisplayManager::stopLoading()
{
    if (loadingTaskHandle != NULL)
    {
        vTaskDelete(loadingTaskHandle);
        loadingTaskHandle = NULL;
        currentDisplayMode = DisplayMode::NONE;
    }
}

void DisplayManager::startLoading()
{
    if (currentDisplayMode == DisplayMode::LOADING)
    {
        return; // Already displaying loading animation
    }

    xTaskCreatePinnedToCore(
        [](void *param)
        {
            DisplayManager *displayManager = static_cast<DisplayManager *>(param);
            int quarter = 0;
            while (true)
            {
                displayManager->display->clearDisplay();
                for (int i = 0; i < 4; i++)
                {
                    if (i != quarter)
                    {
                        displayManager->display->drawCircleHelper(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + SCREEN_Y_OFFSET, 10, 1 << i, SH110X_WHITE);
                    }
                }
                displayManager->display->display();
                quarter = (quarter + 1) % 4;
                vTaskDelay(pdMS_TO_TICKS(50));
            }
        },
        "LoadingAnimationTask",
        2048,
        this,
        1,
        &loadingTaskHandle,
        1);

    currentDisplayMode = DisplayMode::LOADING;
}

void DisplayManager::displayMenu()
{
    if (currentDisplayMode == DisplayMode::SETTINGS_MENU)
    {
        return; // Already displaying menu
    }

    this->display->clearDisplay();
    this->display->setTextSize(1);
    this->display->setTextColor(SH110X_WHITE);
    this->display->setCursor(0, 0);
    this->display->println("Menu");
    this->display->display();

    currentDisplayMode = DisplayMode::SETTINGS_MENU;
}