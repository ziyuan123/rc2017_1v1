//
// Created by admin on 2017/6/1.
//

#include "Grayscale4Sensor.h"
#include "UpLib/UP_System.h"
#include "utils.h"
#include "common.h"
#include "ServoMove.h"

int G4SNextDirection = DIRECTION_NONE;

u8 G4S_GRAY_SCALE_SENSOR_LIST[4] = {0, 0, 0, 0};

int G4S_GRAYSCALE_DATA[4] = {0, 0, 0, 0};

#define G4S_SENSOR_DATA_LENGTH 4
/*
 * 0->forward
 * 1->backward
 * 2->left
 * 3->right
 */
const int G4S_SENSOR_DATA[4][G4S_SENSOR_DATA_LENGTH] = {{3200, 3100, 3020, 2700},
                                                        {3150, 3030, 2720, 2450},
                                                        {3150, 3050, 2720, 2350},
                                                        {3100, 3000, 2680, 2380}};
int moto_speed = 500;

void G4S_update_gray_scale_sensor(void) {
    G4S_GRAYSCALE_DATA[0] = UP_ADC_GetValue(G4S_GRAY_SCALE_SENSOR_LIST[0]);
    G4S_GRAYSCALE_DATA[1] = UP_ADC_GetValue(G4S_GRAY_SCALE_SENSOR_LIST[1]);
    G4S_GRAYSCALE_DATA[2] = UP_ADC_GetValue(G4S_GRAY_SCALE_SENSOR_LIST[2]);
    G4S_GRAYSCALE_DATA[3] = UP_ADC_GetValue(G4S_GRAY_SCALE_SENSOR_LIST[3]);

    G4SNextDirection = G4S_direction_to_centre();

    if (G4SNextDirection == DIRECTION_NONE) {
        SM_move(DIRECTION_FORWARD, moto_speed);
        return;
    }
    if (G4SNextDirection & DIRECTION_LEFT) {
        SM_spin(DIRECTION_LEFT, moto_speed);
    } else if (G4SNextDirection & DIRECTION_RIGHT) {
        SM_spin(DIRECTION_RIGHT, moto_speed);
    }
    if (G4SNextDirection & DIRECTION_FORWARD) {
        SM_move(DIRECTION_FORWARD, moto_speed);
    } else if (G4SNextDirection & DIRECTION_BACK) {
        SM_move(DIRECTION_BACK, moto_speed);
    }
}

int G4S_Direction_Data[4] = {0};

int G4S_direction_to_centre() {
    int i, x = 0, y = 0, result = DIRECTION_NONE;

    //find the nearest value in the array
    for (i = 0; i < 4; i++) {
        G4S_Direction_Data[i] = find_nearest_in_array_descend(G4S_GRAYSCALE_DATA[i], G4S_SENSOR_DATA[i], 0,
                                                              G4S_SENSOR_DATA_LENGTH);
        UP_LCD_ShowInt(i * 2, 1, G4S_Direction_Data[i]);
    }

    y = G4S_Direction_Data[1] - G4S_Direction_Data[0];//backward - forward
    x = G4S_Direction_Data[3] - G4S_Direction_Data[2];//right - left

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

