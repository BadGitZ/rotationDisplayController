/*
 * timing.h
 *
 * Created: 08.08.2020 17:55:10
 *  Author: Badgitz
 */ 


#ifndef TIMING_H_
#define TIMING_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

// Timer Status
#define TIMER_STATUS_RUN	0x00
#define TIMER_STATUS_STOP	0x01

typedef struct {
	uint32_t start_value;
	uint32_t current_value;
	uint8_t status;
} timer_t;

void hwTimerInit(void);
uint32_t getTick(void);
void timer_init ( volatile timer_t *timer, uint32_t start_value );
void timer_start ( volatile timer_t *timer );
void timer_stop ( volatile timer_t *timer );
void timer_tick ( volatile timer_t *timer );
uint8_t is_timer_down ( volatile timer_t *timer );
uint8_t is_timer_running ( volatile timer_t *timer );

#endif /* TIMING_H_ */