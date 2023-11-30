#ifndef __OS_H
#define __OS_H

//Définit le nombre maximal de callback de type Chrono
#define	MAX_CALLBACKS		10
#define MAXBUFUSART0		20

// PROTOTYPE DES FONCTIONS EXTERNES
//**********************************************************
//********** FONCTIONS POUR LE MOTEUR OS *******************
//**********************************************************

//Initialisation des Callbacks
void OS_Init(void);

//Enregistrer des fonctions callback liées au temps
//Retourne un ID associé à l'enregistrement
unsigned char Callbacks_Record_Timer(void(*pt_Function)(void), unsigned int Time); 

//Retirer des fonctions callback liées au temps, prend l'ID du CallBack comme argument
char Callbacks_Remove_Timer(unsigned char IDCB);

//Enregistrer des fonctions callback liées à l'USART
void Callbacks_Record_Usart0_RX(void(*ptFonction)(volatile char*));

//Retirer des fonctions callback liées à l'USART
void Callbacks_Remove_Usart0_RX(void);

//Démarrage de la boucle principale
void OS_Start(void);

//State MAchine
unsigned char StateMachine(char state, unsigned char stimuli);

#endif
