 /*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h" 
#include "../RIT/RIT.h"
#include <stdio.h>

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
 extern int k;
 int x1=230,y1=158,x2=234,y2=158;
 extern int x1p,x2p;
 int count = 0;
 uint16_t angolo = 225;
 uint16_t angolold = 0;
 int punteggio = 0;
 char str[10];
 int record = 100;
 
void TIMER0_IRQHandler (void)
{		
	if(angolo == 225) {
		
		for(k=0;k<5;k++) {
			LCD_DrawLine( x1, y1+k, x2, y2+k, Green);
		}
			
		if(count == 0) {
			if(angolold == 315) {
				for(k=0;k<5;k++) {
					LCD_DrawLine( x1-5, y1-5+k, x2-5, y2-5+k, Black);
		}
	}
			else if (angolold == 135){
				for(k=0;k<5;k++) {
					LCD_DrawLine( x1+5, y1+5+k, x2+5, y2+5+k, Black);
			}	
		}
			else if(angolold == 330) {
				for(k=0;k<5;k++) {
					LCD_DrawLine( x1-5, y1-2+k, x2-5, y2-2+k, Black);
		}
	}
			else if (angolold == 150){
				for(k=0;k<5;k++) {
					LCD_DrawLine( x1+5, y1+2+k, x2+5, y2+2+k, Black);
			}	
		}
	}
	
		if(count != 0) {	
			for(k=0;k<5;k++) {
				LCD_DrawLine( x1+5, y1-5+k, x2+5, y2-5+k, Black);
		}	 
	}	
			x1=x1-5;
			y1=y1+5;
			x2=x2-5;
			y2=y2+5;
		
			count++;
			disable_timer(1);
			reset_timer(1);
	
		if(y1 == 268)	{
		
			if(x1 >= x1p && x2 <= x2p) {
				
				if((x2-x1p) < 15 || (x2p-x1) < 15) angolo = 150;
				else angolo = 135;
				
				count = 0;
				angolold = 225;
				init_timer(1, 0x848);
				enable_timer(1);
				if(punteggio < 100) punteggio += 5;
				else punteggio +=10;
				sprintf(str,"%d",punteggio);
				GUI_Text(7, 160, (uint8_t *) str, White, Black);
				if(punteggio > record) record = punteggio;
				sprintf(str,"%d",record);
				GUI_Text(210, 7, (uint8_t *) str, White, Black);
				}
			else {}
		}
		if(x1 == 5) {
			angolo = 315;
			count = 0;
			angolold = 225;
			init_timer(1, 0x424);
			enable_timer(1);
		}
	}
	
	else if(angolo == 135) {
		
		for(k=0;k<5;k++) {
			LCD_DrawLine( x1, y1+k, x2, y2+k, Green);
		}
		if(count == 0) {
			if(angolold == 225) {
				for(k=0;k<5;k++) {
					LCD_DrawLine( x1+5, y1-5+k, x2+5, y2-5+k, Black);	
				}
			}
			else if (angolold == 45){
				for(k=0;k<5;k++) {
					LCD_DrawLine( x1-5, y1+5+k, x2-5, y2+5+k, Black);
				}	 
			}
			else if (angolold == 210){
				for(k=0;k<5;k++) {
					LCD_DrawLine( x1+5, y1-2+k, x2+5, y2-2+k, Black);
				}	 
			}
			else if (angolold == 30){
				for(k=0;k<5;k++) {
					LCD_DrawLine( x1-5, y1+2+k, x2-5, y2+2+k, Black);
				}	 
			}			
		}	
		if(count != 0) {		
			for(k=0;k<5;k++) {
				LCD_DrawLine( x1+5, y1+5+k, x2+5, y2+5+k, Black);
			}
		} 	
			x1=x1-5;
			y1=y1-5;
			x2=x2-5;
			y2=y2-5;

			count++;
			disable_timer(1);
			reset_timer(1);

		if(x1 == 5 && y1 != 8) {
			angolo = 45;
			count = 0;
			angolold = 135;
			init_timer(1, 0x424);
			enable_timer(1);
		}
		if(y1 == 8 && x1 != 5) {
			angolo = 225;
			count = 0;
			angolold = 135;
			init_timer(1, 0x424);
			enable_timer(1);
		}
		if(y1 == 8 && x1 == 5) {
			angolo = 315;
			count = 0;
			angolold = 135;
			init_timer(1, 0x424);
			enable_timer(1);
		}
	}
	
	else if(angolo == 45) {
		
		for(k=0;k<5;k++) {
			LCD_DrawLine( x1, y1+k, x2, y2+k, Green);
		}
				
		if(count == 0) {
			if(angolold == 315) {
				for(k=0;k<5;k++) {
					LCD_DrawLine( x1-5, y1-5+k, x2-5, y2-5+k, Black);
				}
			}
			else if (angolold == 135){
				for(k=0;k<5;k++) {
					LCD_DrawLine( x1+5, y1+5+k, x2+5, y2+5+k, Black);
				}	
			}
			else if (angolold == 330){
				for(k=0;k<5;k++) {
					LCD_DrawLine( x1-5, y1-2+k, x2-5, y2-2+k, Black);
				}	
			}
			else if (angolold == 150){
				for(k=0;k<5;k++) {
					LCD_DrawLine( x1+5, y1+2+k, x2+5, y2+2+k, Black);
				}	
			}
		}
		
		if(count != 0) {	
				for(k=0;k<5;k++) {
					LCD_DrawLine( x1-5, y1+5+k, x2-5, y2+5+k, Black);
				}	 
		}		
			x1=x1+5;
			y1=y1-5;
			x2=x2+5;
			y2=y2-5;
		
			count++;
			disable_timer(1);
			reset_timer(1);
	
		if(y1 == 8 && x2 != 234) {
			angolo = 315;
			count = 0;
			angolold = 45;
			init_timer(1, 0x424);
			enable_timer(1);
		}		
		if(x2 == 234 && y1 != 8) {
			angolo = 135;
			count = 0;
			angolold = 45;
			init_timer(1, 0x424);
			enable_timer(1);
		}
		if(x2 == 234 && y1 == 8) {
			angolo = 225;
			count = 0;
			angolold = 45;
			init_timer(1, 0x424);
			enable_timer(1);
		}
	}
		
	else if(angolo == 315) {
		
		for(k=0;k<5;k++) {
			LCD_DrawLine( x1, y1+k, x2, y2+k, Green);
		}
		
		if(count == 0) {
			if(angolold == 225) {
				for(k=0;k<5;k++) {
					LCD_DrawLine( x1+5, y1-5+k, x2+5, y2-5+k, Black);	
				}
			}
			
			else if (angolold == 45){
				for(k=0;k<5;k++) {
					LCD_DrawLine( x1-5, y1+5+k, x2-5, y2+5+k, Black);
				}	 
			}
			else if(angolold == 210) {
				for(k=0;k<5;k++) {
					LCD_DrawLine( x1+5, y1-2+k, x2+5, y2-2+k, Black);	
				}
			}
			
			else if (angolold == 30){
				for(k=0;k<5;k++) {
					LCD_DrawLine( x1-5, y1+2+k, x2-5, y2+2+k, Black);
				}	 
			}
		}
		
		if(count != 0) {	
			for(k=0;k<5;k++) {
				LCD_DrawLine( x1-5, y1-5+k, x2-5, y2-5+k, Black);
			}
		}		
		
			x1=x1+5;
			y1=y1+5;
			x2=x2+5;
			y2=y2+5;
		
			count++;
			disable_timer(1);
			reset_timer(1);
	
		if(x2 == 234) {
			angolo = 225;	
			count = 0;
			angolold = 315;
			init_timer(1, 0x424);
			enable_timer(1);
		}
		if(y1 == 268) {
			if(x1 >= x1p && x2 <= x2p) {
				
				if((x2-x1p) < 15 || (x2p-x1) < 15) angolo = 30;
				else angolo = 45;
				
				count = 0;
				angolold = 315;
				init_timer(1, 0x848);
				enable_timer(1);
				if(punteggio<100) punteggio += 5;
				else punteggio += 10;
				sprintf(str,"%d",punteggio);
				GUI_Text(7, 160, (uint8_t *) str, White, Black);
				if(punteggio > record) record = punteggio;
				sprintf(str,"%d",record);
				GUI_Text(210, 7, (uint8_t *) str, White, Black);
			}
			else {}
		}
	}
	
	else if(angolo == 150) {
		
		if(count == 0) {
			if(angolold == 225) {
				for(k=0;k<5;k++) {
					LCD_DrawLine( x1+5, y1-5+k, x2+5, y2-5+k, Black);	
				}
			}
			else if (angolold == 45){
				for(k=0;k<5;k++) {
					LCD_DrawLine( x1-5, y1+5+k, x2-5, y2+5+k, Black);
				}	 
			} 
			else if (angolold == 210){
				for(k=0;k<5;k++) {
					LCD_DrawLine( x1+5, y1-2+k, x2+5, y2-2+k, Black);
				}	 
			}
			else if (angolold == 30){
				for(k=0;k<5;k++) {
					LCD_DrawLine( x1-5, y1+2+k, x2-5, y2+2+k, Black);
				}	 
			}
		}	
		if(count != 0) {		
			for(k=0;k<5;k++) {
				LCD_DrawLine( x1+5, y1+2+k, x2+5, y2+2+k, Black);
			}	
		}
		for(k=0;k<5;k++) {
			LCD_DrawLine( x1, y1+k, x2, y2+k, Green);
		}		
			x1=x1-5;
			y1=y1-2;
			x2=x2-5;
			y2=y2-2;

			count++;
			disable_timer(1);
			reset_timer(1);
		
		if(x1 == 5 && y1 != 8) {
			angolo = 30;
			count = 0;
			angolold = 150;
			init_timer(1, 0x424);
			enable_timer(1);
		}
		if(y1 == 8 && x1 != 5) {
			angolo = 210;
			count = 0;
			angolold = 150;
			init_timer(1, 0x424);
			enable_timer(1);
		}
		if(y1 == 8 && x1 == 5) {
			angolo = 330;
			count = 0;
			angolold = 150;
			init_timer(1, 0x424);
			enable_timer(1);
		}
	}
	
	else if(angolo == 30) {
		
		if(count == 0) {
			if(angolold == 315) {
				for(k=0;k<5;k++) {
					LCD_DrawLine( x1-5, y1-5+k, x2-5, y2-5+k, Black);
				}
			}
			else if (angolold == 135){
				for(k=0;k<5;k++) {
					LCD_DrawLine( x1+5, y1+5+k, x2+5, y2+5+k, Black);
				}	
			}
			else if (angolold == 330){
				for(k=0;k<5;k++) {
					LCD_DrawLine( x1-5, y1-2+k, x2-5, y2-2+k, Black);
				}	
			}
			else if (angolold == 150){
				for(k=0;k<5;k++) {
					LCD_DrawLine( x1+5, y1+2+k, x2+5, y2+2+k, Black);
				}	
			}
		}
		
		if(count != 0) {	
				for(k=0;k<5;k++) {
					LCD_DrawLine( x1-5, y1+2+k, x2-5, y2+2+k, Black);
				}	 
		}	
		
		for(k=0;k<5;k++) {
			LCD_DrawLine( x1, y1+k, x2, y2+k, Green);
		}		
			x1=x1+5;
			y1=y1-2;
			x2=x2+5;
			y2=y2-2;
		
			count++;
			disable_timer(1);
			reset_timer(1);
	
		if(y1 == 8 && x2 != 234) {
			angolo = 330;
			count = 0;
			angolold = 30;
			init_timer(1, 0x424);
			enable_timer(1);
		}		
		if(x2 == 234 && y1 != 8) {
			angolo = 150;
			count = 0;
			angolold = 30;
			init_timer(1, 0x424);
			enable_timer(1);
		}
		if(x2 == 234 && y1 == 8) {
			angolo = 210;
			count = 0;
			angolold = 30;
			init_timer(1, 0x424);
			enable_timer(1);
		}
	}
	
	else if(angolo == 210) {
		
		if(count == 0) {
			if(angolold == 315) {
				for(k=0;k<5;k++) {
					LCD_DrawLine( x1-5, y1-5+k, x2-5, y2-5+k, Black);
		}
	}
			else if (angolold == 135){
				for(k=0;k<5;k++) {
					LCD_DrawLine( x1+5, y1+5+k, x2+5, y2+5+k, Black);
			}	
		}
			else if(angolold == 330) {
				for(k=0;k<5;k++) {
					LCD_DrawLine( x1-5, y1-2+k, x2-5, y2-2+k, Black);
		}
	}
			else if (angolold == 150){
				for(k=0;k<5;k++) {
					LCD_DrawLine( x1+5, y1+2+k, x2+5, y2+2+k, Black);
			}	
		}
	}
	
		if(count != 0) {	
			for(k=0;k<5;k++) {
				LCD_DrawLine( x1+5, y1-2+k, x2+5, y2-2+k, Black);
		}	 
	}	
		for(k=0;k<5;k++) {
			LCD_DrawLine( x1, y1+k, x2, y2+k, Green);
		}
			x1=x1-5;
			y1=y1+2;
			x2=x2-5;
			y2=y2+2;
		
			count++;
			disable_timer(1);
			reset_timer(1);
		
		if(y1 == 268)	{
		
			if(x1 >= x1p && x2 <= x2p) {
				
				if((x2-x1p) < 15 || (x2p-x1) < 15) angolo = 135;
				else angolo = 150;
				
				count = 0;
				angolold = 210;
				init_timer(1, 0x848);
				enable_timer(1);
				if(punteggio < 100) punteggio += 5;
				else punteggio +=10;
				sprintf(str,"%d",punteggio);
				GUI_Text(7, 160, (uint8_t *) str, White, Black);
				if(punteggio > record) record = punteggio;
				sprintf(str,"%d",record);
				GUI_Text(210, 7, (uint8_t *) str, White, Black);
			}
			else {}
		}
		if(x1 == 5) {
			angolo = 330;
			count = 0;
			angolold = 210;
			init_timer(1, 0x424);
			enable_timer(1);
		}
	}
	
	else if(angolo == 330) {
		
		if(count == 0) {
			if(angolold == 225) {
				for(k=0;k<5;k++) {
					LCD_DrawLine( x1+5, y1-5+k, x2+5, y2-5+k, Black);	
				}
			}
			
			else if (angolold == 45){
				for(k=0;k<5;k++) {
					LCD_DrawLine( x1-5, y1+5+k, x2-5, y2+5+k, Black);
				}	 
			}
			else if(angolold == 210) {
				for(k=0;k<5;k++) {
					LCD_DrawLine( x1+5, y1-2+k, x2+5, y2-2+k, Black);	
				}
			}
			
			else if (angolold == 30){
				for(k=0;k<5;k++) {
					LCD_DrawLine( x1-5, y1+2+k, x2-5, y2+2+k, Black);
				}	 
			}
		}
		
		if(count != 0) {	
			for(k=0;k<5;k++) {
				LCD_DrawLine( x1-5, y1-2+k, x2-5, y2-2+k, Black);
			}
		}	
		
		for(k=0;k<5;k++) {
			LCD_DrawLine( x1, y1+k, x2, y2+k, Green);
		}
			x1=x1+5;
			y1=y1+2;
			x2=x2+5;
			y2=y2+2;
		
			count++;
			disable_timer(1);
			reset_timer(1);
	
		if(x2 == 234) {
			angolo = 210;	
			count = 0;
			angolold = 330;
			init_timer(1, 0x424);
			enable_timer(1);
		}
		if(y1 == 268) {
			if(x1 >= x1p && x2 <= x2p) {
				
				if((x2-x1p) < 15 || (x2p-x1) < 15) angolo = 45;
				else angolo = 30;
				
				count = 0;
				angolold = 330;
				init_timer(1, 0x848);
				enable_timer(1);
				if(punteggio<100) punteggio += 5;
				else punteggio += 10;
				sprintf(str,"%d",punteggio);
				GUI_Text(7, 160, (uint8_t *) str, White, Black);
				if(punteggio > record) record = punteggio;
				sprintf(str,"%d",record);
				GUI_Text(210, 7, (uint8_t *) str, White, Black);	
			}
			else {}
		}
	}
	
	if(y1 == 298) {
		disable_timer(0);
		disable_RIT();
		GUI_Text(80, 170, (uint8_t *) " You Lose ", White, Black);
	}
	
	
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
uint16_t SinTable[45] =
{
    410, 467, 523, 576, 627, 673, 714, 749, 778,
    799, 813, 819, 817, 807, 789, 764, 732, 694, 
    650, 602, 550, 495, 438, 381, 324, 270, 217,
    169, 125, 87 , 55 , 30 , 12 , 2  , 0  , 6  ,   
    20 , 41 , 70 , 105, 146, 193, 243, 297, 353
};
void TIMER1_IRQHandler (void)
{
		static int ticks=0;
	/* DAC management */	
	LPC_DAC->DACR = SinTable[ticks]<<6;
	ticks++;
	if(ticks==45) ticks=0;

  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
