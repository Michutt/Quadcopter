#ifndef NRF24L01_H
#define NRF24L01_H

#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"

void NRF_init(spi_inst_t *port, uint8_t sck, uint8_t mosi, 
                uint8_t miso, uint8_t ce, uint8_t csn);
uint8_t NRF_readReg(uint8_t reg);
void NRF_writeReg(uint8_t reg, uint8_t *buff, uint8_t buffSize);

#endif          // !NRF24L01_H