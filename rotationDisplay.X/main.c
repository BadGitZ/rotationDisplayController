/*
 * rotationDisplayController
 *
 * main.c
 *
 * ATtiny85 as Controller for model display stand with rotating table and RGB-lighting
 *
 * Created: 28.06.2020 18:44:23
 * Author : Badgitz
 */ 

#include "main.h"
#include "led.h"
#include "motor.h"
#include "timing.h"

static void ADCInit();
static void getButtonValues();
static buttons_t getJoyState();
static void processInput(buttons_t button);
static bool checkStartButton();

float adcStep = 0.01953;  // (0-5V over 256 values)

float middleButton = 0;
float upButton = 0;
float rightButton = 0;
float downButton = 0;
float leftButton = 0;

//Initializes the ADC peripheral
static void ADCInit() {  
    //B3 ADC Pin for 5 Buttons
    ADMUX |= (1 << ADLAR) | (1 << MUX1) | (1 << MUX0);	//Left shift Result and ADC3
    ADCSRA |= (1 << ADEN) | (1 << ADPS1) | (1 << ADPS0);	//Enable ADC and set Prescaler to 8
	
    //initial Conversion for Checkup
    ADCSRA |= (1 << ADSC);         // start ADC Conversion
    while (ADCSRA & (1 << ADSC)); // wait till Conversion complete
    (void)ADCH;	//dump first conversion
}

//Determines if joystick is used and returns the direction
static buttons_t getJoyState() {
  float voltage = 0;

  //5 Conversions with averaging
  for (uint8_t i = 0; i < 5; i++) {
    ADCSRA |= (1 << ADSC);	//restart Conversion
    while (ADCSRA & (1 << ADSC));
    voltage = voltage + ADCH * adcStep;
  }
  voltage = voltage / 5;    //average
  
  buttons_t pressedButton = none;
  
  if (voltage >= middleButton - 0.1 && voltage <= middleButton + 0.1) {
      pressedButton = middle;
  }
  else if (voltage >= upButton - 0.1 && voltage <= upButton + 0.1) {
      pressedButton = up;
  }
  else if (voltage >= rightButton - 0.1 && voltage <= rightButton + 0.1) {
      pressedButton = right;
  }
  else if (voltage >= downButton - 0.1 && voltage <= downButton + 0.1) {
      pressedButton = down;
  }
  else if (voltage >= leftButton - 0.1 && voltage <= leftButton + 0.1) {
      pressedButton = left;
  }
  
  return pressedButton;
}

//executes User Input
static void processInput(buttons_t button) {
  
  switch(button) {
    case middle:
      setAllLeds(3, 255, 0, 0);
      updateLeds();
      break;
    case up:
      setAllLeds(3, 0, 255, 0);
      updateLeds();
      break;
    case right:
      setAllLeds(3, 0, 0, 255);
      updateLeds();
      break;
    case down:
      setAllLeds(3, 0, 255, 255);
      updateLeds();
      break;
    case left:
      setAllLeds(3, 255, 255, 0);
      updateLeds();
      break;
    default:
      break;
  }
}

//checks if the User wants to calibrate the analog button values on startup
static bool checkStartButton() {
    //checking if button is pressed on controller startup
    
    float voltage = 0;        // real battery voltage (0-5V) with decimals
  
    uint32_t ticks = getTick();
    
    //getting ADC values for one second
    while(getTick() - ticks < 100) {
        ADCSRA |= (1 << ADSC);	
        while (ADCSRA & (1 << ADSC));
        voltage = voltage + (((ADCH * adcStep) - voltage) / 15);  // integrated last 15-sample rolling average
    }
  
    if (voltage > 0.01) {
        return true;
    }
    return false;
}

//blocking millisecond waitfunction
void waitTicks(uint32_t ticks) {
    uint32_t waitTicks = getTick();
    while(getTick() - waitTicks <= ticks);
}

//Blocking Setup Function to determine Button ADC Values
static void configureButtonValues() {
    uint32_t ticks = 0;
    float voltage = 0;
    float* pButtonVoltage = 0;
    
    //make Setup mode visible
    setAllLeds(3, 255, 255, 255);
    updateLeds();
  
    waitTicks(5000);
    //doing the measurements
    for (buttons_t currentButton = middle; currentButton < none; currentButton++) {
        voltage = 0;
        setAllLeds(3, 0, 0, 0);
        updateLeds();
        waitTicks(5000);
        switch (currentButton) {
          case middle:
            setAllLeds(3, 255, 0, 0);
            pButtonVoltage = (float*)(MIDDLE_BUTTON_EEPADDR);
            break;
          case up:
            setAllLeds(3, 0, 255, 0);
            pButtonVoltage = (float*)(UP_BUTTON_EEPADDR);
            break;
          case right:
            setAllLeds(3, 0, 0, 255);
            pButtonVoltage = (float*)(RIGHT_BUTTON_EEPADDR);
            break;
          case down:
            setAllLeds(3, 0, 255, 255);
            pButtonVoltage = (float*)(DOWN_BUTTON_EEPADDR);
            break;
          case left:
            setAllLeds(3, 255, 255, 0);
            pButtonVoltage = (float*)(LEFT_BUTTON_EEPADDR);
            break;
          default:
            break;
        }
        updateLeds();
        ticks = getTick();
        while(getTick() - ticks < 1000) {
            ADCSRA |= (1 << ADSC);	//restart Conversion
            while (ADCSRA & (1 << ADSC));
            voltage = voltage + (((ADCH * adcStep) - voltage) / 15);  // integrated last 15-sample rolling average
        }
        eeprom_write_float(pButtonVoltage, voltage);
    }
}

//gets analog values from eeprom
static void getButtonValues() {
   middleButton = eeprom_read_float((float*)(MIDDLE_BUTTON_EEPADDR));
   upButton = eeprom_read_float((float*)(UP_BUTTON_EEPADDR));
   rightButton = eeprom_read_float((float*)(RIGHT_BUTTON_EEPADDR));
   downButton = eeprom_read_float((float*)(DOWN_BUTTON_EEPADDR));
   leftButton = eeprom_read_float((float*)(LEFT_BUTTON_EEPADDR));
}

int main(void)
{
    hwTimerInit();
    initializeLeds();
    initialzeMotor();
    ADCInit();
	
    //if Values need to be configured
    if (checkStartButton()) {
        configureButtonValues();
    }
    getButtonValues();
    
    //return to normal operation
    startMotor();
	
    setLed(0, 1, 1, 1, 1);
    updateLeds();
	
    uint32_t counter = getTick();
    while (1) 
    {
        processInput(getJoyState());
 	updateMotor();
		
	if (getTick() - counter >= 1000) {
            counter = getTick();     
	}
    }
}

/*
 * Joystick 
 * 
up = motor clock/stop
down = motor counterclock/stop
left = motor slower
right = motor faster

middle = led mode
right = rgb select
left = cycle mode
down = brightness
up = dimming mode 
*/