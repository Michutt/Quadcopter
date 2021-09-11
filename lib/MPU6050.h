#ifndef MPU6050_H
#define MPU6050_H

#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"

void MPU_init(i2c_inst_t i2c, uint32_t baud, uint8_t SDA, uint8_t SCL);

#endif          // !MPU6050_H