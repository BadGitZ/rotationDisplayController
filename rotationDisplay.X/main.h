/*
 * main.h
 *
 * Created: 29.07.2020
 * Author : Badgitz
 */ 

#ifndef __MAIN_H
#define __MAIN_H

#include <avr/io.h>
#include <avr/eeprom.h>
#include <stdbool.h>

#define MIDDLE_BUTTON_EEPADDR 0x00
#define UP_BUTTON_EEPADDR 0x04
#define RIGHT_BUTTON_EEPADDR 0x08
#define DOWN_BUTTON_EEPADDR 0x0C
#define LEFT_BUTTON_EEPADDR 0x10

typedef enum {
    middle = 0,
    up,
    right,
    down,
    left,
    none
} buttons_t;

void waitTicks(uint32_t ticks);

#endif /* __MAIN_H */