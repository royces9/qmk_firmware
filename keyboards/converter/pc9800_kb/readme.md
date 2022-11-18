# pc9800_kb

![pc9800_kb](imgur.com image replace me!)

*A short description of the keyboard/project*
A converter for the NEC PC-9800 series keyboards. The keyboard doesn't need to be dissassembled; the attached mini-DIN 8 cable can be plugged into the converter for use via USB.
A breakout board/cable helps with this!


* Keyboard Maintainer: [Royce Sato](https://github.com/royces9)
* Hardware Supported: *The PCBs, controllers supported*
* Hardware Availability: *Links to where you can find this hardware*

Make example for this keyboard (after setting up your build environment):

    make converter/pc9800_kb:default

Flashing example for this keyboard:

    make converter/pc9800_kb:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

## Hardware setup
I used a teensy 2.0, so the following instructions will assume the same. A different board/chip should work, with some work.

The mini-DIN 8 cable on the keyboard has a total of 8 pins, of which 6 are used.

They can be connected as follows:
| Pin # | Name | Teensy port |
|---|---|---|
| 1 | RST | D7 |
| 2 | Ground | Ground |
| 3 | RDY | D6 |
| 4 | RXD | D2 |
| 5 | RTY | D0 |
| 6 | NC | None |
| 7 | NC | None |
| 8 | 5V | Vcc |

The firmware can be flashed, and the keyboard should work normally.


## Implementation details
The main source of information I used is the 「PC-9800シリーズ テクニカルデータブック HARDWARE編」.
The keyboard sends serial data through the RXD pin (pin 4), with a baud rate of 19200 kb/s.
Data frames have a start bit, 8 bits of data, a parity bit, and a stop bit.
The parity bit is odd.

Setting the RDY pin to low tells the keyboard that the receiver is ready to receive data, the RDY is then set to high when handling the frame.
Once the frame is done being processed, the RDY pin is set back to low. The action of the RDY going from 1 to 0, lets the keyboard know to send another frame if ready.

When the RTY pin is low, it tells the keyboard to resend the last code it sent. The firmware as it is keeps the RTY pin high.

The RST pin sets the keyboard to a starting state. It must be set low for at least 13us to reset the keyboard. The firmware keeps the RST pin high.

Data is 8 bits, with the first 7 bits forming the keycode, and the last bit denoting either make (0, key press) or break (1, key release).

