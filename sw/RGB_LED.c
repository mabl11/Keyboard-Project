/*
 * RGB_LED.c
 *
 * Created: 09.04.2022 11:36:59
 *  Author: mauro
 */

// #include "matrix_query.h"
// #include "GenericHID.h"
// #include "RGB_LED.h"

//#define F_CPU 16000000UL

//#define RGB_LED PORTF7
//volatile int interrupt_counter = 0;

//void SetUp_Timer(void){
	//TCCR0B |= (1 << CS00); //start timer with no prescaler
	//TIFR0 = 1 << TOV0; //clear overflow flag
	//TIMSK0 |= (1 << TOIE0);	//enable overflow
	//sei();						
//}


//ISR(TIMER0_OVF_vect){
	//interrupt_counter++;
	//PORTF ^= (1 << RGB_LED);
	
//}