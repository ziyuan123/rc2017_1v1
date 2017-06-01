#include "UpLib/UP_System.h"
#include "Grayscale4Sensor.h"

#ifdef DEBUG_ON
//then the program is in debug mode
#endif

u8 GLOBAL_SENSOR_LIST[] = {1, 2, 3, 4};

int main(void) {
    UP_Timer_EnableIT(0, 10000);
    UP_Timer_SetHadler(0, G4S_update_grayscale_sensor);
    UP_System_Init();
    UP_delay_ms(100);

    while (1) {
    }
}
