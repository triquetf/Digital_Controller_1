#define RTC_ADDRESS 0b1101000		//Adresse du RTC_DS3232

// Adresses de données RTC3232
enum {SECONDE,MINUTE,HEURE,JOUR,DATE,MOIS,ANNEE,
	SecAlarm1,MinAlarm1, HourAlarm1, DateAlarm1,
	MinAlarm2, HourAlarm2, DateAlarm2,
CONTROL, ControlStatus, AagingOffset, MSBTemps,LSBTemp};



void setSeconde (unsigned char data);
void setMinute (unsigned char data);
void setHeure (unsigned char data);
void setJour (unsigned char data);
void setDate (unsigned char data);
void setMois (unsigned char data);
void setAnnee (unsigned char data);

// Initialisation de la clock lorsqu'on
void RTC_Clock_Set(        unsigned char Sec,
unsigned char Min,
unsigned char Hrs,
unsigned char Day,
unsigned char Date,
unsigned char Month,
unsigned char Year);

void RTC_Alarm_Set(         unsigned char Sec,
unsigned char Min,
unsigned char Hrs,
unsigned char Date);

void RTC_Clock_Set_Date(	unsigned char Date,
unsigned char Month,
unsigned char Year);

void RTC_Clock_Set_Heure(	unsigned char Sec,
unsigned char Min,
unsigned char Heure);

void RTC_Clock_Read_All(void);

void RTC_Clock_Read_Byte(unsigned char Adr_Pointer);

unsigned char convertBCDtoChar(unsigned char AddressOfData, unsigned char Register_Data);

unsigned char convertchartoBCD(unsigned char addressofdata, unsigned char toconvert);