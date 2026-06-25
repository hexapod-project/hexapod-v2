#include "DisplayManager.h"
#include "Utils.h"
#include <Adafruit_GFX.h>
#include <Wire.h>
#include "Bitmaps.h"

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

void DisplayManager::startAnim(int16_t w, int16_t h, int16_t x, int16_t y, const unsigned char *frames[], int frameCount, uint16_t color, uint8_t fps, uint16_t maxDelay)
{
    stopAnim();

    static int _w = w;
    static int _h = h;
    static int _x = x;
    static int _y = y;
    static const unsigned char **_frames = frames;
    static int _frameCount = frameCount;
    static uint16_t _color = color;
    static uint8_t _fps = fps;
    static uint16_t _maxDelay = maxDelay;

    xTaskCreatePinnedToCore([](void *param)
                            {
DisplayManager *displayManager = DisplayManager::getInstance();
displayManager->runAnimTask(_w, _w, _x, _y, _frames, _frameCount, _color, _fps,_maxDelay); },
                            "AnimTask", 2048, NULL, 2, &animTaskHandle, 1);
}

void DisplayManager::stopAnim()
{
    if (animTaskHandle != NULL)
    {
        vTaskDelete(animTaskHandle);
        animTaskHandle = NULL;
    };
}

void DisplayManager::runAnimTask(int16_t w, int16_t h, int16_t x, int16_t y, const unsigned char *frames[], int frameCount, uint16_t color, uint8_t fps, uint16_t maxDelay)
{
    if (frameCount == 1)
    {
        this->display->clearDisplay();
        this->display->drawBitmap(x, y, frames[0], w, h, SH110X_WHITE, SH110X_BLACK);
        this->display->display();
    }

    int delayTime = pdMS_TO_TICKS(1000 / fps); // Calculate delay time in milliseconds based on FPS
    int frameIndex = 0;

    while (true)
    {
        this->display->clearDisplay();
        this->display->drawBitmap(x, y, frames[frameIndex], w, h, color);
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
    };
}

void DisplayManager::stopLoading()
{
    if (loadingTaskHandle != NULL)
    {
        vTaskDelete(loadingTaskHandle);
        loadingTaskHandle = NULL;
        currentDisplayMode = DisplayMode::HOME;
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
                        displayManager->display->drawCircleHelper(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 10, 1 << i, SH110X_WHITE);
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

void DisplayManager::writeMenuTitle(String title)
{
    display->setTextSize(1);
    display->fillRect(0, 0, SCREEN_WIDTH, TEXT_PIXELS_PER_UNIT + 2, SH110X_BLACK);
    display->setCursor(1, 1);
    display->setTextColor(SH110X_WHITE);
    display->println(title);
}

void DisplayManager::showMenu(String title, std::vector<String> options, int menuCursor)
{
    if (currentDisplayMode != DisplayMode::MENU)
    {
        faceAnimator->hide();
        currentDisplayMode = DisplayMode::MENU;
    }

    display->clearDisplay();

    display->setTextSize(1);
    display->setTextColor(SH110X_WHITE);

    short subMenuIndex = 0;
    short subMenusSize = options.size();
    int selectorRectYBtm = (menuCursor + 1) * TEXT_PIXELS_PER_UNIT + TEXT_PIXELS_PER_UNIT; // Include title height
    int offsetY = max(0, selectorRectYBtm - SCREEN_HEIGHT + TEXT_PIXELS_PER_UNIT);
    display->setCursor(display->getCursorX(), TEXT_PIXELS_PER_UNIT + 2 - offsetY);
    for (subMenuIndex = 0; subMenuIndex < subMenusSize; subMenuIndex++)
    {
        if (subMenuIndex == menuCursor)
        {
            int16_t rectX = 0;
            int16_t rectY = display->getCursorY();
            int16_t rectHeight = TEXT_PIXELS_PER_UNIT;
            display->fillRect(rectX, rectY, SCREEN_WIDTH, rectHeight, SH110X_WHITE);
            display->setTextColor(SH110X_BLACK);
        }
        else
        {
            display->setTextColor(SH110X_WHITE);
        }

        display->print("> ");
        display->println(options[subMenuIndex]);
    }

    // Write title
    writeMenuTitle(title);

    display->display();
}

void DisplayManager::exitMenu()
{
    if (currentDisplayMode != DisplayMode::MENU)
    {
        return;
    }

    currentDisplayMode = DisplayMode::HOME;
    display->clearDisplay();
    display->display();
    faceAnimator->show();
    Serial.println("Exit menu");
}

void DisplayManager::showIdle()
{
    faceAnimator->setState(FaceState::FACE_IDLE);
    faceAnimator->setExpression(FaceExpression::FACE_NEUTRAL);
}

void DisplayManager::changeMood(FaceExpression expression)
{
    switch (expression)
    {
    case FaceExpression::FACE_ANGRY:
    case FaceExpression::FACE_HAPPY:
    case FaceExpression::FACE_SAD:
    case FaceExpression::FACE_NEUTRAL:
    case FaceExpression::FACE_TIRED:
        faceAnimator->setState(FaceState::FACE_IDLE);
        break;
    case FaceExpression::FACE_SLEEP:
        faceAnimator->setState(FaceState::FACE_STILL);
        break;
    default:
        break;
    }
    faceAnimator->setExpression(expression);
}

void DisplayManager::showCalibratorSelector(String title, int cursor, bool blink)
{
    display->clearDisplay();

    display->drawBitmap(HALF_SCREEN_WIDTH - HEXAPOD_VECTOR_W / 2, HALF_SCREEN_HEIGHT - HEXAPOD_VECTOR_H / 2 + TEXT_PIXELS_PER_UNIT, blink ? hexapodVectors[0] : hexapodVectors[cursor], HEXAPOD_VECTOR_W, HEXAPOD_VECTOR_H, SH110X_WHITE);

    int backPosY = SCREEN_HEIGHT - TEXT_PIXELS_PER_UNIT - 1;
    if (cursor == 0)
    {
        display->fillRect(0, backPosY, 22, TEXT_PIXELS_PER_UNIT, SH110X_WHITE);
        display->setTextColor(SH110X_BLACK);
    }
    else
    {
        display->setTextColor(SH110X_WHITE);
    }

    display->setCursor(1, backPosY);
    display->setTextSize(1);
    display->println("Back");

    writeMenuTitle(title);

    display->display();

    currTitle = title;
    currCursorValue = cursor;
    startTime = millis();

    currentDisplayMode = DisplayMode::CALIBRATOR_SELECTOR;
}

void DisplayManager::showCalibratorSetter(String title, int pwm)
{
    display->clearDisplay();

    writeMenuTitle(title);

    int16_t textX1 = 0;
    int16_t textY1 = 0;
    u_int16_t textWidth = 0;
    u_int16_t textHeight = 0;
    display->setTextSize(3);
    display->getTextBounds(String(pwm), 0, 0, &textX1, &textY1, &textWidth, &textHeight);
    display->setCursor(HALF_SCREEN_WIDTH - textWidth / 2, HALF_SCREEN_HEIGHT - textHeight / 2);
    display->println(pwm);

    display->display();

    currentDisplayMode = DisplayMode::CALIBRATOR_SETTER;
}

void DisplayManager::loop()
{
    faceAnimator->loop();

    if (currentDisplayMode == DisplayMode::CALIBRATOR_SELECTOR)
    {
        ulong elapsedTime = millis() - startTime;
        if(elapsedTime > 500) {
            showCalibratorSelector(currTitle, currCursorValue, millis() % 2);
        }
    }
}