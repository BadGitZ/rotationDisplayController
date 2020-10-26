/*
 * led.h
 *
 * Created: 29.07.2020
 * Author : Badgitz
 */ 

#ifndef __LED_H
#define __LED_H

#include <avr/io.h>

//Definitons
#define LEDCOUNT 20

typedef struct {
	uint8_t brightness;
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} led_t;

void initializeLeds(void);
void updateLeds(void);
void setLed(uint8_t address, uint8_t brightness, uint8_t red, uint8_t green, uint8_t blue);
void setAllLeds(uint8_t brightness, uint8_t red, uint8_t green, uint8_t blue);
void increaseAllLeds(uint8_t redincrement, uint8_t greenincrement, uint8_t blueincrement);
void decreaseAllLeds(uint8_t reddecrement, uint8_t greendecrement, uint8_t bluedecrement);

#endif /* __LED_H */