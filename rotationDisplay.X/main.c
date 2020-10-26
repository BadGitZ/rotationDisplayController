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

bool ledMode = false;

uint8_t rgbEffect = 0;
uint8_t rgbSelect = 0;

timer_t debounceTimer;

volatile timer_t* getdebounceTimer(void) {
  return &debounceTimer;
}

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
static void processInput (buttons_t button)
{
  if (is_timer_down (&debounceTimer))
    {
      switch (button)
        {
          //changes between led mode and motor mode ----------------------------
        case middle:
          if (ledMode)
            {
              ledMode = false;
              if (isMotorRunning ())
                {
                  if (isMotorCounterclock ())
                    {
                      setLed (0, 1, 0, 0, 10);
                    }
                  else
                    {
                      setLed (0, 1, 0, 10, 0);
                    }
                }
              else
                {
                  setLed (0, 1, 10, 0, 0);
                }
              updateLeds ();
            }
          else
            {
              ledMode = true;
              setLed (0, 3, 255, 255, 255);
              updateLeds ();
            }
          break;
          //starts Motor Clockwise and Brightness up ---------------------------
        case up:
          if (ledMode)
            {
              switch(rgbSelect) {
                case 0:
                  increaseAllLeds (1, 1, 1);
                  break;
                case 1:
                  increaseAllLeds (1, 0, 0);
                  break;
                case 2:
                  increaseAllLeds (0, 1, 0);
                  break;
                case 3:
                  increaseAllLeds (0, 0, 1);
                  break;
                default:
                  break;
              }
              updateLeds ();
            }
          else
            {
              startMotor ();
              if (isMotorCounterclock ())
                {
                  reverseMotor ();
                  setLed (0, 1, 0, 255, 0);
                  updateLeds ();
                }
              else
                {
                  stopMotor();
                  setLed (0, 1, 255, 0, 0);
                  updateLeds ();
                }
            }
          break;
          //accelerates Motor and rgb Selection --------------------------------
        case right:
          if (ledMode)
            {
              rgbSelect++;
              if (rgbSelect > 3) {
                  rgbSelect = 0;
              } 
            }
          else
            {
              changeMotorSpeed (getMotorSpeed () + 5);
            }
          break;
          //start Motor counterclockwise and Brightness down -------------------
        case down:
          if (ledMode)
            {
              switch(rgbSelect) {
                  case 0:
                    decreaseAllLeds (1, 1, 1);
                    break;
                  case 1:
                    decreaseAllLeds (1, 0, 0);
                    break;
                  case 2:
                    decreaseAllLeds (0, 1, 0);
                    break;
                  case 3:
                    decreaseAllLeds (0, 0, 1);
                    break;
                  default:
                    break;
              }
              updateLeds ();
            }
          else
            {
              startMotor ();
              if (!isMotorCounterclock ())
                {
                  reverseMotor ();
                  setLed (0, 1, 0, 0, 255);
                  updateLeds ();
                }
              else
                {
                  stopMotor ();
                  setLed (0, 1, 255, 0, 0);
                  updateLeds ();
                }
            }
          break;
          //decrease Motor speed and LED Mode Change ---------------------------
        case left:
          if (ledMode)
            {
              setAllLeds (1, 255, 255, 0);
              updateLeds ();
            }
          else
            {
              changeMotorSpeed (getMotorSpeed () - 5);
            }
          break;

        default:
          break;
        }
      timer_start(&debounceTimer);
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
    setLed(0, 3, 255, 255, 255);
    updateLeds();
  
    waitTicks(5000);
    //doing the measurements
    for (buttons_t currentButton = middle; currentButton < none; currentButton++) {
        voltage = 0;
        setLed(0, 3, 0, 0, 0);
        updateLeds();
        waitTicks(5000);
        switch (currentButton) {
          case middle:
            setLed(0, 3, 255, 0, 0);
            pButtonVoltage = (float*)(MIDDLE_BUTTON_EEPADDR);
            break;
            
          case up:
            setLed(0, 3, 0, 255, 0);
            pButtonVoltage = (float*)(UP_BUTTON_EEPADDR);
            break;
            
          case right:
            setLed(0, 3, 0, 0, 255);
            pButtonVoltage = (float*)(RIGHT_BUTTON_EEPADDR);
            break;
            
          case down:
            setLed(0, 3, 0, 255, 255);
            pButtonVoltage = (float*)(DOWN_BUTTON_EEPADDR);
            break;
            
          case left:
            setLed(0, 3, 255, 255, 0);
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
    	
    setLed(0, 1, 10, 0, 0);
    setAllLeds (1, 0, 0, 0);
    updateLeds();
    
    timer_init (&debounceTimer, 250);
    timer_start (&debounceTimer);
    
    uint32_t counter = getTick();
    while (1) 
    {
        processInput(getJoyState());
 	updateMotor();
		
	if (getTick() - counter >= 1000) {
            counter = getTick();     
            //PINB |= (1 << PB0);
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
left = change effect -> normal, cycle, rainbow, dimming
down = brightness down
up =  brightness up
*/