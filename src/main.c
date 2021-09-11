#include "pico/stdlib.h"

#define NRF_CE      0
#define NRF_CSN     0
#define NRF_MOSI    0
#define NRF_MISO    0
#define NRF_CLK     0


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