/*
 * motor.c
 *
 * Created: 29.07.2020 22:19:27
 *  Author: Badgitz
 */ 

#include "motor.h"

motor_t displayMotor;

//Initializes PWM for Motor-Control
static void pwmInit(void) {
    DDRB |= (1 << DDB4);
    TCCR1 |= 1<<CS10;	//No Prescaler
    GTCCR |= (1 << PWM1B) | (1 << COM0B1);	//PWM-Mode on PB4, PB3 free	
    OCR1C = 0xFF;	//Counter reload
    OCR1B = 0x0;	//Pulse on this value
}

void initialzeMotor(void) {
    //PWM for motor speed
    pwmInit();
    //Pin 0 for motor direction
    DDRB |= (1 << DDB0);
    PORTB |= (1 << PB0);
	
    displayMotor.speed = 10;
    displayMotor.currentSpeed = 0;
    displayMotor.direction = clockwise;
    displayMotor.isRunning = false;
    displayMotor.isReversing = false;
    timer_init(&displayMotor.motorTimer, 10);
}

void startMotor(void) {
    if (!displayMotor.isRunning) {
	displayMotor.isRunning = true;
	timer_start(&displayMotor.motorTimer);
    }
}

void stopMotor(void) {
    if (displayMotor.isRunning) {
	displayMotor.isRunning = false;
    }
}

void reverseMotor(void) {
    displayMotor.isReversing = true;
}

void changeMotorSpeed(uint8_t speed) {
    displayMotor.speed = speed;
}

bool isMotorRunning(void) {
  return displayMotor.isRunning;
}

bool isMotorCounterclock(void) {
  return displayMotor.direction;
}

uint8_t getMotorSpeed(void) {
    return displayMotor.speed;
}

volatile timer_t* getMotorTimer(void) {
    return &displayMotor.motorTimer;
}

void updateMotor(void) {
    if (is_timer_down(&displayMotor.motorTimer)) {
	if (displayMotor.isRunning) {
            //breaking to 0 and Reversing polarity
            if (displayMotor.isReversing) {
		if (displayMotor.currentSpeed == 0) {
                    if (displayMotor.direction == clockwise) {
                        PORTB |= (1 << PB0);
			displayMotor.direction = counterclockwise;
                    }
                    else {
                        PORTB &= ~(1 << PB0);
			displayMotor.direction = clockwise;
                    }		
                    displayMotor.isReversing = false;
                }
		else {
                    displayMotor.currentSpeed--;
                    OCR1B = displayMotor.currentSpeed;
		}
            }
            //accelerating to desired Speed
            else if (displayMotor.currentSpeed < displayMotor.speed) {
                displayMotor.currentSpeed++;
		OCR1B = displayMotor.currentSpeed;
            }
            timer_start(&displayMotor.motorTimer);
        }
        //Motor not stopped yet
        else {
            if(displayMotor.currentSpeed != 0) {
                displayMotor.currentSpeed--;
                OCR1B = displayMotor.currentSpeed;
                timer_start(&displayMotor.motorTimer);
            }
            else timer_stop(&displayMotor.motorTimer);
        }
    }
}

