/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_adc.c
** Last modified Date:  20184-12-30
** Last Version:        V1.00
** Descriptions:        functions to manage A/D interrupts
** Correlated files:    adc.h
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "adc.h"
#include "../GLCD/GLCD.h"
#include <stdlib.h>

/*----------------------------------------------------------------------------
  A/D IRQ: Executed when A/D Conversion is ready (signal from ADC peripheral)
 *----------------------------------------------------------------------------*/
unsigned short AD_current;   
unsigned short AD_last = 0xFF;
extern int k;
int x1p=95,x2p=144,y1p=278,y2p=287;
int numpos = 15;


void ADC_IRQHandler(void) {
	AD_current = ((LPC_ADC->ADGDR>>4) & 0xFF0);
  
 if(abs(AD_current - AD_last) > 150) {
		
  if(AD_current > AD_last){
		if(x2p < 239-numpos) {
	
			for(k=0;k<numpos;k++) {
				LCD_DrawLine( x2p+1+k, y1p, x2p+1+k, y2p, Green);
			}

			for(k=0;k<numpos;k++) {
				LCD_DrawLine( x1p+k, y1p, x1p+k, y2p, Black);
			}

		x1p = x1p + k;
		x2p = x2p + k;
		
		}	
	} 
	
	else if(AD_current < AD_last){
		if(x1p > numpos) {
			for(k=0;k<numpos;k++) {
				LCD_DrawLine( x1p-k-1, y1p, x1p-k-1, y2p, Green);
			}

			for(k=0;k<numpos;k++) {
				LCD_DrawLine( x2p-k, y1p, x2p-k, y2p, Black);
			}

		x1p = x1p - k;
		x2p = x2p - k;
		
		}
	}
	
} 
  AD_last = AD_current;	
}
