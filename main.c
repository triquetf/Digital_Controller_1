// INCLUDE
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>	// Manipulation de chaînes de caractères
#include <stdlib.h> // pour utiliser la fonction itoa()

#include "Main.h"
#include "OS.h"
#include "Hardware.h"
#include "USART.h"
#include "lcd.h"
#include "ADC.h"
#include "ftoa.h"
#include "PWM.h"

// Mes variables globales
unsigned char IDCB_Led = 0;			// Identificateur callback timer pour le clignotement de la LED

//****************** fonction principale *****************
int main (void)
{
 	//Initialisation hardware 
	Init_Hardware();
	//Initilisation LCD
	lcd_init();
	lcd_on();
	lcd_disable_cursor();
	lcd_set_cursor(0,0);
	
	
	//Initialisation ADC
	ADC_init();
	// Initialisation PWM
	
	
	// Initialisation des Callbacks
	OS_Init();
 	IDCB_Led = Callbacks_Record_Timer(Switch_LED, 500);
	
	Callbacks_Record_Usart0_RX(USART0_RX);

 	// Lancement OS (Boucle infinie)
	OS_Start();
	//N'arrive jamais ici
	return 0; 
}

//**************** Switch LED ************************************
//  Signalisation par clignotement de la LED  pendant 500 ms 
//****************************************************************
void Switch_LED(void)
{
	TOGGLE_IO(PORTD,PORTD7);
}


//****************USART0_RX*************************
// Appelé quand on a reçu un message du terminal PC
//**************************************************
void USART0_RX(volatile char *Trame_USART0)
{
        
}
		
	
	//*****************************************
	//           STATE MACHINE
	//*****************************************
	
	
	char Date(char input)
	{
		// Maxime P. & Florent
		//return ST_FCT_DATE;
		return ST_TXT_TIME;
	}
	
	char Time(char input)
	{
		// Maxime P. & Florent M.
		//return ST_TXT_SENSOR;
		return ST_TXT_CLOCK;
	}
	
	char Adc(char input)
	{
		// Someone 
		return ST_TXT_ACTUATOR;
	}
	
	char Current(char input)
	{
		
		// Lukman N. & Rémi G
		return ST_TXT_ACTUATOR;
	}
	
	char Thermocouple(char input)
	{
		
		// Pierre C. & Arnaud D.
		return ST_TXT_ACTUATOR;
	}
	
	char Dac(char input)
	{
		// Pierre B.
		return ST_TXT_STORAGE;
	}
	
	char Relay(char input)
	{
		// Someone
		return ST_TXT_STORAGE;
	}
	
	char Pwm_1(char input)
	{
		// Pierre B.
		return ST_TXT_STORAGE;
	}
	
	char Pwm_1_2(char input)
	{
		// Pierre B.
		return ST_TXT_STORAGE;
	}
	
	char Pwm_1_2_3(char input)
	{
		// Pierre B.
		return ST_TXT_STORAGE;
	}
	
	char Periode(char input)
	{
		// Pierre B.
		//return ST_FCT_PERIODE;
		return ST_TXT_STORAGE;
	}
	
	char Resolution(char input)
	{
		// Pierre B.
		//return ST_FCT_RESOLUTION;
		return ST_TXT_PWM_SETUP;
	}
	
	char Dent_Scie(char input)
	{
		// Pierre B.
		return ST_TXT_STORAGE;
	}
	
	char Isocele(char input)
	{
		// Pierre B.
		return ST_TXT_STORAGE;
	}
	
	char Eeprom(char input)
	{
		// Florimond H. & Smaïn J.
		return ST_TXT_MONITORING;
	}
	
	char Sram(char input)
	{
		// Thibault T. & Maxime M.
		return ST_TXT_MONITORING;
	}
	
	char Monitoring(char input)
	{
		// Someone
		return ST_TXT_CONTRAST;
	}
	
	char Contrast(char input)
	{
		// Pierre C. & Arnaud D.
		return ST_TXT_DEBUG;
	}
	
	char Debug(char input)
	{
		// Someone
		return ST_TXT_SETUP;
	}
	
	char Sampling_Time(char input)
	{
		// Florimond H. & Smaïn J.
		//return ST_FCT_SAMPLING_TIME;
		return ST_TXT_ON_OFF;
	}
	
	char Duration(char input)
	{
		// Florimond H. & Smaïn J.
		//return ST_FCT_DURATION;
		return ST_TXT_ON_OFF;
	}
	
	char Datalogger_On_Off(char input)
	{
		// Florimond H. & Smaïn J.
		return ST_TXT_DATA_TRANSFER;
	}
	
	char Transfer_Usart(char input)
	{
		// Florimond H. & Smaïn J.
		//return ST_FCT_DATA_TRANSFER;
		return ST_TXT_DATALOGGER;
	}
	
	char Sampling_CTRL(char input)
	{
		// Pierre C., Arnaud D., Thibault T.,  Maxime M., Maxime P., Florent M., Lukman N., Rémi G., Charles M., Denis B.
		//return ST_FCT_SAMPLING_CTRL;
		return ST_TXT_MANUAL_MODE;
	}

	char Manual_Mode(char input)
	{
		// Pierre C., Arnaud D., Thibault T.,  Maxime M., Maxime P., Florent M., Lukman N., Rémi G., Charles M., Denis B.
		//return ST_FCT_MANUAL_MODE;
		return ST_TXT_AUTO_MODE;
	}
	
	char Auto_Mode(char input)
	{
		// Pierre C., Arnaud D., Thibault T.,  Maxime M., Maxime P., Florent M., Lukman N., Rémi G., Charles M., Denis B.
		//return ST_FCT_AUTO_MODE;
		return ST_TXT_MANUAL_MODE;
	}
	
	char Pid_P(char input)
	{
		// Lukman N. & Rémi G.
		//return ST_FCT_P;
		return ST_TXT_I;
	}
	
	char Pid_I(char input)
	{
		// Lukman N. & Rémi G
		//return ST_FCT_I;
		return ST_TXT_D;
	}
	
	
	char Pid_D(char input)
	{
		// Lukman N. & Rémi G
		//return ST_FCT_D;
		return ST_TXT_WINDUP;
	}
	
	
	char Pid_WindUp(char input)
	{
		// Lukman N. & Rémi G
		//return ST_FCT_WINDUP;
		return ST_TXT_SAMPLING_CTRL;
	}
	
	char Recursion(char input)
	{
		// Pierre C., Arnaud D., Thibault T.,  Maxime M., Maxime P., Florent M., Charles M., Denis B.
		// Download fichier CSV commun !
		return ST_TXT_SAMPLING_CTRL;
	}
	
	char Smith(char input)
	{
		// Charles M. & Denis B.
		// Download fichier CSV commun !
		return ST_TXT_SAMPLING_CTRL;
	}
	
	char Internal_Model(char input)
	{
		// Maxime P. & Florent M.
		// Download fichier CSV commun !
		return ST_TXT_MODEL_SETTING;
	}
	
	char Internal_Model_Setting(char input)
	{
		// Maxime P. & Florent M.
		// Download fichier CSV commun !
		//return ST_FCT_MODEL_SETTING;
		return ST_TXT_SAMPLING_CTRL;
	}
	
	char Rst(char input)
	{
		// Thibault T. & Maxime M.
		// Download fichier CSV commun !
		return ST_TXT_SAMPLING_CTRL;
	}
	
	char Pwm_Manual(char input)
	{
		// Pierre B.
		//return ST_FCT_MANUAL_MODE_PWM;
		return ST_TXT_PWM;
	}


	char Pwm_Sinus(char input)
	{
		// Pierre B.
		//return ST_FCT_MODE_SINUS;
		return ST_TXT_PWM;
	}

	char Sinus_Amplitude(char input)
	{
		// Pierre B.
		//return ST_FCT_SINUS_AMPLITUDE;
		return ST_TXT_ON_OFF_SINUS;
	}
	char Sinus_Periode(char input)
	{
		// Pierre B.
		//return ST_FCT_SINUS_PERIODE;
		return ST_TXT_ON_OFF_SINUS;
	}
	
	char Sinus_On_Off(char input)
	{
		// Pierre B.
		//return ST_FCT_ON_OFF_SINUS;
		return ST_TXT_SINUS;
	}
	
	
	
	int EDIT_VALUE_0_99(int Initial_Value, char input)
	{
		char String[4];
		switch (input)
		{
			case DOWN :
			{
				Initial_Value--;
				if (Initial_Value == -1) Initial_Value = 99;
				itoa(Initial_Value, String, 10);
				//cli();lcd_gotoxy(0,1);lcd_puts("                ");lcd_gotoxy(0,1);lcd_puts(String);sei();
				break;
			}
			case UP :
			{
				Initial_Value++;
				if (Initial_Value == 100) Initial_Value = 0;
				itoa(Initial_Value, String, 10);
				//cli();lcd_gotoxy(0,1);lcd_puts("                ");lcd_gotoxy(0,1);lcd_puts(String);sei();
				break;
			}
			case LEFT :
			{
				Initial_Value = Initial_Value - 10;
				if (Initial_Value <0) Initial_Value = 0;
				itoa(Initial_Value, String, 10);
				//cli();lcd_gotoxy(0,1);lcd_puts("                ");lcd_gotoxy(0,1);lcd_puts(String);sei();
				break;
			}
			case RIGHT :
			{
				Initial_Value = Initial_Value + 10;
				if (Initial_Value > 99) Initial_Value = 99;
				itoa(Initial_Value, String, 10);
				//cli();lcd_gotoxy(0,1);lcd_puts("                ");lcd_gotoxy(0,1);lcd_puts(String);sei();
				break;
			}
		}
		return Initial_Value;
	}