//INCLUDE
#include "USART.h"
#include "Main.h"
#include <avr/io.h>

//DECLARATION DES VARIABLES GLOGALES


//PROTOTYPE FONCTIONS INTERNES


//CONTENU FONCTIONS EXTERNES

void Usart0_Tx(char data)
{
    // UDRE Flag , is the transmit buffer UDR) ready to receive new data ?
	// if UDRE0 =1 the buffer is empty
	while (!(UCSR0A & (1<<UDRE0)));
    UDR0 = data;
}


void Usart0_Tx_String(char *String)
{
	char Continue = TRUE;
	while (Continue)
	{
		if(*String==0) Continue = FALSE;
		else Usart0_Tx(*String++);
	}
}

void USART0_Init_9600(void)
{
	// fréquence horloge = 1000000 hz, Si Baudrate = 9600 alors UBRR = 12
	//1xspeed  U2X0 = 1  
	//UCSR0A |= (1<<U2X0);
	SET_BIT(UCSR0A,U2X0);
	
	// 9600 baud
	//UBRR0 = 12;
	UBRR0H = 0x00;
	UBRR0L = 0x0C;

	// Configuration en émission seulement.
	//(UCSR0B) RXCIE0 = 0 | TXCIE0 =0 | UDRIE0 = 0 | RXEN0 =0 | TXEN0 = 1 | UCSZ02 = 0 | RXB80 = 0 | TXB80 = 0
	UCSR0B = 0b00001000;
	
	// Async. mode, 8 bits, 1 bit de stop, pas de contrôle de parité
   	//(UCSR0C) UMSEL01 = 0 | UMSEL00 = 0 | UPM01 = 0 | UPM00 = 0 | USBS0 = 0 | UCSZ01 = 1 | UCSZ00 = 1 | UCPOL0 = 0;
	UCSR0C = 0b00000110;
}

void USART0_Init_9600_INT_ON_RX(void)
{
	// fréquence horloge = 1000000 hz, Si Baudrate = 9600 alors UBRR = 12
	//1xspeed  U2X0 = 1
	UCSR0A |= (1<<U2X0);
	// 9600 baud
	//UBRR0H = 0x00;
	//UBRR0L = 0x0C;
	UBRR0 = 12;
	// Configuration Emission + Réception, Interruptions en RX
	//(UCSR0B) RXCIE0 = 1 | TXCIE0 =0 | UDRIE0 = 0 | RXEN0 = 1 | TXEN0 = 1 | UCSZ02 = 0 | RXB80 = 0 | TXB80 = 0
	UCSR0B = 0b10011000;
	// Async. mode, 8 bits, 1 bit de stop, pas de contrôle de parité
	//(UCSR0C) UMSEL01 = 0 | UMSEL00 = 0 | UPM01 = 0 | UPM00 = 0 | USBS0 = 0 | UCSZ01 = 1 | UCSZ00 = 1 | UCPOL0 = 0;
	UCSR0C = 0b00000110;
}

void USART0_Init_115200_INT_ON_RX(void)
{
	#if defined (_1MHZ)
	#elif defined (_8MHZ)
		// fréquence horloge = 8000000 hz, Si Baudrate = 115200 alors UBRR = 8
		//1xspeed  U2X0 = 1
		UCSR0A |= (1<<U2X0);
		// 115200 baud
		UBRR0 = 8;
		// Configuration Emission + Réception, Interruptions en RX
		//(UCSR0B) RXCIE0 = 1 | TXCIE0 =0 | UDRIE0 = 0 | RXEN0 = 1 | TXEN0 = 1 | UCSZ02 = 0 | RXB80 = 0 | TXB80 = 0
		UCSR0B = 0b10011000;
		// Async. mode, 8 bits, 1 bit de stop, pas de contrôle de parité
		//(UCSR0C) UMSEL01 = 0 | UMSEL00 = 0 | UPM01 = 0 | UPM00 = 0 | USBS0 = 0 | UCSZ01 = 1 | UCSZ00 = 1 | UCPOL0 = 0;
		UCSR0C = 0b00000110;
	#elif defined (_16MHZ)
		// fréquence horloge = 16000000 hz, Si Baudrate = 115200 alors UBRR = 16
		//1xspeed  U2X0 = 1
		UCSR0A |= (1<<U2X0);
		// 115200 baud
		//UBRR0H = 0x00;
		//UBRR0L = 0x0C;
		UBRR0 = 16;
		// Configuration Emission + Réception, Interruptions en RX
		//(UCSR0B) RXCIE0 = 1 | TXCIE0 =0 | UDRIE0 = 0 | RXEN0 = 1 | TXEN0 = 1 | UCSZ02 = 0 | RXB80 = 0 | TXB80 = 0
		UCSR0B = 0b10011000;
		// Async. mode, 8 bits, 1 bit de stop, pas de contrôle de parité
		//(UCSR0C) UMSEL01 = 0 | UMSEL00 = 0 | UPM01 = 0 | UPM00 = 0 | USBS0 = 0 | UCSZ01 = 1 | UCSZ00 = 1 | UCPOL0 = 0;
		UCSR0C = 0b00000110;
	#endif
	
}




//CONTENU FONCTIONS INTERNES

