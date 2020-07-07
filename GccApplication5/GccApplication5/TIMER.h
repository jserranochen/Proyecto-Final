/*
 * TIMER.h
 *
 * Created: 2/03/2019 16:24:16
 *  Author: marlon
 */ 


#ifndef TIMER_H_
#define TIMER_H_
	
	#include <avr/io.h>

	void timer_init();

	void timer_on();
	void timer_off();

#endif /* TIMER_H_ */