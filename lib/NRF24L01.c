#include "NRF24L01.h"

#define OUTPUT          1u
#define OUT_LOW         0u
#define OUT_HIGH        1u
#define BYTES_2USE      1u
#define DUMMY_BYTE      0xff
#define WRITE_REG       0b00100000
#define CHANNEL         60u

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

uint8_t NRF_readReg(uint8_t reg)
{
    uint8_t buff = 0;

    setCSNLow();
    spi_write_blocking(NRF1.port, &reg, BYTES_2USE);
    spi_read_blocking(NRF1.port, DUMMY_BYTE, &buff, BYTES_2USE);
    setCSNHigh();

    return buff;
}

void NRF_writeReg(uint8_t reg, uint8_t *buff, uint8_t buffSize)
{
    reg = WRITE_REG | (0b00011111 & reg);

    setCSNLow();
    spi_write_blocking(NRF1.port, &reg, BYTES_2USE);
    spi_write_blocking(NRF1.port, buff, buffSize);
    setCSNHigh();
}


