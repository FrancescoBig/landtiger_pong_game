/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../GLCD/GLCD.h"
#include "../timer/timer.h"
#include "../adc/adc.h"
/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
volatile int k;
extern uint8_t button;
extern int x1,x2,y1,y2;
extern uint16_t angolo;
extern uint8_t punteggio1, punteggio2;
extern int x1p,x2p,x1p2,x2p2;

void deleteGame() {
	for(k=0;k<10;k++) {
		LCD_DrawLine(5, 32+k, 234, 32+k, Black);
	}
	for(k=0;k<10;k++) {
		LCD_DrawLine(5, 278+k, 234, 278+k, Black);
	}
	for(k=0;k<10;k++) {
		LCD_DrawLine(x1, y1+k, x2, y2+k, Black);
	}
}

void RIT_IRQHandler (void)
{	
	static uint8_t isEnabled = 1;	
	static int down = 0;
	down++;

	ADC_start_conversion();	
	
	if(button == 1 && (LPC_GPIO2->FIOPIN & (1<<11)) == 0){
		reset_RIT();
		switch(down){
			case 1:
				if(isEnabled == 1 && y1 < 297 && y1 > 18) {
					for(k=0;k<5;k++) {
					LCD_DrawLine( 118, 273+k, 122, 273+k, Black);
					}
		
				enable_timer(0);
				}
				else disable_RIT();
			break;
		default:
			break;
		}
	}
	
	else if(button == 2 && (LPC_GPIO2->FIOPIN & (1<<12)) == 0){
		reset_RIT();
		switch(down){
			case 1:	
			if(isEnabled == 1 && y1 < 297 && y1 > 18 && y1 != 158) {
				disable_timer(0);
				isEnabled = 0;
				GUI_Text(95, 170, (uint8_t *) " Pause ", White, Black);
				disable_RIT();
			}		
			else if(isEnabled == 0){
				enable_timer(0);
				isEnabled = 1;
				GUI_Text(95, 170, (uint8_t *) " Pause ", Black, Black);
			}
			else disable_RIT();	
			break;
		default:
			break;
		}
	}	

	else if(button == 0 && (LPC_GPIO2->FIOPIN & (1<<10)) == 0){
		reset_RIT();
		switch(down){
			case 1:
				if(isEnabled == 0 || punteggio1 == 5 || punteggio2 == 5) {	
					disable_timer(0);
					reset_timer(0);
					reset_timer(1);
					disable_RIT();
					deleteGame();
					if(isEnabled == 0) GUI_Text(95, 170, (uint8_t *) " Pause ", Black, Black);
					isEnabled = 1;
					x1=230,y1=158,x2=234,y2=158;
					angolo = 225;
					x1p=95,x2p=144;
					x1p2=95,x2p2=144;
						if(punteggio1 == 5) {
							GUI_TextInverse(155, 20, (uint8_t *) " You Lose ", Black, Black);
							GUI_Text(80, 300, (uint8_t *) " You Win ", Black, Black);
						}
						if(punteggio2 == 5) {
							GUI_TextInverse(155, 20, (uint8_t *) " You Win ", Black, Black);
							GUI_Text(80, 300, (uint8_t *) " You Lose ", Black, Black);
						}
					punteggio1 = 0;
					punteggio2 = 0;
					StartTable();
				}
				break;
			default:
				break;
		}
	}	
	
	
	else {	/* button released */
		down=0;
			
		NVIC_EnableIRQ(EINT0_IRQn);
		LPC_PINCON->PINSEL4    |= (1 << 20);
			
		NVIC_EnableIRQ(EINT1_IRQn);
		LPC_PINCON->PINSEL4    |= (1 << 22);
				
		NVIC_EnableIRQ(EINT2_IRQn);
		LPC_PINCON->PINSEL4    |= (1 << 24);
		
	}				
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
}
	

/******************************************************************************
**                            End Of File
******************************************************************************/
