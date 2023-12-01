#ifndef _main_h_
#define _main_h_

// INCLUDE (si applicable)
// TEST GIT - BRANCH
// DEFINE 


// Gestion registre par bit unique
#define SET_BIT(port,bit)  (port |= (1<<bit))   //set bit in port
#define CLR_BIT(port,bit)  (port &= ~(1<<bit))  //clear bit in port
#define TOGGLE_IO(port,bit) (port ^= (1<<bit))  //toggle

#define TRUE				1
#define FALSE				0

#ifndef NULL
#define NULL	0
#endif

enum {NONE,UP, DOWN, LEFT, RIGHT, ENTER};	// Used with the button variable


#define _8MHZ

// STATE MACHINE
// Niv Superieur
#define ST_TXT_WELCOME		1

// FOCTIONNALITES , HORIZONTAL
#define ST_TXT_SETUP		2
#define ST_TXT_DATALOGGER	3
#define ST_TXT_CONTROL		4
#define ST_TXT_PWM			5
#define ST_TXT_SINUS		6

// DETAILS FONCTIONNALITES, VERTICAL
// SETUP
#define ST_TXT_CLOCK		7
#define ST_TXT_SENSOR		8
#define ST_TXT_ACTUATOR		9
#define ST_TXT_STORAGE		10
#define ST_TXT_MONITORING	11
#define ST_TXT_CONTRAST		12
#define ST_TXT_DEBUG		13

// DATALOGGER
#define ST_TXT_PARAMETERS_DL	14
#define ST_TXT_ON_OFF			15
#define ST_TXT_DATA_TRANSFER	16

// DIGITAL CONTROL
#define ST_TXT_PARAMETERS_CTRL	17
#define ST_TXT_SAMPLING_CTRL	18
#define ST_TXT_MANUAL_MODE		19
#define ST_TXT_AUTO_MODE		20

// PWM
#define ST_TXT_MANUAL_MODE_PWM	21
#define ST_TXT_MODE_SINUS		22

// SINUS
#define ST_TXT_PARAMETERS_SINUS	23
#define ST_TXT_ON_OFF_SINUS		24

// DETAILS SOUS-FONCTIONNALITES, HORIZONTAL

// SETUP
#define ST_TXT_DATE				25
#define ST_TXT_TIME				26

#define ST_TXT_ADC				27
#define ST_TXT_CURRENT			28
#define ST_TXT_THERMOCOUPLE		29

#define ST_TXT_DAC				30
#define ST_TXT_PWM_SETUP		31
#define ST_TXT_RELAY			32

#define ST_TXT_PWM_1			33
#define ST_TXT_PWM_1_2			34
#define ST_TXT_PWM_1_2_3		35
#define ST_TXT_PWM_TRIANGLE		36
#define ST_TXT_PERIODE			37
#define ST_TXT_RESOLUTION		38

#define ST_TXT_DENT_SCIE		39
#define ST_TXT_ISOCELE			40

#define ST_TXT_EEPROM			41
#define ST_TXT_SRAM				42

#define ST_FCT_DATE				43
#define ST_FCT_TIME				44
#define ST_FCT_ADC				45
#define ST_FCT_CURRENT			46
#define ST_FCT_THERMOCOUPLE		47
#define ST_FCT_DAC				48
#define ST_FCT_RELAY			49
#define ST_FCT_PWM_1			50
#define ST_FCT_PWM_1_2			51
#define ST_FCT_PWM_1_2_3		52
#define ST_FCT_PERIODE			53
#define ST_FCT_RESOLUTION		54
#define ST_FCT_DENT_SCIE		55
#define ST_FCT_ISOCELE			56
#define ST_FCT_EEPROM			57
#define ST_FCT_SRAM				58
#define ST_FCT_MONITORING		59
#define ST_FCT_CONTRAST			60
#define ST_FCT_DEBUG			61

// DATALOGGER
#define ST_TXT_SAMPLING_TIME	62
#define ST_TXT_DURATION			63

#define ST_FCT_ON_OFF			64
#define ST_FCT_DATA_TRANSFER	65

#define ST_FCT_SAMPLING_TIME	66
#define ST_FCT_DURATION			67

// DIGITAL CONTROL
#define ST_TXT_PID				68
#define ST_TXT_RECURSION		69
#define ST_TXT_SMITH			70
#define ST_TXT_MODEL			71
#define ST_TXT_RST				72

#define ST_FCT_SAMPLING_CTRL	73
#define ST_FCT_MANUAL_MODE		74
#define ST_FCT_AUTO_MODE		75

#define ST_TXT_P				76
#define ST_TXT_I				77
#define ST_TXT_D				78
#define ST_TXT_WINDUP			79
#define ST_FCT_P				80
#define ST_FCT_I				81
#define ST_FCT_D				82
#define ST_FCT_WINDUP			83

#define ST_TXT_MODEL_RECURSION	84
#define ST_TXT_MODEL_SETTING	85
#define ST_FCT_RECURSION		86
#define ST_FCT_SMITH			87
#define ST_FCT_MODEL			88
#define ST_FCT_MODEL_SETTING	89
#define ST_FCT_RST				90

#define ST_FCT_MANUAL_MODE_PWM	91
#define ST_FCT_MODE_SINUS		92

#define ST_TXT_SINUS_AMPLITUDE	93
#define ST_TXT_SINUS_PERIODE	94
#define ST_FCT_SINUS_AMPLITUDE	95
#define ST_FCT_SINUS_PERIODE	96
#define ST_FCT_ON_OFF_SINUS		97








//DECLARATION DES FONCTIONS

//CALLBACK
void Switch_LED(void);	// callback timer --> cligotement de la LED
void USART0_RX(volatile char *Trame_USART0);	// callback USART0 --> gestion de la commande recue via le port serie.

//STATE MACHINE
char Set_Pwm_Red(char input);
char Date(char input);
char Time(char input);
char Adc(char input);
char Current(char input);
char Thermocouple(char input);
char Dac(char input);
char Relay(char input);
char Pwm_1(char input);
char Pwm_1_2(char input);
char Pwm_1_2_3(char input);
char Periode(char input);
char Resolution(char input);
char Dent_Scie(char input);
char Isocele(char input);
char Eeprom(char input);
char Sram(char input);
char Monitoring(char input);
char Contrast(char input);
char Debug(char input);
char Sampling_Time(char input);
char Duration(char input);
char Datalogger_On_Off(char input);
char Transfer_Usart(char input);

char Sampling_CTRL(char input);
char Manual_Mode(char input);
char Auto_Mode(char input);

char Pid_P(char input);
char Pid_I(char input);
char Pid_D(char input);
char Pid_WindUp(char input);

char Recursion(char input);
char Smith(char input);
char Internal_Model(char input);
char Internal_Model_Setting(char input);
char Rst(char input);

char Pwm_Manual(char input);
char Pwm_Sinus(char input);

char Sinus_Amplitude(char input);
char Sinus_Periode(char input);
char Sinus_On_Off(char input);


//AUTRES
int EDIT_VALUE_0_99(int Initial_Value, char input);
int EDIT_VALUE(int Initial_Value, char input, int Value_Min, int Value_Max);

#endif
