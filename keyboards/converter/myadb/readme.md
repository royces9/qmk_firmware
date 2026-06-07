# Apple ADB keyboard USB converter

A USB converter for Apple's ADB keyboards. The keyboard doesn't need to be dissassembled; a compatible mini-DIN 4 cable can be used to attach the keyboard to the converter for use via USB.

## Implementation details

The main source of information I used is the "Guide to the Macintosh® Family Hardware, Second Edition".

### Connector ー mini-DIN 4

#### KB pins

Female socket pins on KB side.
```
  -----
 / 4 3 \
( 2   1 )
 \     /
  -----
```

| Pin # | Name             | Additional info |
|-------|------------------|-----------------|
| 1     | Apple Device Bus | Data            |
| 2     | Power on         | Unused.         |
| 3     | 5V               |                 |
| 4     | Ground           |                 |

### Protocol

The data frame is structured as below:

```
_____              _____________________________________________________________________     ____ _ _ _ ____   __________ _ _ _ ____     _____
     |             |   |       |       |       |       |       |       |       |       |     |             |   |     |             |     |
     |             |   |       |       |       |       |       |       |       |       |     |             |   |     |             |     |
     |             |   |       |       |       |       |       |       |       |       |     |             |   |     |             |     |
     |             |   |       |       |       |       |       |       |       |       |     |             |   |     |             |     |
     |___ _ _ _ ___|   |_______|_______|_______|_______|_______|_______|_______|_______|_____|             |___|     |___ _ _ _ ___|_____|
     
     ^                 ^                               ^               ^               ^         ^         ^         ^             ^
     |                 |                               |               |               |         |         |         |             |
     |    Attention    |                               |               |               |         | Stop-to |  Start  |             | Stop
     |____and Sync_____|_________Device address________|_Command code__|_Register code_|__Stop___|_start___|__bit____|_Data bytes__|_bit______
                       |                                                               |
                       |__________________________Command byte_________________________|

```


```
| Device Address bits   |  Command  | Register  |           |
|  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |  Command  |
-------------------------------------------------------------
|  x  |  x  |  x  |  x  |  0  |  0  |  0  |  0  | SendReset |
|  A3 |  A2 |  A1 |  A0 |  0  |  0  |  0  |  1  | Flush     |
|  x  |  x  |  x  |  x  |  0  |  0  |  1  |  0  | Reserved  |
|  x  |  x  |  x  |  x  |  0  |  0  |  1  |  1  | Reserved  |
|  x  |  x  |  x  |  x  |  0  |  1  |  x  |  x  | Reserved  |
|  A3 |  A2 |  A1 |  A0 |  1  |  0  |  r1 |  r0 | Listen    |
|  A3 |  A2 |  A1 |  A0 |  1  |  1  |  r1 |  r0 | Talk      |
```


#### Attention and Sync

Every command starts with `Attention` and `Sync`.
`Attention` 800μs low followed by a `Sync` of 65μs high.


#### Bit-cell

Each bit is encoded in a bit-cell. Every bit-cell has a low signal, rising edge, high signal, and a falling edge.
`0` and `1` are distinguished by the lengths of the low and high signals.

| Bit-cell time | 0 low time           | 1 low time           |
|---------------|----------------------|----------------------|
|     100μs     | 65% of bit-cell time | 35% of bit-cell time |


```
Logical 0
_     _____
|     |   |
|     |   |
|     |   |
|     |   |
|_____|   |

^     ^   ^
|     |   |
|     |   |

Logical 1
_   _______
|   |     |
|   |     |
|   |     |
|   |     |
|___|     |

^   ^     ^
|   |     |

```