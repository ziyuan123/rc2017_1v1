#include "UpLib/UP_System.h"
#include "common.h"
#include "Grayscale4Sensor.h"
#include "ServoMove.h"
#include "CheckState.h"


#ifdef DEBUG_ON
//then the program is in debug mode
#endif


u8 GLOBAL_SENSOR_LIST[4] = {0, 1, 2, 3};

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
    CS_Enable = ENABLE;

    while (1) {
        switch (CS_State) {
            case STATE_ON_STAGE:
                break;
            case STATE_UNDER_STAGE:
                break;
            case STATE_ENEMY_FORWARD:
                break;
            case STATE_ENEMY_BACKWARD:
                break;
            case STATE_ENEMY_LEFT:
                break;
            case STATE_ENEMY_RIGHT:
                break;
            default:
                break;
        }
    }
}
