//
// Created by ilalh on 2017/6/12.
//

#include "ServoMove.h"
#include "common.h"
#include "UpLib/STM32Lib/stm32f10x.h"
#include "UpLib/UP_CDS5500.h"

//SM_Moto_Servo_List[0]--left moto
//SM_Moto_Servo_List[1]--right moto
u8 SM_Moto_Servo_List[4] = {1, 2, 0, 0};
s16 SM_Moto_Servo_Speed[4] = {0, 0, 0, 0};

void SM_init() {
    UP_CDS_SetMode(SM_Moto_Servo_List[0], CDS_MOTOMODE);
    UP_CDS_SetMode(SM_Moto_Servo_List[1], CDS_MOTOMODE);
}

void SM_move(int direction, int speed) {
    speed = speed > 0 ? speed : -speed;
    if (direction == DIRECTION_FORWARD) {
        SM_servo_move(speed, -speed);
    } else if (direction == DIRECTION_BACK) {
        SM_servo_move(-speed, speed);
    } else {
        SM_servo_move(0, 0);
    }
}

void SM_spin(int direction, int speed) {
    speed = speed > 0 ? speed : -speed;
    if (direction == DIRECTION_LEFT) {
        SM_servo_move(-speed, -speed);
    } else if (direction == DIRECTION_RIGHT) {
        SM_servo_move(speed, speed);
    }
}

void SM_turn_around(int direction, int is_forward, int speed, int diff_speed) {
    speed = speed > 0 ? speed : -speed;
    diff_speed = diff_speed > 0 ? diff_speed : -diff_speed;
    int left_speed, right_speed;
    if (direction == DIRECTION_LEFT) {
        left_speed = speed;
        right_speed = speed + diff_speed;
    } else if (direction == DIRECTION_RIGHT) {
        left_speed = speed + diff_speed;
        right_speed = speed;
    }

    if (is_forward == DIRECTION_FORWARD) {
        SM_servo_move(left_speed, -right_speed);
    } else {
        SM_servo_move(-left_speed, right_speed);
    }
}

void SM_servo_move(int left_speed, int right_speed) {
//    UP_CDS_SetSpeed(SM_Moto_Servo_List[0], left_speed);
//    UP_CDS_SetSpeed(SM_Moto_Servo_List[1], right_speed);
    SM_Moto_Servo_Speed[0] = left_speed;
    SM_Moto_Servo_Speed[1] = right_speed;
    UP_CDS_Set4MotoSpeed(SM_Moto_Servo_List, SM_Moto_Servo_Speed);
}
