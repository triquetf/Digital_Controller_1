//FONCTIONS TIMER


//INCLUDE
#include "TIMERS.h"
#include "Main.h"
#include <avr/io.h>


//DECLARATION DES VARIABLES GLOGALES


//PROTOTYPE FONCTIONS INTERNES


//CONTENU FONCTIONS EXTERNES


void TIMER1_Init_1ms(void)
{
	//En mode compteur le registre TCCR1A = 0x00
	//Si diviseur par 1 -> 1000000/1 = 1000 Khz
	// Une période = 1µS
	// Si je compte jusque 1000 --> 1000 X 1 = 1 ms
	
	// MODE OVERFLOW
	// (TCCR1B) : WGM13 =0 |WGM12 = 0  (TCCR1A) : WGM11 = 0 | WGM10 =0
	CLR_BIT(TCCR1B, WGM13);
	CLR_BIT(TCCR1B, WGM12);
	CLR_BIT(TCCR1A, WGM11);
	CLR_BIT(TCCR1A, WGM10);
	
	//No prescaler
	// (TCCR1B) : CS12 = 0 | CS11 = 0 | CS10 = 0
	CLR_BIT(TCCR1B, CS12);
	CLR_BIT(TCCR1B, CS11);
	SET_BIT(TCCR1B, CS10);
	
	// Valeur initiale du compteur = 65535 - 1000 = 64535
	TCNT1 = 64535;
	/* Autre procédé, on écrit (en format hexadécimal) dans le byte de poids plus élevé, puis dans le byte de poids le moins élevé.
	TCNT1H = 0xFC;
	TCNT1L = 0x17;
	*/
	
	// Autorisation de l'interruption en cas d'overflow
	SET_BIT(TIMSK1, TOIE1);
	//TIMSK1 |= (1<<TOIE1);
}


void TIMER0_Init_1ms(void)
{
	// fréquence horloge = 1000000 hz
	// Utilisation du TIMER 0, comptage sur 8 bits
	// Si diviseur par 8 --> 1000000/8 = 125 Khz
	// Une période = 8µS
	// Si je compte jusque 125 --> 125 X 8 = 1 ms
	//TCCR0A = 0x00; // |= (0<<CS02)|(1<<CS01)|(0<<CS00);
	CLR_BIT(TCCR0A,CS02);
	SET_BIT(TCCR0A,CS01);
	CLR_BIT(TCCR0A,CS00);
	//TCCR0B |= (0<<CS02)|(1<<CS01)|(0<<CS00);
	CLR_BIT(TCCR0B,CS02);
	SET_BIT(TCCR0B,CS01);
	CLR_BIT(TCCR0B,CS00);
	
	// Valeur initiale du compteur = 256 - 125 = 131
	TCNT0 = 131;
	// Autorisation de l'interruption en cas d'overflow
	TIMSK0 = (1<<TOIE0);
	SET_BIT(TIMSK0,TOIE0);
	
	/*
	// fréquence horloge = 16Mhz
	// Utilisation du TIMER 0, comptage sur 8 bits
	// Si diviseur par 8 --> 16000000/64 = 250 Khz
	// Une période = 4µS
	// Si je compte jusque 250 --> 250 X 4 = 1 ms
	//TCCR0A = 0x00; // |= (0<<CS02)|(1<<CS01)|(1<<CS00);
	//SET_BIT(TCCR0A,CS02);
	//CLR_BIT(TCCR0A,CS01);
	//CLR_BIT(TCCR0A,CS00);
	//TCCR0B |= (0<<CS02)|(1<<CS01)|(0<<CS00);
	
	
	CLR_BIT(TCCR0B,CS02);
	SET_BIT(TCCR0B,CS01);
	SET_BIT(TCCR0B,CS00);
	
	// Valeur initiale du compteur = 256 - 250 = 6
	TCNT0 = 6;
	// Autorisation de l'interruption en cas d'overflow
	TIMSK0 = (1<<TOIE0);
	SET_BIT(TIMSK0,TOIE0);
	*/
	
}

//CONTENU FONCTIONS INTERNES

	
