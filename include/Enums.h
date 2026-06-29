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
    STOP_TO_CHANGE_DIRECTION,
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

enum Joint
{
    LEFT_FRONT_COXA = 1,
    LEFT_FRONT_FEMUR = 2,
    LEFT_FRONT_TIBIA = 3,
    
    LEFT_MID_COXA = 4,
    LEFT_MID_FEMUR = 5,
    LEFT_MID_TIBIA = 6,
    
    LEFT_BACK_COXA = 7,
    LEFT_BACK_FEMUR = 8,
    LEFT_BACK_TIBIA = 9,
    
    RIGHT_FRONT_COXA = 10,
    RIGHT_FRONT_FEMUR = 11,
    RIGHT_FRONT_TIBIA = 12,
    
    RIGHT_MID_COXA = 13,
    RIGHT_MID_FEMUR = 14,
    RIGHT_MID_TIBIA = 15,
    
    RIGHT_BACK_COXA = 16,
    RIGHT_BACK_FEMUR = 17,
    RIGHT_BACK_TIBIA = 18,
};

enum DisplayMode
{
    HOME,
    LOADING,
    MENU,
    CALIBRATOR_SELECTOR,
    CALIBRATOR_SETTER
};

enum FaceExpression
{
    FACE_NEUTRAL,
    FACE_HAPPY,
    FACE_SAD,
    FACE_ANGRY,
    FACE_TIRED,
    FACE_SLEEP
};

enum FaceState
{
    FACE_NONE,    
    FACE_IDLE,
    FACE_STILL
};

enum State
{
    STATE_IDLE,
    SATE_MOVING,
    STATE_SLEEP
};
