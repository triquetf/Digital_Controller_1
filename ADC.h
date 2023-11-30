#ifndef _ADC_H_
#define _ADC_H_

// DEFINE

// FONCTIONS VISIBLES
void ADC_init(void);
void ADC_ON(unsigned char Canal_Nbr);
void ADC_OFF()	;
unsigned int Conversion_ADC_10bits(void);

#endif 
