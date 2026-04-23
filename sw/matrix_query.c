/*
* CFile1.c
*
* Created: 19.04.2022 13:38:23
*  Author: maubla
*/
#include <stdio.h>

#include "matrix_query.h"
#include "matrix_mb62.h"

#define F_CPU 16000000UL

#define MATRIX_ROWS 5
#define MATRIX_COLS 14

#define ROW_0 PINF0
#define ROW_1 PINF1
#define ROW_2 PINF4
#define ROW_3 PINF5
#define ROW_4 PINF6

#define COLUMN_0 PORTC6
#define COLUMN_1 PORTC7
#define COLUMN_2 PORTB6
#define COLUMN_3 PORTB5
#define COLUMN_4 PORTB4
#define COLUMN_5 PORTD7
#define COLUMN_6 PORTD6
#define COLUMN_7 PORTD4
#define COLUMN_8 PORTD5
#define COLUMN_9 PORTD3
#define COLUMN_10 PORTD2
#define COLUMN_11 PORTD1
#define COLUMN_12 PORTD0
#define COLUMN_13 PORTB7

uint8_t ROWS[MATRIX_ROWS] = {ROW_0, ROW_1, ROW_2, ROW_3, ROW_4}; //Y
uint8_t COLUMNS[MATRIX_COLS] = {COLUMN_0, COLUMN_1, COLUMN_2, COLUMN_3, COLUMN_4, COLUMN_5, COLUMN_6, COLUMN_7, COLUMN_8, COLUMN_9, COLUMN_10, COLUMN_11, COLUMN_12, COLUMN_13}; //X

uint8_t keycode_toHost = 0;

unsigned int Row_Index; //row index counter (for matrix pos)
unsigned int Column_Index; //column index counter (for matrix pos)

uint8_t checkMatirx_getKey();
void TurnOff_Cols(void);
void TurnOn_Cols(void);

uint8_t checkMatirx_getKey(){
	if(Column_Index == 13){
		Column_Index = 0; 
	}
	for(; Column_Index<14; Column_Index++){
		TurnOn_Cols();

		for(Row_Index=0; Row_Index<5; Row_Index++){
			if((PINF & (1<<ROWS[Row_Index])) == (1<<ROWS[Row_Index])){
				keycode_toHost = KEY_MATRIX[Row_Index][Column_Index]; 
			}
		if(keycode_toHost){
			break;
		}
		}
		TurnOff_Cols();
	}
	return keycode_toHost;
}

void TurnOn_Cols(void){
	if((Column_Index == 0) || (Column_Index == 1)) {
		PORTC |= 1<<COLUMNS[Column_Index]; //turn on all Columns of PORTC 
	}
	else if((Column_Index == 13) | (Column_Index == 2) | (Column_Index == 3) | (Column_Index == 4)) {
		PORTB |= 1<<COLUMNS[Column_Index]; //turn on all Columns of PORTB
	}
	else {
		PORTD |= 1<<COLUMNS[Column_Index]; //turn on all Columns of PORD 
	}
}

void TurnOff_Cols(void){
	if((Column_Index == 0) || (Column_Index == 1)) {
		PORTC &= ~(1<<COLUMNS[Column_Index]); //turn off all Columns of PORTC
	}
	else if((Column_Index == 13) | (Column_Index == 2) | (Column_Index == 3) | (Column_Index == 4)) {
		PORTB &= ~(1<<COLUMNS[Column_Index]); //turn off all Columns of PORTB
	}
	else {
		PORTD &= ~(1<<COLUMNS[Column_Index]); //turn off all Columns of PORTD
	}
}

void SetUp_Timer(void){
	TCCR0B |= (1 << CS00); //start timer with no prescaler
	TIFR0 = 1 << TOV0; //clear overflow flag
	TIMSK0 |= (1 << TOIE0);	//enable overflow
	sei();
}