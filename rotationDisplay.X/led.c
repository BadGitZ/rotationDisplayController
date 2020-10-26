/*
 * led.c
 *
 * Created: 29.07.2020
 * Author : Badgitz
 */ 

#include "led.h"

led_t led[LEDCOUNT];

//Initializes SPI for DotStar-Communication
static void spiInit(void) {
    //B2, B1 -> CLK, MOSI/DO
    DDRB |= (1 << DDB2)|(1 << DDB1);
    //Init USI Mode to SPI
    USICR &= ~((1 << USISIE)|(1 << USIOIE)|(1 << USIWM1));
    USICR |= (1 << USIWM0)|(1 << USICS1)|(1 << USICLK);
}

//SPI tx without rx
static void spiTransfer(uint8_t databyte) {
    //Load Data Register
    USIDR = databyte;
    //Clear Counter
    USISR |= (1 << USIOIF);
	
    //Clocking the Data out
    while (!(USISR & (1 << USIOIF))) {
	USICR |= (1 << USITC);
    }
    (void)USIDR;	//dump rx
}

void initializeLeds(void) {
    //initialize SPI Peripheral
    spiInit();
    //initialize all LEDs
    for (uint8_t i = 0; i < LEDCOUNT; i++) {
	setLed(i, 0x00, 0x00, 0x00, 0x00);
    }
}

void updateLeds(void) {
    //start frame
    spiTransfer(0x00);
    spiTransfer(0x00);
    spiTransfer(0x00);
    spiTransfer(0x00);
    //led frames
    for (uint8_t i = 0; i < LEDCOUNT; i++) {
        spiTransfer(0xE0 | led[i].brightness);
	spiTransfer(led[i].blue);
	spiTransfer(led[i].green);
	spiTransfer(led[i].red);
    }
    //update frame
    spiTransfer(0x00);
    spiTransfer(0x00);
    spiTransfer(0x00);
    spiTransfer(0x00);
}

//set individual LED values
void setLed(uint8_t address, uint8_t brightness, uint8_t red, uint8_t green, uint8_t blue) {
    led[address].brightness = brightness;
    led[address].red = red;
    led[address].green = green;
    led[address].blue = blue;
}

void increaseAllLeds(uint8_t redincrement, uint8_t greenincrement, uint8_t blueincrement) {
  for (uint8_t i = 1; i < LEDCOUNT; i++) {
      if (led[i].red < 255)
        led[i].red += redincrement;
      if (led[i].green < 255)
        led[i].green += greenincrement;
      if (led[i].blue < 255)
        led[i].blue += blueincrement;
    }
}

void decreaseAllLeds(uint8_t reddecrement, uint8_t greendecrement, uint8_t bluedecrement) {
  for (uint8_t i = 1; i < LEDCOUNT; i++) {
      if (led[i].red > 0)
        led[i].red -= reddecrement;
      if (led[i].green > 0)
        led[i].green -= greendecrement;
      if (led[i].blue > 0)
        led[i].blue -= bluedecrement;
    }
}

//sets all Led values except for the control led
void setAllLeds(uint8_t brightness, uint8_t red, uint8_t green, uint8_t blue) {
    for (uint8_t i = 1; i < LEDCOUNT; i++) {
        led[i].brightness = brightness;
        led[i].red = red;
        led[i].green = green;
        led[i].blue = blue;
    }
}