//
// Created by ilalh on 2017/7/11.
//

#include "../UpLib/UP_System.h"

#ifndef RC2017_1V1_CHECKSTATE_H
#define RC2017_1V1_CHECKSTATE_H

extern u8 CS_IRSensorList[8];

extern u8 CS_InclinationSensorList[2];

extern int CS_State;

extern u8 CS_EnemyState;

void CS_Init();

void CS_enable(int enable);

void CS_CheckState();

void CS_CheckEnemyExti(u32 channel);
void CS_CheckEnemyExtiFrontLeft();
void CS_CheckEnemyExtiFrontRight();
void CS_CheckEnemyExtiBackLeft();
void CS_CheckEnemyExtiBackRight();

#endif //RC2017_1V1_CHECKSTATE_H
