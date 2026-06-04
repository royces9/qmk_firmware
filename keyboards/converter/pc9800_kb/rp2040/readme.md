# NEC PC-9800 keyboard USB converter

A usb converter for the NEC PC-9800 series keyboards. The keyboard doesn't need to be dissassembled; the attached mini-DIN 8 cable can be plugged into the converter for use via USB.

## Make and flash example

### Make

```
make converter/pc9800_kb_rp2040:default
```

### Flash

```
mount /dev/ /mnt
cp output.uf2 /mnt/
umount /dev/
```

## Hardware setup

The following hardware were used:
* [RP2040-Zero] (https://www.waveshare.com/rp2040-zero.htm)
* [DIN breakout board](https://booth.pm/ja/items/3534917)
* [TI SN74HC08N](https://www.ti.com/product/SN74HC08/part-details/SN74HC08N)
* 10kΩ resistor
* 5.6kΩ resistor※

※ Any resistor around 5kΩ should work fine

## Settings

The pins are set as follows:

| KB Pin # | Name    | RP2040-Zero Pin # | Note        |
|----------|---------|-------------------|-------------|
| 1        | RST     | 15                |             |
| 2        | Ground  | GND               |             |
| 3        | RDY     | 14                |             |
| 4        | RXD     | 1                 | UART RX pin |
| 5        | RTY     | 8                 |             |
| 6        | NC      | -                 |             |
| 7        | NC      | -                 |             |
| 8        | 5V      | 5V                |             |

※ The keyboard for the PC9800 asks for 5V and outputs 5V from the `RXD` pin. I haven't tested with 3.3V.

