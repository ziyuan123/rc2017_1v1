//
// Created by admin on 2017/7/14.
//

#include "common.h"
#include "UserAction_czy.h"
#include "../UpLib/UP_System.h"
#include "Grayscale4Sensor.h"
#include "ServoMove.h"
#include "CheckState.h"
#include "stdlib.h"

u8 UAczy_arm_servo_list[4] = {3, 4, 5, 6};//电机编号
u8 UAczy_hand_motor_list[4] = {7, 8, 9, 10};//手臂编号
s16 UAczy_hand_motor_speed[4] = {0, 0, 0, 0};//速度


//初始化
void UA01_Init1() {
    int i = 0;
    for (i = 0; i < 4; i++) {
        UP_CDS_SetMode(UAczy_arm_servo_list[i], CDS_SEVMODE);
        UP_CDS_SetMode(UAczy_hand_motor_list[i], CDS_MOTOMODE);
    }
}

//前手臂up
void UA01_FrontArmUp1() {
    UP_CDS_SetAngle(UAczy_arm_servo_list[0], 250, 512);
    UP_CDS_SetAngle(UAczy_arm_servo_list[1], 750, 512);
}

//前手臂down
void UA01_FrontArmDown1() {
    UP_CDS_SetAngle(UAczy_arm_servo_list[0], 750, 512);
    UP_CDS_SetAngle(UAczy_arm_servo_list[1], 250, 512);
}

//后手臂up
void UA01_BackArmUp1() {
    UP_CDS_SetAngle(UAczy_arm_servo_list[2], 750, 512);
    UP_CDS_SetAngle(UAczy_arm_servo_list[3], 250, 512);
}

//后手臂down
void UA01_BackArmDown1() {
    UP_CDS_SetAngle(UAczy_arm_servo_list[2], 250, 512);
    UP_CDS_SetAngle(UAczy_arm_servo_list[3], 750, 512);
}


//动作
void UA01_PreAction1() {
    int i = 0;
    for (i = 0; i < 4; i++) {
        UAczy_hand_motor_speed[i] = 0;
    }
    UP_CDS_Set4MotoSpeed(UAczy_hand_motor_list, UAczy_hand_motor_speed);
    UA01_FrontArmUp1();
    UA01_BackArmUp1();
}

//上台
void UA01_GetOnStage1(int direction) {
    UA01_PreAction1();
    if (direction == DIRECTION_FORWARD) {
        UAczy_hand_motor_speed[0] = MOTOR_SPEED;
        UAczy_hand_motor_speed[1] = -MOTOR_SPEED;
        UAczy_hand_motor_speed[2] = MOTOR_SPEED;
        UAczy_hand_motor_speed[3] = -MOTOR_SPEED;
        UP_CDS_Set4MotoSpeed(UAczy_hand_motor_list, UAczy_hand_motor_speed);//四电机速度初始化设置
        SM_Move(DIRECTION_FORWARD, 700);    //MOTOR_SPEED速度向前
    } else {
        UAczy_hand_motor_speed[0] = -MOTOR_SPEED;
        UAczy_hand_motor_speed[1] = MOTOR_SPEED;
        UAczy_hand_motor_speed[2] = -MOTOR_SPEED;
        UAczy_hand_motor_speed[3] = MOTOR_SPEED;
        UP_CDS_Set4MotoSpeed(UAczy_hand_motor_list, UAczy_hand_motor_speed);
        SM_Move(DIRECTION_BACK, 700);   //MOTOR_SPEED速度向后
    }
    UP_delay_ms(400);


    /*前手臂下*/
    if (direction == DIRECTION_FORWARD)
        UA01_FrontArmDown1();
    else
        UA01_BackArmDown1();

    UP_delay_ms(1000);


    /*后手臂下*/
    if (direction == DIRECTION_FORWARD)
        UA01_BackArmDown1();
    else
        UA01_FrontArmDown1();

    UP_delay_ms(400);


    /*前起*/
    if (direction == DIRECTION_FORWARD)
        UA01_FrontArmUp1();
    else
        UA01_BackArmUp1();

    UP_delay_ms(500);



    /*后起*/
    if (direction == DIRECTION_FORWARD)
        UA01_BackArmUp1();
    else
        UA01_FrontArmUp1();

    UP_delay_ms(200);
}

//找寻擂台
int UA01_FindStage1() {
    int stable_count = 0;

    while (CS_State != STATE_UNDER_STAGE_FACE_TO_STAGE) {
        SM_Spin(DIRECTION_LEFT, 300);
        UP_delay_ms(100);
    }
    SM_Move(DIRECTION_FORWARD, 0);

    while (1) {
        stable_count = 0;
        while (stable_count < 10) {
            SM_Move(DIRECTION_FORWARD, MOTOR_SPEED);
            if (G4S_direction_data[2] > 2 && G4S_direction_data[3] > 2 && G4S_direction_data[0] > 2)
                return DIRECTION_FORWARD;
            else
                stable_count++;
            UP_delay_ms(200);
        }
        stable_count = 0;
        while (stable_count < 10) {
            SM_Move(DIRECTION_BACK, MOTOR_SPEED);
            if (G4S_direction_data[2] > 2 && G4S_direction_data[3] > 2 && G4S_direction_data[1] > 2)
                return DIRECTION_BACK;
            else
                stable_count++;
            UP_delay_ms(200);
        }

        SM_Spin(DIRECTION_LEFT, 300);
        UP_delay_ms(400);
    }
}


//攻击
void UA01_PreAttack1() {
    int i = 0;
    for (i = 0; i < 4; i++) {
        UAczy_hand_motor_speed[i] = 0;
    }
    UP_CDS_SetAngle(UAczy_arm_servo_list[0], 512+112, 512);
    UP_CDS_SetAngle(UAczy_arm_servo_list[1], 512-112, 512);
    UP_CDS_SetAngle(UAczy_arm_servo_list[2], 512-127, 512);
    UP_CDS_SetAngle(UAczy_arm_servo_list[3], 512+127, 512);
}

//攻击
void UA01_Attack1(int direction) {
    UA01_PreAttack1();
    if (direction == DIRECTION_FORWARD) {
        UAczy_hand_motor_speed[0] = MOTOR_SPEED_ATTACK;
        UAczy_hand_motor_speed[1] = -MOTOR_SPEED_ATTACK;
        UAczy_hand_motor_speed[2] = -MOTOR_SPEED_ATTACK;
        UAczy_hand_motor_speed[3] = MOTOR_SPEED_ATTACK;
        UP_CDS_Set4MotoSpeed(UAczy_hand_motor_list, UAczy_hand_motor_speed);//四电机速度初始化设置
        SM_Move(DIRECTION_FORWARD, MOTOR_SPEED_ATTACK);    //MOTOR_SPEED_ATTACK速度向前
    } else {
        UAczy_hand_motor_speed[0] = -MOTOR_SPEED_ATTACK;
        UAczy_hand_motor_speed[1] = MOTOR_SPEED_ATTACK;
        UAczy_hand_motor_speed[2] = MOTOR_SPEED_ATTACK;
        UAczy_hand_motor_speed[3] = -MOTOR_SPEED_ATTACK;
        UP_CDS_Set4MotoSpeed(UAczy_hand_motor_list, UAczy_hand_motor_speed);
        SM_Move(DIRECTION_BACK, MOTOR_SPEED_ATTACK);   //MOTOR_SPEED_ATTACK速度向后
    }
}

void UA01_StopAttack1() {
    int i = 0;
    for (i = 0; i < 4; i++) {
        UAczy_hand_motor_speed[i] = 0;
    }
    UP_CDS_Set4MotoSpeed(UAczy_hand_motor_list, UAczy_hand_motor_speed);
}