#include "DisplayManager.h"
#include "Utils.h"
#include <Adafruit_GFX.h>
#include <Wire.h>

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
        if (this->currentDisplayMode != DisplayMode::HOME)
        {
            return;
        }

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
    int selectorRectYBtm = (menuCursor + 1) * TEXT_PIXELS_PER_UNIT + TEXT_PIXELS_PER_UNIT;
    int offsetY = selectorRectYBtm/SCREEN_HEIGHT * TEXT_PIXELS_PER_UNIT;
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
    display->fillRect(0, 0, SCREEN_WIDTH, TEXT_PIXELS_PER_UNIT + 2, SH110X_BLACK);
    display->setCursor(1, 1);
    display->setTextColor(SH110X_WHITE);
    display->println(title);

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

void DisplayManager::loop()
{
    faceAnimator->loop();
}