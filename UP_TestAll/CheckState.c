//
// Created by ilalh on 2017/7/11.
//

#include "CheckState.h"
#include "common.h"

u8 CS_IRSensorList[4];
u8 CS_IRSensorData[4];

int CS_Enable = DISABLE;

int CS_State = STATE_UNDER_STAGE;

void CS_CheckState() {
    if (CS_Enable == DISABLE)
        return;
    int i = 0;
    for (i = 0; i < 4; i++) {
        CS_IRSensorData[i] = UP_ADC_GetIO(CS_IRSensorList[i]);
    }

    if ((CS_IRSensorData[0] && CS_IRSensorData[1]) || (CS_IRSensorData[2] && CS_IRSensorData[3])) {
        CS_State = STATE_UNDER_STAGE;
        return;
    }
    for (i = 0; i < 4; i++) {
        if (CS_IRSensorData[i] == 1) {
            CS_State = i + 1;
            return;
        }
    }
    CS_State = STATE_ON_STAGE;
}
