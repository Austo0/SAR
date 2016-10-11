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

 static int counter = 0;
 static int seconds = 0;
 static int minutes = 0;
 static int hours = 0;
 static int stop = 0;
 static int zeroed = 0;

// Update the timer
 void Update_Time()
 {
 	if(counter >= 100)
 	{
 		counter = 0;
 		seconds++;
 	}
 	if(seconds >= 60)
 	{
 		seconds = 0;
 		minutes++;
 	}
 	if(minutes >= 60)
 	{
 		minutes = 0;
 		hours++;
 	}
 }

 // Initialise the timer and pin change interrupts
 void Initialise_Interrupts()
 {
			/* Button on Port B pin 0 --- route via PCINT0 */
			/* Button on Port B pin 1 --- route via PCINT1 */
	        PCMSK0 |= (1 << PCINT0) | (1 << PCINT1);
	        PCICR  |= (1 << PCIE0);

	        /* Initialise timer1 interrupts */
	        TCCR1B |= (1 << WGM12);					// Set the timer to CTC mode
	        OCR1A = 20000;							// Value to count to
	        TCCR1B |= (1 << CS11) ;					// 8 pre-scaler
	        TIMSK1 |= (1 << OCIE1A);				// Enable interrupt flag when timer is matched with OCR0A

	        /* Initialise timer2 interrupts */
	        OCR2A = 0;								// Initial value to count to
	        TCCR2A |= (1 << COM2A1);				// Set non-inverting mode
	        TCCR2A |= (1 << WGM20) | (1 << WGM21);	// Set fast PWM mode
	        TCCR2B |= (1 << CS20) ;					// No pre-scaling

	        /* Globally enable interrupts */
	        sei();
 }

int main(void)
{
	Initialise_Interrupts();	//Initialise interrupts

	/* Set up Port B; input 1 on Bit 0, input 2 on Bit 1, output on Bit 3  */
	DDRB |= (1 << PB3) ;

	/* No pull-up resistor on inputs */
	PORTB = 0x00;

	lcd_init('c');		// Initialise the LCD
	char str[20];

	while (1)
	{

		//Concatenate the time in the format HH:MM:SS.XX where XX is hundredths of seconds
		snprintf(str,20,"%02i:%02i:%02i.%02i\n%i",hours,minutes,seconds,counter,OCR2A);
		lcd_display(str,0);		// Display the time
		_delay_ms(50);			// Short delay
    	lcd_clear();			//Clear the LCD

	}
	return 0;
}


// Interrupt when timer reaches OCR0A
ISR(TIMER1_COMPA_vect)
{
	if(stop != 1 && zeroed !=1)	// If the stop watch has not been stopped
	{
		counter++;	// Increment the timer
		Update_Time();			//Update the timer
	}
}

	ISR(PCINT0_vect)
	{
		uint8_t pin;
		pin = PINB;		// Save the button that was pressed
		// If the stop button is pressed
		if (! (pin & (1 << PB0)))
		{
			stop = !stop;	//Stop the timer
			zeroed = 0;		//Timer not reset
		}
		// If the reset button has been pressed and the time is stopped
		if ((!(pin & (1 << PB1))) && stop == 1 && zeroed == 0 )
		{
			/* Reset the time */
			counter = 0;
			seconds = 0;
			minutes = 0;
			hours = 0;
			zeroed = 1;
		}
		// If the button on PB1 is pressed
		if  (!(pin & (1 << PB1)))
		{
			if (OCR2A >= 250)
			{
				OCR2A = 0; 	// Reset the PWM duty cycle
			}
			else
			{
			OCR2A += 1;	// Increment the PWM duty cycle
			}
		}
	}



