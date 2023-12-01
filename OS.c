#include "OS.h"
#include "Menu.h"
#include "Main.h"
#include "TIMERS.h"
#include "USART.h"
#include "lcd.h"
#include "DS3232.h"
#include <avr/interrupt.h>
#include <avr/io.h>

//Variables globales
//char Lcd_TXT[6] [6] = {" ","GREEN","DOWN","RED","ENTER","BLUE"} ;

//Callback Chrono
void (*My_CB[MAX_CALLBACKS])(void);
unsigned int Time_CB[MAX_CALLBACKS];
volatile unsigned int Tick_CB[MAX_CALLBACKS];

//Interruption INT0 (demande ouverture porte)
//volatile unsigned char Door_Open = FALSE; // variable booléenne qui signale une demande d'ouverture de porte (via INT0)

//Callback USART0 (réception d'une chaîne de caractères)
void(*MaCBUSART0)(volatile char*);
volatile unsigned char USART0_Reception;
volatile char buf_USART0[MAXBUFUSART0];
volatile unsigned char idxbuf_USART0 = 0;

//Gestion Touches
volatile unsigned char Button;
unsigned char Latch_Button;

//Variables pour la machine d'états
unsigned char state;  // holds the current state, according to "menu.h"
char Message_LCD[17];

// DECLARATION DES FONCTIONS INTERNES


// DECLARATION DES FONCTIONS EXTERNES

// ****************  OSInitialiser ******************************
// Initialise l'OS: initialise les variables et démarre le Timer
// **************************************************************
void OS_Init(void)
{
 	unsigned char i;
 	//Initialisation variables Callback Timer
 	for (i=0; i< MAX_CALLBACKS; i++)
 	{
  		 My_CB[i] = 0;
  	}
  
	//Initialisation variables Callback USART0
	MaCBUSART0 = 0;	
	USART0_Reception = 0;
} 

// ENREGISTREMENT CALLBACKS TIMER
// ****************  EnregistrerFonctionDeRappel ******************************
// Sauve l'adresse de la fonction à rappeler. Lorsque le nombre d'interruptions
// aura atteint temps millisecondes, le système rappellera la fonction
// ****************************************************************************
unsigned char Callbacks_Record_Timer(void(*ptFonction)(void), unsigned int Time)
{
 	unsigned int i= 0; //(+1 car la valeur 0 doit signifier que la fonction n'est pas appelée)
 	while (My_CB[i]!=0 && i< (MAX_CALLBACKS+1)) i++;
	 //S'il reste de la place on enregistre et on retourne i (opération réussie)
 	if (i< (MAX_CALLBACKS+1))
 	{
  		 My_CB[i] = ptFonction;
  		 Time_CB[i] = Time; 
  		 Tick_CB[i] = 0; //Initialiser le compteur à 0;
   		return (i+1); // ID du call back 
  	}
 	else return 255; //Il n'y a plus de place pour enregistrer un callback
}

// RETIRER FONCTION DE RAPPEL
// ****************  Retirer fonction de rappel ********
// Libère l'emplacement de la callback
// *****************************************************
char Callbacks_Remove_Timer(unsigned char ID_CB)
{
	 My_CB[ID_CB-1] = 0;
	 return 0;
}

// **************** Enregistrer CallBack USART0 ****************************
// Sauve l'adresse de la fonction à rappeler
// *************************************************************************
void Callbacks_Record_Usart0_RX(void(*ptFonction)(volatile char*))
{
	//Sauver l'adresse de la fonction pour rappel
	MaCBUSART0 = ptFonction;
}

// ****************  Retirer fonction de rappel USART0 **********************

void Callbacks_Remove_Usart0_RX(void)
{
	MaCBUSART0 = 0;
}
	 
	 
// BOUCLE PRINCIPALE DE L'OS
// ****************  Boucle principale de l'OS ***********************
// Boucle infinie qui attend des événement liés aux interruptions pour 
// appeler les fonctions enregistrées
// *******************************************************************
void OS_Start(void)
{
	unsigned char idx;
	//Création, configuration et démarrage de Timer0pour générer une interruption toutes les mS
 	TIMER0_Init_1ms(); //A partir d'ici, interruption toutes les ms par Timer0
	// Configuration USART0 pour 9600 baud avec interruption en réception
	USART0_Init_115200_INT_ON_RX();
	
	// For debug
	//Usart0_Tx_String("Usart0 OK");
	
	
	// Initialisation des interruptions, on autorise toutes les interruptions
	// Pour les interruptions particulières, voir chaque fonction
	
	// Pour STATES MACHINE
	unsigned char nextstate;
	PGM_P statetext; // chaîne de texte sauvegardé dans la mémoire programme
	char (*pStateFunc)(char); // pointeur d'une fonction
	unsigned char input = NONE;
	unsigned char i, j;
	
	// Initialisation des variables qui concernent la machine d'états
	state = ST_TXT_WELCOME;
	nextstate = ST_TXT_WELCOME;
	statetext = Txt_WELCOME;
	pStateFunc = NULL;
	
 	sei();  

 	// BOUCLE INFINIE
	// Boucle principale de l'OS d'où on ne sort jamais
	 while(1)
 	 {
  		 // Check les conditions pour rappeler les fonctions liées au temps 
  		 for (idx = 0; idx < MAX_CALLBACKS; idx++)
    	 {
	 		if (My_CB[idx]) //Si on a l'adresse d'une fonction CB à cet index
     		//Si on est arrivé au nombre de mS demandé, on appelle la fonction 
			{	
     			if (Tick_CB[idx] >= Time_CB[idx])
      			{ 
	  				 Tick_CB[idx] = 0;
      				 My_CB[idx]();  //Rappel de la fonction enregistrée!
	 			}
			}
  		 }
		 // Check si réception Trame USART0
		 if (USART0_Reception)
		 {
		   USART0_Reception = FALSE;
		   if (MaCBUSART0) MaCBUSART0(buf_USART0); //Rappel de la fonction enregistrée!
		 }  
		 
		 // State Machine
		 if (statetext)
		 {
			 //Afficher_LCD(statetext);
			 cli();lcd_clrscr();lcd_gotoxy(0,0);lcd_puts(strcpy_P(Message_LCD, statetext));sei();
			 statetext = NULL; // Pour ne pas écrire le même texte sur l'afficheur (évite la scintillation de l'écran)
		 }
		 		 
		 // Read buttons
		 input = Button;
		 Button = NONE;

		 // When in this state, we must call the state function
		 if (pStateFunc)
		 {
			 nextstate = pStateFunc(input);
		 }
		 else
		 {
			 if (input != NONE)
			 {
				 nextstate = StateMachine(state, input);
			 }
		 }
		 if (nextstate != state)  // il y a changement d'état
		 {
			 state = nextstate; // l'état est maintenant le nouveau état de la séquence définie dans main.h
			 for (i=0; (j=pgm_read_byte(&Menu_State[i].state)); i++)
			 {
				 if (j == state)
				 {
					 statetext =  (PGM_P) pgm_read_word(&Menu_State[i].pText);
					 pStateFunc = (PGM_VOID_P) pgm_read_word(&Menu_State[i].pFunc);
					 break;
				 }
			 }
		 }
		 
  	 }
}

// CONTENU DES FONCTIONS INTERNES
unsigned char StateMachine(char state, unsigned char stimuli)
{
	unsigned char nextstate = state;    // Default stay in same state
	unsigned char i, j;
	for (i=0; ( j=pgm_read_byte(&menu_nextstate[i].state) ); i++ )
	{
		if ( j == state &&
		pgm_read_byte(&menu_nextstate[i].input) == stimuli)
		{
			// This is the one!
			nextstate = pgm_read_byte(&menu_nextstate[i].nextstate);
			break;
		}
	}
	return nextstate;
}


// INTERRUPTIONS        

// ******************
// INTERRUPTION TIMER
// ******************
ISR(TIMER0_OVF_vect)
{
	TCNT0 = 131;  // reconfiguration du Timer0
	// Ajourner tous les TICKS
	unsigned char Int_Counter;
  	for (Int_Counter = 0; Int_Counter < MAX_CALLBACKS; Int_Counter++)
	{
		Tick_CB[Int_Counter]++;
	}
}

// ******************
// INTERRUPTION INT0
// ******************
ISR(INT0_vect)
{	
	Usart0_Tx_String("Alarme sonne");Usart0_Tx(0X0D);
}

// ***************************************
// INTERRUPTION USART0 en RX (TERMINAL PC)
// ***************************************
ISR(USART0_RX_vect)
{
	buf_USART0[idxbuf_USART0] = UDR0;		 //Lire le registre de réception, le charger dans le buffer
	if (buf_USART0[idxbuf_USART0]=='@') 
	{
		Usart0_Tx(buf_USART0[idxbuf_USART0]);//Transmettre le caractère en retour 
		buf_USART0[++idxbuf_USART0] = 0;	// Caractère 'NULL' de fin de chaîne 
		USART0_Reception = TRUE;
		idxbuf_USART0 = 0;
		//Transmettre retour chariot ('\r' + '\n')
		Usart0_Tx('\r');
		Usart0_Tx('\n');
		Usart0_Tx('>');  // Transmettre un prompt
	}
	else
	{
		//Transmettre le caractère en retour 
		Usart0_Tx(buf_USART0[idxbuf_USART0]);
		//Si on arrive au maximum du buffer, remettre à zéro
		if (++idxbuf_USART0 >= MAXBUFUSART0) idxbuf_USART0 = 0;
	}
}

//Interruption Touches
ISR(PCINT2_vect)
{
	// tester	PINC, la variable Button mémorise la touche appuyée.
	char comp_PINC = ~PINC;
	//push test
	if (comp_PINC & (1<<PINC3))
	Button = UP;
	else if (comp_PINC & (1<<PINC4))
	Button = DOWN;
	else if (comp_PINC & (1<<PINC5))
	Button = LEFT;
	else if (comp_PINC & (1<<PINC6))
	Button = RIGHT;
	else if (comp_PINC & (1<<PINC7))
	Button = ENTER;
	else
	Button = NONE;	
}








