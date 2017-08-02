//
// Created by ilalh on 2017/7/11.
//

#include "../UpLib/UP_System.h"

#ifndef RC2017_1V1_CHECKSTATE_H
#define RC2017_1V1_CHECKSTATE_H

extern u8 CS_IRSensorList[4];

extern int CS_State;

void CS_enable(int enable);

void CS_CheckState();

#endif //RC2017_1V1_CHECKSTATE_H
