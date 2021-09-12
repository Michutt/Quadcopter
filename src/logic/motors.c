#include "motors.h"

#define MOTOR_CNT               4u


static uint8_t motors_idx[MOTOR_CNT], slices[MOTOR_CNT], channels[MOTOR_CNT];

void MOTORS_init(uint8_t motor1, uint8_t motor2, uint8_t motor3, uint8_t motor4)
{
    motors_idx[0] = motor1;
    motors_idx[1] = motor2;
    motors_idx[2] = motor3;
    motors_idx[3] = motor4;

    uint8_t i = 0;

    for (i=0u; i<MOTOR_CNT; ++i)
    {
        gpio_set_function(motors_idx[i], GPIO_FUNC_PWM);
        slices[i] = pwm_gpio_to_slice_num(motors_idx[i]);
        channels[i] = pwm_gpio_to_channel(motors_idx[i]);

        pwm_set_clkdiv(slices[i], 152u);
        pwm_set_wrap(slices[i], 16384u); 
        pwm_set_chan_level(slices[i], channels[i], 800u); //~800 min 1600 max
        pwm_set_enabled(slices[i], true);
    }
    
    sleep_ms(7000u);
}