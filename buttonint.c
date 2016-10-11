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
#include <string.h>




 // Initialise the timer and pin change interrupts
 void Initialise_Interrupts()
 {

	        /* Initialise timer2 interrupts */
	        OCR2A = 128;								// Initial value to count to
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
	DDRD &= ~(1 << PD2);

	/* No pull-up resistor on inputs */
	PORTB = 0x00;
	PORTB |= ~(1 << PD2);

	lcd_init('c');		// Initialise the LCD
	char str[20];

	while (1)
	{

//		for(int i = 7; i >= 0; i--)
//		{
//			if(PIND & (1 << PD2))
//			{
//				OCR2A += 1*i;
//			}
//			else
//			{
//				OCR2A -= 1*i;
//			}
//			snprintf(str,20,"%i",OCR2A);
//			lcd_display(str,0);		// Display the time
//			_delay_ms(50);			// Short delay
//			lcd_clear();			//Clear the LCD
//		}

	}
	return 0;
}




