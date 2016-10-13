/*
 *  SAR.c
 * By Austen Fogarty 1231547
 * Demonstrates the use of a successive approximation register
 * using the pwm output to generate a constant reference voltage
 * over a low pass filer
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

// Slow SAR conversion
double SAR_Conversion()
 {
		int delay = 50;

		int ADC1;					// Measured ADC
		OCR2A = (1 << 7);			// 50% duty cycle

		 for(int i = 7; i >= 0; i--)	// For 8 bits
		 {
		 	OCR2A |= (1 << i);			// Set the bit to check
		 	_delay_ms(delay);			// Wait for reference voltage to settle

		 	if(!(PINB & (1 << PB0)))	// If the reference voltage is higher than the ADC input
		 	{
		 		OCR2A &= ~(1 << i);		// Set the current bit to a zero
		 	}
		 }
		 ADC1 = OCR2A;					// Save the PWM duty cycle


	 return ((double)5.04/255)*ADC1;
 }

// Fast SAR conversion
double SAR_Conversion1()
 {
		int delay = 2;

		int ADC1;						// Measured ADC
		OCR2A = (1 << 7);				// 50% duty cycle

		 for(int i = 7; i >= 0; i--)	// For 8 bits
		 {
		 	OCR2A |= (1 << i);			// Set the bit to check
		 	_delay_ms(delay);			// Wait for reference voltage to settle

		 	if(!(PINB & (1 << PB0)))	// If the reference voltage is higher than the ADC input
		 	{
		 		OCR2A &= ~(1 << i);		// Set the current bit to a zero
		 	}
		 }
		 ADC1 = OCR2A;					// Save the PWM duty cycle


	 return ((double)5.04/255)*ADC1;
 }

/* Calculate the mean of N ADC samples */
float Mean(int const *nsamples,int N)
{
	float u = 0;
	// N = Number of samples
	for (int n = 0; n < N; n++)
	{
		u +=nsamples[n];
	}

	return ((float)u)/N;		//Calculate Mean;
}


/* Calculate the standard deviation of N samples */
float Standard_Deviation(int const *nsamples,int N)
{
	float M = Mean(nsamples,N);
	float U2 = 0;
	for (int n = 0; n < N; n++)
	{
		U2 += pow((float)(nsamples[n]-M),2);
	}
	U2 = ((float)U2/N);
	return sqrt(U2);
}


int main(void)
{
	Initialise_Interrupts();	//Initialise interrupts

	/* Set up Port B; output on Bit 3  */
	DDRB |= (1 << PB3) ;

	/* No pull-up resistor on inputs */
	PORTB = 0x00;

	lcd_init('c');		// Initialise the LCD
	char str[34];		// Display
	char Svoltage[20];	// standard deviation voltage
	char Mvoltage[20];	// mean voltage
	char S[20];			// standard deviation ADC
	char M[20];			// mean ADC

	int N = 500;
	int nsamples[N];	// voltage
	while (1)
	{
		// For the specified number of samples
		for(int n = 0; n < N; n++)
		{
		SAR_Conversion1();		// Run the SAR conversion

		nsamples[n] = OCR2A;
		_delay_ms(2);
		}
		dtostrf(((double)5.04/255)*Standard_Deviation(nsamples,N),5,4,Svoltage); // Standard Deviation voltage value
		dtostrf(Mean(nsamples,N),5,3,M);							// Mean ADC value
		dtostrf(((double)5.04/255)*Mean(nsamples,N),5,4,Mvoltage);	// Mean voltage
		dtostrf(Standard_Deviation(nsamples,N),5,4,S);				// Standard Deviation ADC value


		 snprintf(str,34,"M: %sV\nS:%sV %s",Mvoltage,Svoltage,S);	// Convert to string
		 _delay_ms(200);
		 lcd_clear();												// Clear the LCD
		 lcd_display(str,0);										// Display the voltage on the LCD

	}
	return 0;
}





