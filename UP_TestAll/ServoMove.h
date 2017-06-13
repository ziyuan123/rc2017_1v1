//
// Created by ilalh on 2017/6/12.
//

#ifndef RC2017_1V1_SERVOMOVE_H
#define RC2017_1V1_SERVOMOVE_H

void SM_init();

void SM_move(int direction, int speed);

void SM_spin(int direction, int speed);

void SM_turn_around(int direction, int is_forward, int speed, int diff_speed);

void SM_servo_move(int left_speed, int right_speed);

#endif //RC2017_1V1_SERVOMOVE_H
