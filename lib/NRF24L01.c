#include "NRF24L01.h"

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
static uint8_t rxName[] = "namee"; 
static uint8_t txName[] = "namee"; 

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

static void NRF_config(void)
{
    setCSNHigh();
    setCELow();
    sleep_ms(11u);

    NRF_writeReg8(0x00, 0b00001010);                  //power up & enable CRC
    sleep_us(1500u);

    NRF_writeReg8(0x01, 0b00000000);                  // no ack

    NRF_writeReg8(0x05, CHANNEL);                     // set channel

    NRF_writeReg(0x0A, rxName, NAME_LEN);         // set RX name
    NRF_writeReg(0x10, txName, NAME_LEN);         // set TX name

    NRF_writeReg8(0x11, BYTES_IN_FRAME);             // set bytes in pipe
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

    NRF_config();
}

void NRF_TxMode(void)
{
    uint8_t reg = NRF_readReg(0x00);
    reg &= ~(1<<0);                                 // set PRIM_RX to 0
    NRF_writeReg8(0x00, reg);
    setCELow();
    sleep_us(130u);
}

void NRF_RxMode(void)
{
    uint8_t reg = NRF_readReg(0x00);
    reg |= (1<<0);                                  // set PRIM_RX to 1
    NRF_writeReg8(0x00, reg);
    setCEHigh();
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
    sleep_us(300u);
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
    status = !(status & 0b00000001);

    return status;
}

uint8_t NRF_check(void)
{
    uint8_t status = NRF_readReg(0x07);
    status = (status & 0b01100000);

    return status;
}
