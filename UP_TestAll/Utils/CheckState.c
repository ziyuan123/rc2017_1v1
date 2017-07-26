//
// Created by ilalh on 2017/7/11.
//

#include "CheckState.h"
#include "common.h"

u8 CS_IRSensorList[4];
u8 CS_IRSensorData[4];

int CS_Enable = DISABLE;

int CS_State = STATE_UNDER_STAGE_FACE_TO_STAGE;

void CS_CheckState() {
    if (CS_Enable == DISABLE)
        return;
    int i = 0;
    for (i = 0; i < 4; i++) {
        CS_IRSensorData[i] = UP_ADC_GetIO(CS_IRSensorList[i]);
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
    CS_State = STATE_ON_STAGE;
}
