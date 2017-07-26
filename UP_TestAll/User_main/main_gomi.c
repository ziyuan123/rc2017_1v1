#include "UpLib/UP_System.h"
#include "common.h"
#include "Utils/Grayscale4Sensor.h"
#include "Utils/ServoMove.h"
#include "Utils/CheckState.h"
#include "Utils/UserAction01.h"


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
    UA01_Init();
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

    while (!(UP_ADC_GetIO(CS_IRSensorList[2]) == 0 && UP_ADC_GetIO(CS_IRSensorList[3]) == 0));

    UA01_GetOnStage(DIRECTION_FORWARD);

    G4S_Enable = ENABLE;
    CS_Enable = ENABLE;

    int under_stage_count = 0;
    while (1) {
        if (CS_State != STATE_UNDER_STAGE_FACE_TO_STAGE && CS_State != STATE_UNDER_STAGE_FACE_NOT_TO_STAGE) {
            under_stage_count = 0;
            G4S_Enable = ENABLE;
        }
        switch (CS_State) {
            case STATE_ON_STAGE:
                UP_Bluetooth_Puts("OS\n");
                break;
            case STATE_UNDER_STAGE_FACE_TO_STAGE:
            case STATE_UNDER_STAGE_FACE_NOT_TO_STAGE:
                G4S_Enable = DISABLE;
                UP_Bluetooth_Puts("US\n");
                under_stage_count++;
                if (under_stage_count > 4) {
                    UP_Bluetooth_Puts("get on stage\n");
                    G4S_Enable = DISABLE;
                    under_stage_count = 0;
                    UA01_GetOnStage(UA01_FindStage());
                }
                break;
            case STATE_ENEMY_FORWARD:
                UP_Bluetooth_Puts("EF\n");
                break;
            case STATE_ENEMY_BACKWARD:
                UP_Bluetooth_Puts("EB\n");
                break;
            case STATE_ENEMY_LEFT:
                UP_Bluetooth_Puts("EL\n");
                break;
            case STATE_ENEMY_RIGHT:
                UP_Bluetooth_Puts("ER\n");
                break;
            default:
                UP_Bluetooth_Puts("NO\n");
                break;
        }
        UP_delay_ms(500);
    }
}