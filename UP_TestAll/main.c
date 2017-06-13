#include "UpLib/UP_System.h"
#include "common.h"
#include "Grayscale4Sensor.h"
#include "ServoMove.h"

#ifdef DEBUG_ON
//then the program is in debug mode
#endif

u8 GLOBAL_SENSOR_LIST[4] = {1, 2, 3, 4};
extern u8 G4S_GRAY_SCALE_SENSOR_LIST[4];

void init() {
    G4S_GRAY_SCALE_SENSOR_LIST[0] = GLOBAL_SENSOR_LIST[0];
    G4S_GRAY_SCALE_SENSOR_LIST[1] = GLOBAL_SENSOR_LIST[1];
    G4S_GRAY_SCALE_SENSOR_LIST[2] = GLOBAL_SENSOR_LIST[2];
    G4S_GRAY_SCALE_SENSOR_LIST[3] = GLOBAL_SENSOR_LIST[3];
    SM_init();
}

int main(void) {
    int next_direction;

#ifdef DEBUG_ON
    UP_Bluetooth_EnableIT();
#endif

    UP_Timer_EnableIT(0, 10000);
    UP_Timer_SetHadler(0, G4S_update_gray_scale_sensor);
    UP_System_Init();
    UP_delay_ms(100);

    init();

    while (1) {

        next_direction = G4S_direction_to_centre();
        switch (next_direction) {
            case DIRECTION_NONE:
                UP_LCD_ShowCharacter(0, 0, "0");
                break;
            case DIRECTION_FORWARD:
//                SM_move(DIRECTION_FORWARD, 512);
                UP_LCD_ShowCharacter(0, 0, "F");
                break;
            case DIRECTION_BACK:
//                SM_move(DIRECTION_BACK, 512);
                UP_LCD_ShowCharacter(0, 0, "B");
                break;
            case DIRECTION_LEFT:
//                SM_spin(DIRECTION_LEFT, 512);
                UP_LCD_ShowCharacter(0, 0, "L");
                break;
            case DIRECTION_RIGHT:
//                SM_spin(DIRECTION_RIGHT, 512);
                UP_LCD_ShowCharacter(0, 0, "R");
                break;
//            default:
//                SM_spin(DIRECTION_LEFT, 512);
        }
    }
}
