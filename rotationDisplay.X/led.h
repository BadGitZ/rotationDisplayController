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
#define LEDCOUNT 1

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

#endif /* __LED_H */