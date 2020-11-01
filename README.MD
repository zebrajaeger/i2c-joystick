# I2C Joystick

## Prepare Arduino Nano

### Flash fuses with arduino isp

``` bash
apt install avrdude
```

Read/check fuse
``` bash
avrdude -p m328p -P /dev/ttyUSB0 -b 19200 -c avrisp -U efuse:r:a
```

Write Fuse
``` bash
avrdude -p m328p -P /dev/ttyUSB0 -b 19200 -c avrisp -U lfuse:w:0xBF:m
```

## I²C

- Address is 0x30
- read only, 4 Bytes in row
    - 16 Bit per channel but only 12 Bits are used.
    - LSB first

| Byte / Bit | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| 0 | X_0 | X_1 | X_2 | X_3 | X_4 | X_5 | X_6 | X_7 |
| 1 | X_8 | X_9 | X_A | x_B | 0 | 0 | 0 | 0 |
| 2 | Y_0 | Y_1 | Y_2 | Y_3 | Y_4 | Y_5 | Y_6 | Y_7 |
| 3 | Y_8 | Y_9 | Y_A | Y_B | 0 | 0 | 0 | 0 |



## Hardware

// TODO Schematic, Image

- Arduino Nano
- Analog magnetic joystick
- 3.3V Linear voltage regulator

- Input Voltage ~7.5...12V on Arduino Vin.
- Arduino 5V to the 3.3V regulator input. 
- The Joystick is powered by 3.3V (important!).
- Joystick output voltages to Arduino input pins : A0, A1
- I2C pins: A5(SCL), A4(SDA)
- Arduino ref (reference input voltage for ADC) is connected to 3.3V