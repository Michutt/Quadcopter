#ifndef NRF24L01_H
#define NRF24L01_H

#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"

void NRF_init(spi_inst_t *port, uint8_t sck, uint8_t mosi, 
                uint8_t miso, uint8_t ce, uint8_t csn);
void NRF_config(void);
void NRF_TxMode(void);
void NRF_RxMode(void);
void NRF_sendMsg(uint8_t *msg);
void NRF_readMsg(uint8_t *msg);
uint8_t NRF_newMsg(void);

#endif          // !NRF24L01_H