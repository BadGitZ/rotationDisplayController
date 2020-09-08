/*
 * timing.c
 *
 * Created: 08.08.2020 17:54:53
 *  Author: Badgitz
 */ 

#include "timing.h"
#include "motor.h"

uint32_t ms_tick = 0;
timer_t* motorTimer;

ISR(TIMER0_COMPA_vect) {
    ms_tick++;
    timer_tick(getMotorTimer());
}

void hwTimerInit(void) {
    TCCR0A |= (1 << WGM01);	//Compare Match CTC
    TCCR0B |= (1 << CS01);	//Prescaler 8
    OCR0A = 125 - 1;	// (CLK/Prescaler)/1000 = 125
    TIMSK |= (1 << OCIE0A);	//Enable Timer Interrupt
	
    //enable Interrupts
    sei();
}

uint32_t getTick() {
    return ms_tick;
}

void timer_init ( volatile timer_t *timer, uint32_t start_value ) {
    timer->start_value = start_value;
    timer_stop ( timer );
}

void timer_start ( volatile timer_t *timer ) {
    timer->current_value = timer->start_value;
    timer->status = TIMER_STATUS_RUN;
}

void timer_stop ( volatile timer_t *timer ) {
    timer->status = TIMER_STATUS_STOP;
    timer->current_value = 1;
}

void timer_tick (volatile timer_t *timer ) {
    if ( timer->status == TIMER_STATUS_RUN ) {
	timer->current_value--;
	if ( timer->current_value == 0 )
	timer->status = TIMER_STATUS_STOP;
    }
}

uint8_t is_timer_down ( volatile timer_t *timer ) {
    if ( timer->status == TIMER_STATUS_STOP )
        if ( timer->current_value == 0 ) {
            return true;
        }
    return false;
}

uint8_t is_timer_running ( volatile timer_t *timer ) {
    if ( timer->status != TIMER_STATUS_STOP )
        if ( timer->current_value > 0 ) {
            return true;
	}
    return false;
}
