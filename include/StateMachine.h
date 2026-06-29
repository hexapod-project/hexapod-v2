#pragma once 

#include "DisplayManager.h"
#include "FaceAnimator.h"

class StateMachine
{
private:
    static StateMachine *instance;
    FaceAnimator *faceAnimator;
    ulong startIdleMS = 0;
    ulong startSleepMS = 0;

    State state = State::STATE_IDLE;

public:
    StateMachine();
    static StateMachine* getInstance();
    State getState();
    void init();
    void idle();
    void sleep();
    void moving(int moveDir);
    void loop();
};