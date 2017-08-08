//
// Created by admin on 2017/8/6.
//

#ifndef RC2017_1V1_LEDCHEATER_H
#define RC2017_1V1_LEDCHEATER_H

void LC_init(int us, int io);   //  中断设置   定时器延时，IO口
void LC_TimerHandler();          //  中断处理

#endif //RC2017_1V1_LEDCHEATER_H
