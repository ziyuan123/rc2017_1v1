//
// Created by admin on 2017/6/1.
//

#include "Grayscale4Sensor.h"
#include "UpLib/UP_System.h"
#include "utils.h"

extern u8 GLOBAL_SENSOR_LIST[];

int G4S_GRAYSCALE_DATA[4] = {0, 0, 0, 0};

#define G4S_SENSOR_DATA_LENGTH 4
/*
 * 0->forward
 * 1->backward
 * 2->left
 * 3->right
 */
const int G4S_SENSOR0_DATA[G4S_SENSOR_DATA_LENGTH] = {0};
const int G4S_SENSOR1_DATA[G4S_SENSOR_DATA_LENGTH] = {0};
const int G4S_SENSOR2_DATA[G4S_SENSOR_DATA_LENGTH] = {0};
const int G4S_SENSOR3_DATA[G4S_SENSOR_DATA_LENGTH] = {0};

const int G4S_SENSOR_DATA[4][G4S_SENSOR_DATA_LENGTH] = {{0},
                                                        {0},
                                                        {0},
                                                        {0}};

void G4S_update_grayscale_sensor() {
    G4S_GRAYSCALE_DATA[0] = UP_ADC_GetValue(GLOBAL_SENSOR_LIST[0]);
    G4S_GRAYSCALE_DATA[1] = UP_ADC_GetValue(GLOBAL_SENSOR_LIST[1]);
    G4S_GRAYSCALE_DATA[2] = UP_ADC_GetValue(GLOBAL_SENSOR_LIST[2]);
    G4S_GRAYSCALE_DATA[3] = UP_ADC_GetValue(GLOBAL_SENSOR_LIST[3]);
}

int G4S_Direction_Data[4] = {0};

int G4S_direction_to_centre() {
    int i;
    for (i = 0; i < 4; i++) {
        G4S_Direction_Data[i] = find_nearst_in_array(G4S_GRAYSCALE_DATA[i], G4S_SENSOR_DATA[i], 0,
                                                     G4S_SENSOR_DATA_LENGTH);
    }
    //TODO judge the direction
    return DIRECNION_NONE;
}

