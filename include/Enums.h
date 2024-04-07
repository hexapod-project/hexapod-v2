#pragma once

enum GaitType
{
    TRIPOD
};

enum RotateDirection
{
    ROTATE_RIGHT,
    ROTATE_LEFT,
    ROTATE_STOP
};

enum WalkDirection
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    WALK_STOP
};

enum GaitsManagerStates
{
    MOVING,
    CHANGE_DIRECTION,
    STOP_QUEUED,
    STOPPING,
    STOPPED,
};

enum HexapodState
{
    IDLE,
    WALK
};

enum HexapodMode
{
    CONTROLLER,
    CALIBRATE
};

enum LegType
{
    LEFT_FRONT,
    LEFT_MID,
    LEFT_BACK,
    RIGHT_FRONT,
    RIGHT_MID,
    RIGHT_BACK,
};