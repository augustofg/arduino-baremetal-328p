# Baremetal Template for ATMEGA-328P Targets

## Requirements
1. make
1. binutils-avr
1. avr-gcc
1. avr-libc
1. avrdude

## Usage
All source files must be in the `src/` directory. To build the final binary, just type `make`:
```bash
$ make
avr-gcc -MMD -c -Wall -gdwarf-2 -O2 -mmcu=atmega328p -DF_CPU=16000000 src/main.c -o src/main.o
avr-gcc -Wall -gdwarf-2 -O2 -mmcu=atmega328p -DF_CPU=16000000 src/main.o   -o bare-328p.elf -Wl,-Map,bare-328p.map
avr-objcopy -R .eeprom -O ihex "bare-328p.elf" "bare-328p.hex"
```

To program an Arduino UNO or compatibles (ATMEGA-328P based), type `make flash PGPORT=/dev/ttyACM0` where the `PGPORT=...` specifies the serial port device associated with the Arduino target:
```bash
$ make flash PGPORT=/dev/ttyACM0
avrdude -c arduino -p atmega328p -P /dev/ttyUSB2 -B 57600 -u -U flash:w:"bare-328p.hex"
```
