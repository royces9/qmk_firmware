# NEC PC-9800 keyboard USB converter

A usb converter for the NEC PC-9800 series keyboards. The keyboard doesn't need to be dissassembled; the attached mini-DIN 8 cable can be plugged into the converter for use via USB.

## Implementation details

The main source of information I used is the 「PC-9800シリーズ テクニカルデータブック HARDWARE編」.

### Connector ー mini-DIN 8

The mini-DIN 8 cable on the keyboard has a total of 8 pins, of which 6 are used.


#### KB cable pins
```
  -----
 /6 7 8\
( 3 4 5 )
 \ 1 2 /
  -----
```

| Pin # | Name   | Additional info |
|-------|--------|-----------------|
| 1     | RST    | Reset. When held low for >13μs, resets KB.|
| 2     | Ground | |
| 3     | RDY    | Ready. Signal to tell the KB if data is ready to be recieved. Low is ready. High is not ready. |
| 4     | RXD    | Serial data line. |
| 5     | RTY    | Retry. When low, resend most recent data. |
| 6     | NC     | Unused. |
| 7     | NC     | Unused. |
| 8     | 5V     | |

### Protocol

| Baud rate  | Data size | Start bit | Stop bit | Parity bit |
|------------|-----------|-----------|----------|------------|
| 19200 kb/s | 8 bits    | 1 bit     | 1 bit    | 1 bit, odd |

The data frame is structured as below:

```
______        _______________________________________________________________________
      |       |      |      |      |      |      |      |      |      |      |
      | start | data | data | data | data | data | data | data | data | par- | stop
      |  bit  | bit0 | bit1 | bit2 | bit3 | bit4 | bit5 | bit6 | bit7 | ity  | bit
      |       |      |      |      |      |      |      |      |      | bit  |
      |_______|______|______|______|______|______|______|______|______|______|
```

The least significant bit is sent first.

`data bit7` is the `make` bit.

| Value | Name  | Action      |
|-------|-------|-------------|
| 0     | make  | key press   |
| 1     | break | key release |


#### General flow

##### RDY
The `RDY` pin controls when the keyboard sends data.

`RDY` is set to low to tell the keyboard that data is ready to be received.
`RDY` is set to high after receiving data from `RXD`, and is then being processed.
`RDY` is set back to low when input is done being handled. ※

※ `RDY` can not be set back to low too quickly, or the keyboard may stall. A ~4μs delay should be put between setting `RDY` low and setting it back high. 

##### RST

The `RST` pin resets the keyboard. It must be set low for at least 13μs to reset the keyboard.

##### RTY

The `RTY` pin tells the keyboard to resend the last code it sent.
When set to low, the last keycode the keyboard is resent.

