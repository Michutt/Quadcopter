#include "MPU6050.h"
#include <math.h>
#include <stdio.h>

#define MPU_ADDR            0x68
#define LSB_2G              16384.0
#define RAD                 180u
#define PI                  3.141592654
#define RAD_2_DEG           RAD/PI


static i2c_inst_t MPU_i2c;
static uint16_t MPU_accX, MPU_accY, MPU_accZ;
static uint16_t MPU_gyroX, MPU_gyroY, MPU_gyroZ;
static float_t MPU_accAngleX, MPU_accAngleY;


static void MPU_readRaw(void)
{
    uint8_t readBuff[6u] = {0};
    uint8_t reg = 0x3B;                         // acc data first register

    i2c_write_blocking(&MPU_i2c, MPU_ADDR, &reg, 1u, true);
    i2c_read_blocking(&MPU_i2c, MPU_ADDR, readBuff, 6u, false);

    MPU_accX = readBuff[0] << 8 | readBuff[1];
    MPU_accY = readBuff[2] << 8 | readBuff[3];
    MPU_accZ = readBuff[4] << 8 | readBuff[5];

    reg = 0x43;                                 // gyro data first register
    i2c_write_blocking(&MPU_i2c, MPU_ADDR, &reg, 1u, true);
    i2c_read_blocking(&MPU_i2c, MPU_ADDR, readBuff, 6u, false);

    MPU_gyroX = readBuff[0] << 8 | readBuff[1];
    MPU_gyroY = readBuff[2] << 8 | readBuff[3];
    MPU_gyroZ = readBuff[4] << 8 | readBuff[5];
}

static void MPU_raw2Angle(void)
{
    MPU_accAngleX = atan((MPU_accY/LSB_2G)/sqrt(pow((MPU_accX/LSB_2G), 2u) + pow((MPU_accZ/LSB_2G), 2u))) * RAD_2_DEG;
    MPU_accAngleY = atan(-1 * (MPU_accX/LSB_2G)/sqrt(pow((MPU_accY/LSB_2G), 2u) + pow((MPU_accZ/LSB_2G), 2u))) * RAD_2_DEG;
}

void MPU_init(i2c_inst_t i2c, uint32_t baud, uint8_t SDA, uint8_t SCL)
{
    MPU_i2c = i2c;
    i2c_init(&MPU_i2c, baud);
    gpio_set_function(SDA, GPIO_FUNC_I2C);
    gpio_set_function(SCL, GPIO_FUNC_I2C);
    gpio_pull_up(SDA);
    gpio_pull_up(SCL);

    uint8_t buff[] = {0x6B, 0x00};
    i2c_write_blocking(&MPU_i2c, MPU_ADDR, buff, 2u, false);
}

void MPU_update(void)
{
    MPU_readRaw();
    MPU_raw2Angle();
    printf("%f---%f\n", MPU_accAngleX, MPU_accAngleY);
}
