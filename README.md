# bike-speedometer
Arduino-based simple bike speedometer

# specs

## hardware

* Trinket 5v [purchase](https://www.adafruit.com/product/1501)
* Hall Sensor [purchase](https://www.amazon.com/New-Hall-Sensor-Module-Arduino/dp/B009M86TFG/ref=sr_1_2?ie=UTF8&qid=1493972745&sr=8-2&keywords=arduino+hall+sensor)
* 4x7 LED Segment display [purchase](https://www.sparkfun.com/products/9481)
* 74HC595 shift register (2x) [purchase](https://www.adafruit.com/product/450)

## multiplexed 4x7

Mapped pin-out.
```sh
  Type      Seg Pin   Reg Pin
  ----      -------   -------
  Digit 1   1 pin     9 pin
  Digit 2   2 pin     10 pin
  Digit 3   6 pin     11 pin
  Digit 4   8 pin     12 pin
  Seg A     14 pin    1 pin
  Seg B     16 pin    2 pin
  Seg C     13 pin    3 pin
  Seg D     3 pin     4 pin
  Seg E     5 pin     5 pin
  Seg F     11 pin    6 pin
  Seg G     15 pin    7 pin
  DP        7 pin     -
```

# install using adruino IDE
1. Launch Arduino IDE.
2. Load the sketch.
3. Select `Tools > Board > Adafruit Trinket 8MHz`.
4. Select `Tools > Programmer > USBtinyISP`.
5. Start the bootloader [info](https://learn.adafruit.com/introducing-trinket/introduction?embeds=allow&view=all#starting-the-bootloader).
6. Click `Upload` (arrow button).
