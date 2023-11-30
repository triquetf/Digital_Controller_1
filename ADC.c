#include "ADC.h"
#include <avr/io.h>
#include "Main.h"

//FOR DEBUG
#include "USART.h"
// END DEBUG

// DECLARATION DES CONSTANTES

//DECLARATION DES VARIABLES GLOGALES

//DETAIL DES FONCTIONS

void ADC_init(void)
{
// ADC inactif, diviseur par 16 (compromis vitesse / précision)
	//ADCSRA |= (0<<ADEN)|(1<<ADPS2)|(0<<ADPS1)|(0<<ADPS0);
	CLR_BIT(ADCSRA,ADEN);
	SET_BIT(ADCSRA,ADPS2);
	CLR_BIT(ADCSRA,ADPS1);
	CLR_BIT(ADCSRA,ADPS0);
	
	// tension ref = VCC, justification à droite
	//ADMUX |= (0<<REFS1)|(1<<REFS0)|(0<<ADLAR);
	CLR_BIT(ADMUX,REFS1);
	SET_BIT(ADMUX,REFS0);
	CLR_BIT(ADMUX,ADLAR);
}

void ADC_ON(unsigned char Canal_Nbr)
{
	unsigned char Tampon;
	//Sélection du canal (il s'agit des 5 bits LSB du registre ADMUX --> pas de shift, uniquement un 'ou' avec le nombre 
	//après masquage !)
	Tampon = ADMUX & 0b11100000;
	ADMUX =  Tampon | Canal_Nbr;
	//ADC ON
	SET_BIT(ADCSRA,ADEN);
}

void ADC_OFF()	
{
	CLR_BIT(ADCSRA,ADEN);
}


unsigned int Conversion_ADC_10bits(void)
{
	// *** CONVERSION ADC *** (DS p207)
	//ADCSRA |= (1<<ADSC);
	SET_BIT(ADCSRA,ADSC);
	// attendre fin de conversion (DS p 205)
	while(!(ADCSRA & (1<<ADIF)));
	// Reset du flag ADIF
	SET_BIT(ADCSRA,ADIF);
	//Usart0_Tx(ADCH);Usart0_Tx(ADCL);
	//return ADC;
	//return (ADCL+(ADCH<<8));
	return ADC;
}



	
