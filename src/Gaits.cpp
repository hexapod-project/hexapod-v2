#include "Gaits.h"

std::vector<std::vector<LegType>> TRIPOD_GAIT = {
    {LegType::RIGHT_FRONT, LegType::LEFT_MID, LegType::RIGHT_BACK},
    {LegType::LEFT_FRONT, LegType::RIGHT_MID, LegType::LEFT_BACK},
};

std::map<GaitType, std::vector<std::vector<LegType>>> GAITS = {
    {GaitType::TRIPOD, TRIPOD_GAIT},
};