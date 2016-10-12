/*
 *  buttonint.c
 *
 *  By M. J. Cree
 * Edited by Austen Fogarty 1231547
 * Demonstrates the use of timers and interrupts
 * to make a stopwatch with stop and reset buttons
 *
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

 // Initialise the timer and pin change interrupts
 void Initialise_Interrupts()
 {
	        /* Initialise timer2 interrupts */
	        OCR2A = 128;							// Initial value to count to
	        TCCR2A |= (1 << COM2A1);				// Set non-inverting mode
	        TCCR2A |= (1 << WGM20) | (1 << WGM21);	// Set fast PWM mode
	        TCCR2B |= (1 << CS20) ;					// No pre-scaling

	        /* Globally enable interrupts */
	        sei();
 }

int main(void)
{
	Initialise_Interrupts();	//Initialise interrupts

	/* Set up Port B; output on Bit 3  */
	DDRB |= (1 << PB3) ;

	/* No pull-up resistor on inputs */
	PORTB = 0x00;

	lcd_init('c');		// Initialise the LCD
	char str[20];		// Display
	char voltage[20];	// Voltage
	int ADC1;			// Measured ADC

	while (1)
	{
		OCR2A = (1 << 7);	// 50% duty cycle

		 		for(int i = 7; i >= 0; i--)
		 		{
		 			OCR2A |= (1 << i);	// Set the bit to check
		 			_delay_ms(50);


		 			if(!(PINB & (1 << PB0)))
		 			{
		 				OCR2A &= ~(1 << i);
		 			}
		 		}
		 		ADC1 = OCR2A;
		 		dtostrf(((double)5/255)*ADC1,4,2,voltage);

		 		snprintf(str,20,"V = %s",voltage);

		 		lcd_clear();			//Clear the LCD
		 		lcd_display(str,0);		// Display the time


	}
	return 0;
}





