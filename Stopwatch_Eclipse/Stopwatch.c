/*
 * Stopwatch.c
 *
 *  Created on: Sep 21, 2021
 *      Author: Spectrum
 */
#define F_CPU 1000000UL
#include"Datatypes.h"
#include<avr/io.h>
#include<avr/interrupt.h>

void TMR0_Init(void);
void INT0_Init(void);
void INT1_Init(void);
void INT2_Init(void);
void TMR1_Init(void);
void TMR1_Reset(void);
void TMR1_Pause(void);
void TMR1_Resume(void);
void Display(u8 c);

u8 Tick = 0, sec = 0, min = 0, hr = 0;
u8 Dgt[6];

ISR(TIMER0_OVF_vect)
{
	   static u8 i=0;
	   PORTA=~(1<<i);
	   if(i==5)
	      i=0;
	   else
	      i++;

	   Display(Dgt[i]);

}

ISR(TIMER1_COMPA_vect)
{
	Tick++;
		if(Tick == 2)
		{

			sec++;
			if(sec == 60)
			{
				sec = 0;
				min++;
			}

			if(min == 60)
			{
				min = 0;
				hr++;
			}

			if(hr == 24)
			{
				hr = 0;
				min = 0;
				sec = 0;
			}

			Dgt[0] = sec%10;
			Dgt[1] = sec/10;
			Dgt[2] = min%10;
			Dgt[3] = min/10;
			Dgt[4] = hr%10;
			Dgt[5] = hr/10;

		Tick=0;
		}
}

ISR(INT0_vect)
{
	TMR1_Reset();
}

ISR(INT1_vect)
{
	TMR1_Pause();
}

ISR(INT2_vect)
{
	TMR1_Resume();
}

int main()
{
	DDRA = 0x3F;
	DDRC = 0x0F;

	PORTD |= (1 << PD2);
	PORTB |= (1 << PB2);


	INT0_Init();
	INT1_Init();
	INT2_Init();

	TMR0_Init();
	TMR1_Init();



	for(;;)
	{

	}

}

void INT0_Init(void)
{
	SREG  &= ~(1<<7);                   // Disable interrupts by clearing I-bit
	DDRD  &= (~(1<<PD2));               // Configure INT0/PD2 as input pin
	GICR  |= (1<<INT0);                 // Enable external interrupt pin INT0
	MCUCR |= (1<<ISC01);   				// Trigger INT0 with the raising edge
	SREG  |= (1<<7);                    // Enable interrupts by setting I-bit
}

void INT1_Init(void)
{
	SREG  &= ~(1<<7);                   // Disable interrupts by clearing I-bit
	DDRD  &= ~(1<<PD3);               	// Configure INT1/PD3 as input pin
	GICR  |= (1<<INT1);                 // Enable external interrupt pin INT1
	MCUCR |= (1<<ISC11 | 1 << ISC10);   // Trigger INT0 with the raising edge
	SREG  |= (1<<7);                    // Enable interrupts by setting I-bit
}

void INT2_Init(void)
{
	SREG  &= ~(1<<7);                   // Disable interrupts by clearing I-bit
	DDRB  &= (~(1<<PB2));               // Configure INT2/PB2 as input pin
	GICR  |= (1<<INT2);                 // Enable external interrupt pin INT2
	SREG  |= (1<<7);                    // Enable interrupts by setting I-bit
}

void TMR1_Init(void)
{
	TCCR1B |= (1 << WGM12 | 1 << CS11);
	TCNT1 = 0;
	OCR1A = 62500;
	TIMSK |= (1<<OCIE1A);
}

void TMR1_Reset(void)
{
	sec = 0, min = 0, hr = 0;
	TCCR1B |= (1<<CS11);
}

void TMR1_Pause(void)
{
	TCCR1B &= ~(1<<CS11);
}

void TMR1_Resume(void)
{
	TCCR1B |= (1<<WGM12| 1<<CS11);
}

void Display(u8 c)
{

	switch(c)
	{
	case 0:
		PORTC = 0;
		break;

	case 1:
		PORTC = 1;
		break;

	case 2:
		PORTC = 2;
		break;

	case 3:
		PORTC = 3;
		break;

	case 4:
		PORTC = 4;
		break;

	case 5:
		PORTC = 5;
		break;

	case 6:
		PORTC = 6;
		break;

	case 7:
		PORTC = 7;
		break;

	case 8:
		PORTC = 8;
		break;

	case 9:
		PORTC = 9;
		break;
	}

}

void TMR0_Init(void)
{
	TCNT0 = 0;
    TCCR0|=(1<<CS01);
	TIMSK|=(1<<TOIE0);
}




