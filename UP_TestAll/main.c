#include "UpLib/UP_System.h"
#include "common.h"
#include "Grayscale4Sensor.h"
#include "ServoMove.h"
#include "CheckState.h"


#ifdef DEBUG_ON
//then the program is in debug mode
#endif


u8 GLOBAL_SENSOR_LIST[8] = {0, 1, 2, 3, 4, 5, 6, 7};

void init() {
    G4S_GrayScaleSensorList[0] = GLOBAL_SENSOR_LIST[0];
    G4S_GrayScaleSensorList[1] = GLOBAL_SENSOR_LIST[1];
    G4S_GrayScaleSensorList[2] = GLOBAL_SENSOR_LIST[2];
    G4S_GrayScaleSensorList[3] = GLOBAL_SENSOR_LIST[3];
    SM_Init();
}

int main(void) {

#ifdef DEBUG_ON
    UP_Bluetooth_EnableIT();
#endif

    UP_Timer_EnableIT(0, 5000);//5ms
    UP_Timer_SetHadler(0, G4S_UpdateGrayScaleSensor);
    UP_Timer_EnableIT(1, 5000);//5ms
    UP_Timer_SetHadler(1, CS_CheckState);
    UP_System_Init();
    UP_delay_ms(100);

    init();

    G4S_Enable = ENABLE;
    CS_Enable = DISABLE;

    while (1) {
        switch (CS_State) {
            case STATE_ON_STAGE:
                UP_LCD_ShowString(0, 0, "OS");
                break;
            case STATE_UNDER_STAGE:
                UP_LCD_ShowString(0, 0, "US");
                break;
            case STATE_ENEMY_FORWARD:
                UP_LCD_ShowString(0, 0, "EF");
                break;
            case STATE_ENEMY_BACKWARD:
                UP_LCD_ShowString(0, 0, "EB");
                break;
            case STATE_ENEMY_LEFT:
                UP_LCD_ShowString(0, 0, "EL");
                break;
            case STATE_ENEMY_RIGHT:
                UP_LCD_ShowString(0, 0, "ER");
                break;
            default:
                UP_LCD_ShowString(0, 0, "NO");
                break;
        }
    }
}
