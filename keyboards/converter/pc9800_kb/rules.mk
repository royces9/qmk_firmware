# This file intentionally left blank

MCU=atmega32u4
F_CPU=16000000
BOOTLOADER=halfkay

CUSTOM_MATRIX = yes

SRC+=setup_pc9800_kb.c
SRC+=uart.c
SRC+=matrix.c


