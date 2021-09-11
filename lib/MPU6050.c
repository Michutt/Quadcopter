#include "MPU6050.h"

#define MPU_ADDR            0x68

void MPU_init(i2c_inst_t i2c, uint32_t baud, uint8_t SDA, uint8_t SCL)
{
    i2c_init(&i2c, baud);
    gpio_set_function(SDA, GPIO_FUNC_I2C);
    gpio_set_function(SCL, GPIO_FUNC_I2C);
    gpio_pull_up(SDA);
    gpio_pull_up(SCL);

    uint8_t buff[] = {0x6B, 0x00};
    i2c_write_blocking(&i2c, MPU_ADDR, buff, 2, false);
}