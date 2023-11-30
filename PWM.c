#include <avr/io.h>
#include <avr/interrupt.h>
#include "PWM.h"
#include "Main.h"

//Initialisation du PWM_1
void PWM_1_A_B_init(unsigned char Prescaler, unsigned int Top_1)
{
	unsigned char Tampon;
	//Clear OC1A, OC1B on Compare Match, set OC1A, OC1B at BOTTOM (non-inverting mode) --> see Table 14-3
	//fast PWM --> see Table 14-5 , mode = 14
	TCCR1A  |= ((1 << COM1A1) | (1 << COM1B1) | (1 << WGM11));
	TCCR1B |=  (1 << WGM13)| (1 << WGM12);
	// Set prescaler, see Table 14-6
	Tampon = TCCR1B & 0B11111000;
	TCCR1B = Tampon | Prescaler;
	ICR1 = Top_1; //overflow tous les Top_1 ticks
	// Initialisation des valeurs de seuil à 0
	OCR1A = 0;
	OCR1B = 0;
}

//Initialisation du PWM_3
void PWM_3_A_init(unsigned char Prescaler, unsigned int Top_3)
{
	unsigned char Tampon;
	//Clear OC3A, OC3B on Compare Match, set OC3A at BOTTOM (non-inverting mode) --> see Table 14-3
	//fast PWM --> see Table 14-5 , mode = 14
	TCCR3A  |= ((1 << COM3A1) | (1 << WGM31));
	TCCR3B |=  (1 << WGM33)| (1 << WGM32);
	// Set prescaler, see Table 14-6
	Tampon = TCCR3B & 0B11111000;
	TCCR3B = Tampon | Prescaler;
	ICR3 = Top_3; //overflow tous les Top_1 ticks
	// Initialisation des valeurs de seuil à 0
	OCR3A = 0;
}

//Change le duty cycle du PWM_1A
void setDutyCycle_1A(int Duty_cycle)
{
	if((Duty_cycle < ICR1) && (Duty_cycle > 0))
	{
		OCR1A = Duty_cycle;
	}
	else if(Duty_cycle >= ICR1)
	{
		OCR1A = ICR1;
	}
	else
	{
		OCR1A = 0;
	}
}

//Change le duty cycle du PWM_1B
void setDutyCycle_1B(int Duty_cycle)
{
	if((Duty_cycle < ICR1) && (Duty_cycle >0)) 
		{
			OCR1B = Duty_cycle;
		}
	else if(Duty_cycle >= ICR1)
		{ 
			OCR1B = ICR1;
		}	
		 else 
			{
				OCR1B = 0;
			}
}

//Change le duty cycle du PWM_3A
void setDutyCycle_3A(int Duty_cycle)
{
	if((Duty_cycle < ICR3) && (Duty_cycle > 0))
	{
		OCR3A = Duty_cycle;
	}
	else if( Duty_cycle >= ICR3)
	{
		OCR3A = Duty_cycle;
	}
	else
	{
		OCR3A = 0;
	}
}






