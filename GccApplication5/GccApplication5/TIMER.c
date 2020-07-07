/*
 * TIMER.C
 *
 * Created: 2/03/2019 16:24:04
 *  Author: marlon
 */ 

 #include "TIMER.h"
 #define Fclk 1
 void timer_init(){
	 
	 //Operation Mode = CTC
	 TCCR1A &=~ (1<<WGM10);
	 TCCR1A &=~ (1<<WGM11);
	 TCCR1B |=  (1<<WGM12);
	 TCCR1B &=~ (1<<WGM13);
	 
	 //Compare value
	 OCR1A = (16000000/1024/Fclk) - 1;

	 //enable interrupt
	 TIMSK1 |= (1<<OCIE1A);
 }

 void timer_on(){

	 TCNT1 = 0x0000;
	 //N = 1024
	 TCCR1B |=  (1<<CS10);
	 TCCR1B &=~ (1<<CS11);
	 TCCR1B |=  (1<<CS12);
	 
 }

 void timer_off(){
	 
	 //Clock setting T1clock = 0 Hz
	 TCCR1B &=~ (1<<CS10);
	 TCCR1B &=~ (1<<CS11);
	 TCCR1B &=~ (1<<CS12);

 }

