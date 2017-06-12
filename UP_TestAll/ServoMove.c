//
// Created by ilalh on 2017/6/12.
//

#include "ServoMove.h"
#include "common.h"
#include "UpLib/STM32Lib/stm32f10x.h"
#include "UpLib/UP_CDS5500.h"

void SM_move(int direction, int speed) {
    speed = speed > 0 ? speed : -speed;
    if (direction == DIRECTION_FORWARD) {
        SM_servo_move(-speed, speed);
    } else if (direction == DIRECTION_BACK) {
        SM_servo_move(speed, -speed);
    }
}

void SM_spin(int direction, int speed) {
    speed = speed > 0 ? speed : -speed;
    if (direction == DIRECTION_LEFT) {
        SM_servo_move(speed, speed);
    } else if (direction == DIRECTION_RIGHT) {
        SM_servo_move(-speed, -speed);
    }
}

void SM_turn_around(int direction, int speed, int diff_speed) {
    speed = speed > 0 ? speed : -speed;
    diff_speed = diff_speed > 0 ? diff_speed : -diff_speed;
    if (direction == DIRECTION_LEFT) {
        SM_servo_move(-speed, speed + diff_speed);
    } else if (direction == DIRECTION_RIGHT) {
        SM_servo_move(speed + diff_speed, -speed);
    }
}

void SM_servo_move(int left_speed, int right_speed) {

}
