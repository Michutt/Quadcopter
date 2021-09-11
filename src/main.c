#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "../lib/MPU6050.h"


#define NRF_CE      8u
#define NRF_CSN     9u
#define NRF_CLK     10u
#define NRF_MOSI    11u
#define NRF_MISO    12u

#define MPU_SCL     3u 
#define MPU_SDA     2u

int main() {
    stdio_init_all();
    MPU_init(i2c1_inst, 400000, MPU_SDA, MPU_SCL);

    while (true) 
    {
        MPU_update();
    }
}