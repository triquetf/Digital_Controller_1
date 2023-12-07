//INCLUDE
#include <avr/io.h>
#include "Main.h"

//DECLARATION DES VARIABLES GLOGALES
//unsigned char Led;
//unsigned char Relais;

//PROTOTYPE FONCTIONS INTERNES


//CONTENU FONCTIONS EXTERNES

void Init_Hardware(void)
{
	/* Configuration I/O */
	//LED en PD7 en mode Output
	SET_BIT(DDRD,DDD7);
	// LED OFF au démarrage
	//Led = FALSE;
	CLR_BIT(PORTD,PD7);
	// RELAIS en PD6 en mode Output
	//SET_BIT(DDRD,DDD6);
	// Contacts RELAIS ouverts au démarrage
	//Relais = FALSE;
	//CLR_BIT(PORTD,PD6);
	// Wake-up en PD2 en mode Input avec pull down
	CLR_BIT(DDRD,DDD2);
	// Pull UP en PD2 enabled
	SET_BIT(PORTD,PD2);
	// Contact secondaire relais en PA6 en mode Input avec pull up
	//CLR_BIT(DDRA,DDA6);
	// Pull UP en PA6 enabled
	//SET_BIT(PORTA,PA6);
	// Interruption externe via INT0 de la broche PD2 enabled
	SET_BIT(EIMSK,INT0);
	// Interruption sur flanc descendant
	//(EICRA) ISC01 = 1 |ISC00 = 0
	SET_BIT(EICRA,ISC01);
	CLR_BIT(EICRA,ISC00);
	
	// Configuration clavier 5 touches
	// TOUCHES UP (PC3),DOWN (PC4), LEFT (PC5), RIGHT (PC6), ENTER (PC7)
	//Input Mode
	CLR_BIT(DDRC,DDC3);
	CLR_BIT(DDRC,DDC4);
	CLR_BIT(DDRC,DDC5);
	CLR_BIT(DDRC,DDC6);
	CLR_BIT(DDRC,DDC7);
	//enable pull up
	SET_BIT(PORTC,PORTC3);
	SET_BIT(PORTC,PORTC4);
	SET_BIT(PORTC,PORTC5);
	SET_BIT(PORTC,PORTC6);
	SET_BIT(PORTC,PORTC7);
	// enable int
	SET_BIT(PCICR,PCIE2);
	// enable mask
	SET_BIT(PCMSK2,PCINT19);  // UP
	SET_BIT(PCMSK2,PCINT20); // DOWN
	SET_BIT(PCMSK2,PCINT21); // LEFT
	SET_BIT(PCMSK2,PCINT22); // RIGHT
	SET_BIT(PCMSK2,PCINT23); // ENTER
	
	// ADC sur PA7
	//Input Mode
	//CLR_BIT(DDRA,DDA7);
	
	// PWM
	// PWM1B sur PD4, Output Mode
	//SET_BIT(DDRD,DDD4);
	// PWM1A sur PD5, Output Mode
	//SET_BIT(DDRD,DDD5);
	// PWM3A sur PB6, Output Mode
	//SET_BIT(DDRB,DDB6);
	
}
//CONTENU FONCTIONS INTERNES
