/*
 * motor.h
 *
 * Created: 29.07.2020
 *  Author: Badgitz
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

#include <avr/io.h>
#include <stdbool.h>
#include "timing.h"

typedef enum {
	clockwise,
	counterclockwise
} motor_direction_t;

typedef struct {
	uint8_t speed;
	uint8_t currentSpeed;
	motor_direction_t direction;
	bool isRunning;
	bool isReversing;
	volatile timer_t motorTimer;
} motor_t;

void initialzeMotor(void);
void startMotor(void);
void stopMotor(void);
void reverseMotor(void);
void changeMotorSpeed(uint8_t speed);
uint8_t getMotorSpeed(void);
volatile timer_t* getMotorTimer(void);
bool isMotorRunning(void);
bool isMotorCounterclock(void);

void updateMotor(void);

#endif /* MOTOR_H_ */