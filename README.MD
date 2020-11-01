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