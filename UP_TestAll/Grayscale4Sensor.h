//
// Created by admin on 2017/6/1.
//

#ifndef RC2017_1V1_GRAYSCALE4SENSOR_H
#define RC2017_1V1_GRAYSCALE4SENSOR_H

#define DIRECNION_NONE 0x000
#define DIRECNION_FORWARD 0x001
#define DIRECNION_BACK 0x010
#define DIRECNION_LEFT 0x011
#define DIRECNION_RIGHT 0x100

extern int G4S_GRAYSCALE_DATA[4];

void G4S_update_grayscale_sensor();
int G4S_direction_to_centre();

#endif //RC2017_1V1_GRAYSCALE4SENSOR_H
