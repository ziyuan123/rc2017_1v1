#include "UpLib/UP_System.h"
#include "common.h"
#include "Grayscale4Sensor.h"
#include "ServoMove.h"

#ifdef DEBUG_ON
//then the program is in debug mode
#endif

extern u8 GLOBAL_SENSOR_LIST[4] = {1, 2, 3, 4};

int main(void) {
    int next_direction;

#ifdef DEBUG_ON
    UP_Bluetooth_EnableIT();
#endif

    UP_Timer_EnableIT(0, 10000);
    UP_Timer_SetHadler(0, G4S_update_gray_scale_sensor);
    UP_System_Init();
    UP_delay_ms(100);

    SM_init();

    while (1) {

        next_direction = G4S_direction_to_centre();
        switch (next_direction) {
            case DIRECTION_NONE:
                UP_LCD_ShowCharacter(0, 0, 48 + DIRECTION_NONE);
                break;
            case DIRECTION_FORWARD:
//                SM_move(DIRECTION_FORWARD, 512);
                UP_LCD_ShowCharacter(0, 0, 48 + DIRECTION_FORWARD);
                break;
            case DIRECTION_BACK:
//                SM_move(DIRECTION_BACK, 512);
                UP_LCD_ShowCharacter(0, 0, 48 + DIRECTION_BACK);
                break;
            case DIRECTION_LEFT:
//                SM_spin(DIRECTION_LEFT, 512);
                UP_LCD_ShowCharacter(0, 0, 48 + DIRECTION_LEFT);
                break;
            case DIRECTION_RIGHT:
//                SM_spin(DIRECTION_RIGHT, 512);
                UP_LCD_ShowCharacter(0, 0, 48 + DIRECTION_RIGHT);
                break;
//            default:
//                SM_spin(DIRECTION_LEFT, 512);
        }
    }
}
