#include "pico/stdlib.h"

#define NRF_CE      8u
#define NRF_CSN     9u
#define NRF_CLK     10u
#define NRF_MOSI    11u
#define NRF_MISO    12u

int main() {
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (true) {
        gpio_put(LED_PIN, 1);
        sleep_ms(250);
        gpio_put(LED_PIN, 0);
        sleep_ms(250);
    }
}