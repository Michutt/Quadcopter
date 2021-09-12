#ifndef MOTORS_H
#define MOTORS_H

#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

void MOTORS_init(uint8_t motor1, uint8_t motor2, uint8_t motor3, uint8_t motor4);

#endif          // !MOTORS_H