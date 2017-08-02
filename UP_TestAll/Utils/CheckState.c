//
// Created by ilalh on 2017/7/11.
//

#include "CheckState.h"
#include "common.h"

u8 CS_IRSensorList[8];
u8 CS_IRSensorData[8];

//0--横倾角
//1--竖倾角
u8 CS_InclinationSensorList[2];
u16 CS_InclinationSensorData[2];

int CS_Enable = DISABLE;

int CS_State = STATE_UNDER_STAGE_FACE_TO_STAGE;


//使能
void CS_enable(int enable) {
    if (enable == ENABLE) {
        CS_Enable = ENABLE;
    } else {
        CS_Enable = DISABLE;
        CS_State = STATE_UNDER_STAGE_FACE_TO_STAGE;
    }
}


//
void CS_CheckState() {
    if (CS_Enable == DISABLE)
        return;
    int i = 0;
    for (i = 0; i < 8; i++) {
        CS_IRSensorData[i] = UP_ADC_GetIO(CS_IRSensorList[i]);
    }

    for (i = 0; i < 2; i++) {
        CS_InclinationSensorData[i] = UP_ADC_GetValue(CS_InclinationSensorData[i]);
    }

    if(CS_InclinationSensorData[0]>2500){
        CS_State = STATE_STUCK_LEFT;
        return;
    } else if(CS_InclinationSensorData[0]<2000){
        CS_State = STATE_STUCK_RIGHT;
        return;
    }

    if(CS_InclinationSensorData[1]>2500){
        CS_State = STATE_STUCK_FRONT;
        return;
    } else if(CS_InclinationSensorData[1]<2000){
        CS_State = STATE_STUCK_BACK;
        return;
    }

    if (CS_IRSensorData[0] == 0 && CS_IRSensorData[1] == 0) {
        CS_State = STATE_UNDER_STAGE_FACE_TO_STAGE;
        return;
    } else if (CS_IRSensorData[2] == 0 && CS_IRSensorData[3] == 0) {
        CS_State = STATE_UNDER_STAGE_FACE_NOT_TO_STAGE;
        return;
    }
    for (i = 0; i < 4; i++) {
        if (CS_IRSensorData[i] == 0) {
            CS_State = STATE_ENEMY_FORWARD + i;
            return;
        }
    }

    if (CS_IRSensorData[4] == 0 || CS_IRSensorData[5] == 0) {
        CS_State = STATE_ENEMY_FORWARD;
        return;
    }
    if (CS_IRSensorData[6] == 0 || CS_IRSensorData[7] == 0) {
        CS_State = STATE_ENEMY_BACKWARD;
        return;
    }
    CS_State = STATE_ON_STAGE;
}
