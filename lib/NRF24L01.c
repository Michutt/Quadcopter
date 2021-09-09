#include "NRF24L01.h"

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

struct NRF_SPI_PINS 
{
    spi_inst_t *port; 
    uint8_t sck; 
    uint8_t mosi; 
    uint8_t miso; 
    uint8_t ce; 
    uint8_t csn;
};

static struct NRF_SPI_PINS NRF1;
static uint8_t rxName[] = "default"; 
static uint8_t rxNameSize = sizeof(rxName);
static uint8_t txName[] = "default"; 
static uint8_t txNameSize = sizeof(txName);

static void setCELow(void)
{
    gpio_put(NRF1.ce, OUT_LOW);
}

static void setCEHigh(void)
{
    gpio_put(NRF1.ce, OUT_HIGH);
}

static void setCSNLow(void)
{
    gpio_put(NRF1.csn, OUT_LOW);
}

static void setCSNHigh(void)
{
    gpio_put(NRF1.csn, OUT_HIGH);
}

static void NRF_writeReg(uint8_t reg, uint8_t *buff, uint8_t buffSize)
{
    reg = WRITE_REG | (0b00011111 & reg);

    setCSNLow();
    spi_write_blocking(NRF1.port, &reg, BYTES_2USE);
    spi_write_blocking(NRF1.port, buff, buffSize);
    setCSNHigh();
}

static void NRF_writeReg8(uint8_t reg, uint8_t buff)
{
    reg = WRITE_REG | (0b00011111 & reg);

    setCSNLow();
    spi_write_blocking(NRF1.port, &reg, BYTES_2USE);
    spi_write_blocking(NRF1.port, &buff, BYTES_2USE);
    setCSNHigh();
}

static uint8_t NRF_readReg(uint8_t reg)
{
    uint8_t buff = 0;

    setCSNLow();
    spi_write_blocking(NRF1.port, &reg, BYTES_2USE);
    spi_read_blocking(NRF1.port, DUMMY_BYTE, &buff, BYTES_2USE);
    setCSNHigh();

    return buff;
}

void NRF_init(spi_inst_t *port, uint8_t sck, uint8_t mosi, 
                uint8_t miso, uint8_t ce, uint8_t csn)
{
    NRF1.port = port;
    NRF1.sck = sck;
    NRF1.mosi = mosi;
    NRF1.miso = miso;
    NRF1.ce = ce;
    NRF1.csn = csn;

    spi_init(port, 1000000);
    gpio_set_function(sck, GPIO_FUNC_SPI);
    gpio_set_function(mosi, GPIO_FUNC_SPI);
    gpio_set_function(miso, GPIO_FUNC_SPI);

    gpio_init(ce);
    gpio_init(csn);
    gpio_set_dir(ce, OUTPUT);
    gpio_set_dir(csn, OUTPUT);

    setCELow();
    setCSNHigh();
}

void NRF_config(void)
{
    setCSNHigh();
    setCELow();
    sleep_ms(11u);

    NRF_writeReg8(0x00, 0b00001010);                  //power up & enable CRC
    sleep_us(1500u);

    NRF_writeReg8(0x01, 0b00000000);                  // no ack

    NRF_writeReg8(0x05, CHANNEL);                     // set channel

    NRF_writeReg(0x0A, rxName, rxNameSize);         // set RX name
    NRF_writeReg(0x10, txName, txNameSize);         // set TX name

    NRF_writeReg8(0x11, BYTES_IN_FRAME);             // set bytes in pipe
}

void NRF_TxMode(void)
{
    uint8_t reg = NRF_readReg(0x00);
    reg &= ~(1<<0);                                 // set PRIM_RX to 0
    NRF_writeReg8(0x00, reg);
    sleep_us(130u);
}

void NRF_RxMode(void)
{
    uint8_t reg = NRF_readReg(0x00);
    reg |= (1<<0);                                  // set PRIM_RX to 0
    NRF_writeReg8(0x00, reg);
    sleep_us(130u);
}

void NRF_sendMsg(uint8_t *msg)
{
    uint8_t reg = SEND_MSG_REG;
    setCSNLow();
    spi_write_blocking(NRF1.port, &reg, BYTES_2USE);
    spi_write_blocking(NRF1.port, msg, BYTES_IN_FRAME);
    setCSNHigh();

    setCEHigh();
    sleep_us(10u);
    setCELow();
}

void NRF_readMsg(uint8_t *msg)
{
    uint8_t reg = READ_MSG_REG;
    setCSNLow();
    spi_write_blocking(NRF1.port, &reg, BYTES_2USE);
    spi_read_blocking(NRF1.port, DUMMY_BYTE, msg, BYTES_IN_FRAME);
    setCSNHigh();
}

uint8_t NRF_newMsg(void)
{
    uint8_t status = NRF_readReg(0x17);
    status = !(status & 1u);

    return status;
}
