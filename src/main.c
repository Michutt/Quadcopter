#include "pico/stdlib.h"
#include "logic/motors.h"
#include "hardware/i2c.h"
#include "../lib/MPU6050.h"
#include "cfg.h"

int main() {
    stdio_init_all();
    MPU_init(i2c1_inst, MPU_SPEED, MPU_SDA, MPU_SCL);
    MOTORS_init(MOTOR1, MOTOR2, MOTOR3, MOTOR4);

    while (true) 
    {
        MPU_update();
    }
}