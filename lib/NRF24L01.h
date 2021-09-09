#ifndef NRF24L01_H
#define NRF24L01_H

#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"

#define OUTPUT          1u
#define OUT_LOW         0u
#define OUT_HIGH        1u
#define BYTES_2USE      1u
#define DUMMY_BYTE      0xff
#define WRITE_REG       0b00100000
#define SEND_MSG_REG    0b10100000
#define READ_MSG_REG    0b01100001
#define CHANNEL         60u
#define BYTES_IN_FRAME  32u
#define NAME_LEN        5u

void NRF_init(spi_inst_t *port, uint8_t sck, uint8_t mosi, 
                uint8_t miso, uint8_t ce, uint8_t csn);
void NRF_TxMode(void);
void NRF_RxMode(void);
void NRF_sendMsg(uint8_t *msg);
void NRF_readMsg(uint8_t *msg);
uint8_t NRF_newMsg(void);
uint8_t NRF_check(void);

#endif          // !NRF24L01_H