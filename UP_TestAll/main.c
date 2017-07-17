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
    CS_IRSensorList[0] = GLOBAL_SENSOR_LIST[4];
    CS_IRSensorList[1] = GLOBAL_SENSOR_LIST[5];
    CS_IRSensorList[2] = GLOBAL_SENSOR_LIST[6];
    CS_IRSensorList[3] = GLOBAL_SENSOR_LIST[7];
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

    G4S_Enable = DISABLE;
    CS_Enable = ENABLE;

    UP_LCD_ClearScreen();

    while (1) {
        switch (CS_State) {
            case STATE_ON_STAGE:
                UP_Bluetooth_Puts("OS");
                break;
            case STATE_UNDER_STAGE:
                UP_Bluetooth_Puts("US");
                break;
            case STATE_ENEMY_FORWARD:
                UP_Bluetooth_Puts("EF");
                break;
            case STATE_ENEMY_BACKWARD:
                UP_Bluetooth_Puts("EB");
                break;
            case STATE_ENEMY_LEFT:
                UP_Bluetooth_Puts("EL");
                break;
            case STATE_ENEMY_RIGHT:
                UP_Bluetooth_Puts("ER");
                break;
            default:
                UP_Bluetooth_Puts("NO");
                break;
        }
        UP_delay_ms(500);
    }
}
