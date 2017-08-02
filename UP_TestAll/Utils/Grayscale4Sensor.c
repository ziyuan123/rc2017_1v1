//
// Created by admin on 2017/6/1.
//

#include "Grayscale4Sensor.h"
#include "../UpLib/UP_System.h"
#include "utils.h"
#include "common.h"
#include "ServoMove.h"
#include "stdlib.h"
#include "CheckState.h"

int G4S_Enable = DISABLE;

int G4S_next_direction = DIRECTION_NONE;

u8 G4S_GrayScaleSensorList[4] = {0, 0, 0, 0};

int G4S_gray_scale_origin_data[4] = {0, 0, 0, 0};

int G4S_direction_data[4] = {0};

int update_count = 0;

void G4S_enable(int enable) {
    if (enable == ENABLE) {
        G4S_Enable = ENABLE;
    } else {
        G4S_Enable = DISABLE;
        G4S_next_direction = DIRECTION_NONE;
    }
}


//数值更新
void G4S_UpdateGrayScaleSensor(void) {
    int i = 0, attack = 0;
    for (i = 0; i < 4; i++) {
        G4S_gray_scale_origin_data[i] = UP_ADC_GetValue(G4S_GrayScaleSensorList[i]);
    }
//    G4S_gray_scale_origin_data[0] = UP_ADC_GetValue(G4S_GrayScaleSensorList[0]);
//    G4S_gray_scale_origin_data[1] = UP_ADC_GetValue(G4S_GrayScaleSensorList[1]);
//    G4S_gray_scale_origin_data[2] = UP_ADC_GetValue(G4S_GrayScaleSensorList[2]);
//    G4S_gray_scale_origin_data[3] = UP_ADC_GetValue(G4S_GrayScaleSensorList[3]);

    G4S_next_direction = G4S_Direction2Centre();

    if (update_count % 100 == 0)
        srand(G4S_gray_scale_origin_data[0]);
    update_count++;
    update_count %= 10000;

    if (G4S_Enable == DISABLE)
        return;

    if (CS_State == STATE_ENEMY_FORWARD || CS_State == STATE_ENEMY_BACKWARD) {
        attack = 1;
        for (i = 0; i < 4; i++) {
            if (G4S_gray_scale_origin_data[i] > 2) {
                attack = 0;
                break;
            }
        }
        if (attack)
            return;
    }

    if (G4S_next_direction == DIRECTION_NONE) {
        switch (rand() % 10) {
            case 0:
            case 1:
            case 2:
                SM_Move(DIRECTION_FORWARD, MOTOR_SPEED);
                break;
            case 3:
            case 4:
            case 5:
                SM_Move(DIRECTION_BACK, MOTOR_SPEED);
                break;
            case 6:
            case 7:
                SM_Spin(DIRECTION_LEFT, MOTOR_SPEED);
                break;
            case 8:
            case 9:
                SM_Spin(DIRECTION_RIGHT, MOTOR_SPEED);
                break;
            default:
                SM_Move(DIRECTION_FORWARD, MOTOR_SPEED);
                break;
        }
        return;
    }

    if (G4S_next_direction & DIRECTION_LEFT) {
        SM_Spin(DIRECTION_LEFT, MOTOR_SPEED);
    } else if (G4S_next_direction & DIRECTION_RIGHT) {
        SM_Spin(DIRECTION_RIGHT, MOTOR_SPEED);
    }
    if (G4S_next_direction & DIRECTION_FORWARD) {
        SM_Move(DIRECTION_FORWARD, MOTOR_SPEED);
    } else if (G4S_next_direction & DIRECTION_BACK) {
        SM_Move(DIRECTION_BACK, MOTOR_SPEED);
    }
}


//方向判断   返回方向值
int G4S_Direction2Centre() {
    int i, x = 0, y = 0, result = DIRECTION_NONE;

    //find the nearest value in the array
    for (i = 0; i < 4; i++) {
        G4S_direction_data[i] = find_nearest_in_array_descend(G4S_gray_scale_origin_data[i], kG4S_SensorData[i], 0,
                                                              G4S_SENSOR_DATA_LENGTH);
    }

    y = G4S_direction_data[G4S_GRAY_SCALE_SENSOR_BACKWARD] -
        G4S_direction_data[G4S_GRAY_SCALE_SENSOR_FORWARD];//backward - forward
    x = G4S_direction_data[G4S_GRAY_SCALE_SENSOR_RIGHT] -
        G4S_direction_data[G4S_GRAY_SCALE_SENSOR_LEFT];//right - left

    if (x == 0 && y == 0) {
        return result;
    }
    if (x > 0) {
        result |= DIRECTION_LEFT;
    } else if (x < 0) {
        result |= DIRECTION_RIGHT;
    }

    if (y > 0) {
        result |= DIRECTION_FORWARD;
    } else if (y < 0) {
        result |= DIRECTION_BACK;
    }

    return result & 0x0f;
}

