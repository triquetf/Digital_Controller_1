#ifndef __FTOA_H
#define __FTOA_H

/******************************************************************
** 	        		  FUNCTION PROTOTYPES	    	  			 **
******************************************************************/

/**
 * Converts a float to a string
 *
 * @param	x				the float number to be converted
 * @param	str				the string in which the float will be converted
 * @param	prec			determines the digits after the point
 * @param	format			accepts only these values : 'f', 'F', 'g', 'G'
 * @return					string length
 */
int My_ftoa (float x, char *str, char prec, char format);

#endif /* __FTOA_H */