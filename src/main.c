#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define NRF_CE      8u
#define NRF_CSN     9u
#define NRF_CLK     10u
#define NRF_MOSI    11u
#define NRF_MISO    12u

int main() {
    gpio_set_function(0, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(0);
    uint channel = pwm_gpio_to_channel(0);

    pwm_set_clkdiv(slice, 152);
    pwm_set_wrap(slice, 16384); 
    pwm_set_chan_level(slice, channel, 800); //~800 min 1600 max
    pwm_set_enabled(slice, true);

    sleep_ms(10000);

    pwm_set_chan_level(slice, channel, 1000); //~800 min 1600 max
    pwm_set_enabled(slice, true);

    sleep_ms(2000);

    pwm_set_chan_level(slice, channel, 800); //~800 min 1600 max
    pwm_set_enabled(slice, true);
    while (true) {
        
    }
}