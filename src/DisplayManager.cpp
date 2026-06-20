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

void DisplayManager::clearFaceAnimationTask()
{
    if (faceAnimationTaskHandle != NULL)
    {
        vTaskDelete(faceAnimationTaskHandle);
        faceAnimationTaskHandle = NULL;
        currentDisplayMode = DisplayMode::NONE;
    }
}

void DisplayManager::displayLoadingAnim()
{
    if (currentDisplayMode == DisplayMode::LOADING)
    {
        return; // Already displaying loading animation
    }

    clearFaceAnimationTask();
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
        &faceAnimationTaskHandle,
        1);

    currentDisplayMode = DisplayMode::LOADING;
}

void DisplayManager::displayIdleAnim()
{
    if (currentDisplayMode == DisplayMode::IDLE_FACE)
    {
        return; // Already displaying idle animation
    }

    clearFaceAnimationTask();
    xTaskCreatePinnedToCore(
        [](void *param)
        {
            DisplayManager *displayManager = static_cast<DisplayManager *>(param);
            displayManager->runAnim(SCREEN_WIDTH, SCREEN_HEIGHT, 0, SCREEN_Y_OFFSET, idle, IDLE_FRAMES, SH110X_WHITE, 25, MAX_IDLE_DELAY);
        },
        "IdleAnimationTask",
        2048,
        this,
        1,
        &faceAnimationTaskHandle,
        1);
    currentDisplayMode = DisplayMode::IDLE_FACE;
}

void DisplayManager::displayHappyAnim()
{
    if (currentDisplayMode == DisplayMode::HAPPY)
    {
        return; // Already displaying happy animation
    }

    clearFaceAnimationTask();
    xTaskCreatePinnedToCore(
        [](void *param)
        {
            DisplayManager *displayManager = static_cast<DisplayManager *>(param);
            displayManager->runAnim(SCREEN_WIDTH, SCREEN_HEIGHT, 0, SCREEN_Y_OFFSET, happy, HAPPY_FRAMES);
        },
        "HappyAnimationTask",
        2048,
        this,
        1,
        &faceAnimationTaskHandle,
        1);
    currentDisplayMode = DisplayMode::HAPPY;
}

void DisplayManager::displaySadAnim()
{
    if (currentDisplayMode == DisplayMode::SAD)
    {
        return; // Already displaying sad animation
    }

    clearFaceAnimationTask();
    xTaskCreatePinnedToCore(
        [](void *param)
        {
            DisplayManager *displayManager = static_cast<DisplayManager *>(param);
            // TODO: Implement sad animation frames and call runAnim with sad frames
            displayManager->runAnim(SCREEN_WIDTH, SCREEN_HEIGHT, 0, SCREEN_Y_OFFSET, angry, ANGRY_FRAMES);
        },
        "SadAnimationTask",
        2048,
        this,
        1,
        &faceAnimationTaskHandle,
        1);
    currentDisplayMode = DisplayMode::SAD;
}

void DisplayManager::displayAngryAnim()
{
    if (currentDisplayMode == DisplayMode::ANGRY)
    {
        return; // Already displaying angry animation
    }

    clearFaceAnimationTask();
    xTaskCreatePinnedToCore(
        [](void *param)
        {
            DisplayManager *displayManager = static_cast<DisplayManager *>(param);
            displayManager->runAnim(SCREEN_WIDTH, SCREEN_HEIGHT, 0, SCREEN_Y_OFFSET, angry, ANGRY_FRAMES);
        },
        "AngryAnimationTask",
        2048,
        this,
        1,
        &faceAnimationTaskHandle,
        1);

    currentDisplayMode = DisplayMode::ANGRY;
}

void DisplayManager::displaySleepAnim()
{
    if (currentDisplayMode == DisplayMode::SLEEP)
    {
        return; // Already displaying sleep animation
    }

    clearFaceAnimationTask();
    xTaskCreatePinnedToCore(
        [](void *param)
        {
            DisplayManager *displayManager = static_cast<DisplayManager *>(param);
            displayManager->runAnim(SCREEN_WIDTH, SCREEN_HEIGHT, 0, SCREEN_Y_OFFSET, sleepAnim, SLEEP_FRAMES);
        },
        "SleepAnimationTask",
        2048,
        this,
        1,
        &faceAnimationTaskHandle,
        1);

    currentDisplayMode = DisplayMode::SLEEP;
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