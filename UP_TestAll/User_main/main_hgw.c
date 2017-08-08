//
// Created by admin on 2017/7/26.
//
#include "../UpLib/UP_System.h"
#include "../Utils/LedCheater.h"
int main(){
    LC_init(50,0);

    UP_System_Init();   //系统初始化
    UP_delay_ms(100);

    while(1);
}