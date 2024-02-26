#include "hexapod.h"
#include "configuration.h"

Hexapod::Hexapod()
{
    this->legs[LEG::RIGHT_FRONT] = LEGS[0];
    this->legs[LEG::RIGHT_MID] = LEGS[1];
    this->legs[LEG::RIGHT_BACK] = LEGS[2];
    this->legs[LEG::LEFT_FRONT] = LEGS[3];
    this->legs[LEG::LEFT_MID] = LEGS[4];
    this->legs[LEG::LEFT_BACK] = LEGS[5];
}

void Hexapod::update() {
    for(int i = 0; i < LEGS_COUNT; i ++) {
        this->legs[i]->update();
    }
}

void Hexapod::walk(double walkDirection) {

}