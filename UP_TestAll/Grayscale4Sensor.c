//
// Created by admin on 2017/6/1.
//

#include "Grayscale4Sensor.h"
#include "UpLib/UP_System.h"
#include "utils.h"
#include "common.h"

extern u8 GLOBAL_SENSOR_LIST[];

int G4S_GRAYSCALE_DATA[4] = {0, 0, 0, 0};

#define G4S_SENSOR_DATA_LENGTH 4
/*
 * 0->forward
 * 1->backward
 * 2->left
 * 3->right
 */
const int G4S_SENSOR_DATA[4][G4S_SENSOR_DATA_LENGTH] = {{0},
                                                        {0},
                                                        {0},
                                                        {0}};

void G4S_update_gray_scale_sensor() {
    G4S_GRAYSCALE_DATA[0] = UP_ADC_GetValue(GLOBAL_SENSOR_LIST[0]);
    G4S_GRAYSCALE_DATA[1] = UP_ADC_GetValue(GLOBAL_SENSOR_LIST[1]);
    G4S_GRAYSCALE_DATA[2] = UP_ADC_GetValue(GLOBAL_SENSOR_LIST[2]);
    G4S_GRAYSCALE_DATA[3] = UP_ADC_GetValue(GLOBAL_SENSOR_LIST[3]);
}

int G4S_Direction_Data[4] = {0};

int G4S_direction_to_centre() {
    int i, max, max_i, average = 0, sum = 0, result;

    //find the nearest value in the array
    for (i = 0; i < 4; i++) {
        G4S_Direction_Data[i] = find_nearest_in_array(G4S_GRAYSCALE_DATA[i], G4S_SENSOR_DATA[i], 0,
                                                      G4S_SENSOR_DATA_LENGTH);
    }

    //find the max G4S_Direction_Data's index
    max = G4S_Direction_Data[0];
    max_i = 0;
    for (i = 0; i < 4; i++) {
        sum += G4S_Direction_Data[i];
        if (G4S_Direction_Data[i] > max) {
            max = G4S_Direction_Data[i];
            max_i = i;
        }
    }

    //return none if max equals average
    average = sum / 4;
    if (average == max)
        return DIRECTION_NONE;

    //the right direction is the opposite
    switch (max_i) {
        case G4S_GRAY_SCALE_SENSOR_FORWARD:
            result = DIRECTION_BACK;
            break;
        case G4S_GRAY_SCALE_SENSOR_BACKWARD:
            result = DIRECTION_FORWARD;
            break;
        case G4S_GRAY_SCALE_SENSOR_LEFT:
            result = DIRECTION_RIGHT;
            break;
        case G4S_GRAY_SCALE_SENSOR_RIGHT:
            result = DIRECTION_LEFT;
            break;
        default:
            result = DIRECTION_NONE;
    }

    return result;
}

