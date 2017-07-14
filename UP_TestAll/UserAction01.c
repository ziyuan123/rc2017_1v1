//
// Created by admin on 2017/7/14.
//

#include "UserAction01.h"
#include "UpLib/UP_System.h"

int UA01_arm_servo_list[4] = {3, 4, 5, 6};
int UA01_hand_motor_list[4] = {7, 8, 9, 10};
int UA01_hand_motor_speed[4] = {0, 0, 0, 0};

void UA01_Init() {
    int i = 0;
    for (i = 0; i < 4; i++) {
        UP_CDS_SetMode(UA01_arm_servo_list[i], CDS_SEVMODE);
        UP_CDS_SetMode(UA01_hand_motor_list[i], CDS_MOTOMODE);
    }
}

void UA01_FrontArmUp() {
    UP_CDS_SetAngle(UA01_arm_servo_list[0], 100, 512);
    UP_CDS_SetAngle(UA01_arm_servo_list[1], 900, 512);
}

void UA01_FrontArmDown() {
    UP_CDS_SetAngle(UA01_arm_servo_list[0], 900, 512);
    UP_CDS_SetAngle(UA01_arm_servo_list[1], 100, 512);
}

void UA01_BackArmUp() {
    UP_CDS_SetAngle(UA01_arm_servo_list[2], 100, 512);
    UP_CDS_SetAngle(UA01_arm_servo_list[3], 900, 512);
}

void UA01_BackArmDown() {
    UP_CDS_SetAngle(UA01_arm_servo_list[2], 900, 512);
    UP_CDS_SetAngle(UA01_arm_servo_list[3], 100, 512);
}