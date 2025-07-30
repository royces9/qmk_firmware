# pc9800_kb

A converter for the NEC PC-9800 series keyboards. The keyboard doesn't need to be dissassembled; the attached mini-DIN 8 cable can be plugged into the converter for use via USB.
A breakout board/cable helps with this!


Make example for this keyboard (after setting up your build environment):

    make converter/pc9800_kb_rp2040:default

Flashing example for this keyboard:

    make converter/pc9800_kb_rp2040:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).


## Hardware setup
# Hardware used
* [Teensy 2.0] (https://www.pjrc.com/store/teensy.html) ※
* [DIN breakout board](https://booth.pm/ja/items/3534917)

※ The keyboard for the PC9800 requires 5V for data high. Newer Teensy boards (3.x, 4.x) have 3.3V, which may or may not work. I haven't tested it. 

The following pins assume usage of the Teensy 2.0. A different board/chip should work, with some work.

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

