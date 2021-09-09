# QUADCOPTER

## BUILD 
- create build directory `mkdir build`
- go to build directory `cd build`
- export absolut path to pico-sdk `export PICO_SDK_PATH=absolut_path/pico-sdk`
- prepare make files `cmake ..`
- build project `make`

## NRF lib 101
- init with `NRF_init()`
- choose mode TX or RX `NRF_TxMode()`, `NRF_RxMode()`
- if TX, send buffer with `NRF_sendMsg()`
- if RX, first check if there is new message `NRF_newMsg()`, then fill buffer with data from `NRF_readMsg()`