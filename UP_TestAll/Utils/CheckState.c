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

u8 CS_EnemyState = 0;

void CS_Init() {
    UP_Timer_EnableIT(1, 5000);//5ms    设置定时器
    UP_Timer_SetHadler(1, CS_CheckState);            //定时器中断 擂台检测
    int i = 0;
    u32 channel;
    for (i = 4; i < 8; i++) {
        switch (CS_IRSensorList[i]) {
            case 12:
                channel = EXTI_AD12;
                break;
            case 13:
                channel = EXTI_AD13;
                break;
            case 14:
                channel = EXTI_AD14;
                break;
            case 15:
                channel = EXTI_AD15;
                break;
            default:
                channel = 0;
        }
        if (channel != 0) {
            UP_Exti_EnableIT(channel, EXTI_Trigger_Rising_Falling);
            UP_Exti_SetHadler(CS_CheckEnemyExti);
        }
    }
}

//使能
void CS_enable(int enable) {
    if (enable == ENABLE) {
        CS_Enable = ENABLE;
    } else {
        CS_Enable = DISABLE;
        CS_State = STATE_UNDER_STAGE_FACE_TO_STAGE;
    }
}

void CS_CheckEnemyExti(u32 channel){
    switch (channel) {
        case EXTI_AD12:
            CS_CheckEnemyExtiFrontLeft();
            break;
        case EXTI_AD13:
            CS_CheckEnemyExtiFrontRight();
            break;
        case EXTI_AD14:
            CS_CheckEnemyExtiBackLeft();
            break;
        case EXTI_AD15:
            CS_CheckEnemyExtiBackRight();
            break;
    }
}

void CS_CheckEnemyExtiFrontLeft() {
    int state = UP_ADC_GetIO(CS_IRSensorList[4]);
    if (state) {
        CS_EnemyState &= 0xE;//&0b1110
    } else {
        CS_EnemyState |= 0x1;//0b0001
    }
}

void CS_CheckEnemyExtiFrontRight() {
    int state = UP_ADC_GetIO(CS_IRSensorList[5]);
    if (state) {
        CS_EnemyState &= 0xD;//&0b1101
    } else {
        CS_EnemyState |= 0x2;//0b0010
    }
}

void CS_CheckEnemyExtiBackLeft() {
    int state = UP_ADC_GetIO(CS_IRSensorList[6]);
    if (state) {
        CS_EnemyState &= 0xB;//&0b1011
    } else {
        CS_EnemyState |= 0x4;//0b0100
    }
}

void CS_CheckEnemyExtiBackRight() {
    int state = UP_ADC_GetIO(CS_IRSensorList[7]);
    if (state) {
        CS_EnemyState &= 0x7;//&0b0111
    } else {
        CS_EnemyState |= 0x8;//0b1000
    }
}

void CS_CheckState() {
    if (CS_Enable == DISABLE)
        return;
    int i = 0;
    for (i = 0; i < 4; i++) {
        CS_IRSensorData[i] = UP_ADC_GetIO(CS_IRSensorList[i]);
    }

    for (i = 0; i < 2; i++) {
        CS_InclinationSensorData[i] = UP_ADC_GetValue(CS_InclinationSensorData[i]);
    }

    if (CS_InclinationSensorData[1] > 2500) {
        CS_State = STATE_STUCK_FRONT;
        return;
    } else if (CS_InclinationSensorData[1] < 2000) {
        CS_State = STATE_STUCK_BACK;
        return;
    }

    if (CS_InclinationSensorData[0] > 2500) {
        CS_State = STATE_STUCK_LEFT;
        return;
    } else if (CS_InclinationSensorData[0] < 2000) {
        CS_State = STATE_STUCK_RIGHT;
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
