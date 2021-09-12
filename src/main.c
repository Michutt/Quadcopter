#include "pico/stdlib.h"
#include "logic/motors.h"

#define NRF_CE      8u
#define NRF_CSN     9u
#define NRF_CLK     10u
#define NRF_MOSI    11u
#define NRF_MISO    12u

#define MOTOR1      0u
#define MOTOR2      1u
#define MOTOR3      4u
#define MOTOR4      5u

int main() {
    MOTORS_init(MOTOR1, MOTOR2, MOTOR3, MOTOR4);

    while (true) {
        
    }
}