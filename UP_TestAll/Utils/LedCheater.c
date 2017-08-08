//
// Created by admin on 2017/8/6.
//

#include "LedCheater.h"
#include "UpLib/UP_IOout.h"
#include "UpLib/UP_Timer.h"

int io_channel = 0;
int io_state = 0;

void LC_init(int us, int io) {
    UP_IOout_Init();
    io_channel = io;
    UP_Timer_EnableIT(3, us);//设置定时器
    UP_Timer_SetHadler(3, LC_TimerHandler);
}

void LC_TimerHandler() {
    if (io_state > 2) {
        UP_IOout_SetIO(io_channel, 1);
        io_state = 0;
    } else {
        UP_IOout_SetIO(io_channel, 0);
        io_state += 1;
    }
}
