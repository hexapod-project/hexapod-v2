#ifndef Gaits_H
#define Gaits_H

#include <map>
#include <vector>
#include "Leg.h"

enum GaitType
{
    TRIPOD
};

extern std::map<GaitType, std::vector<std::vector<LegType>>> GAITS;

#endif