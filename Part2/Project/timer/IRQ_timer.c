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
 uint16_t angolo = 225;
 uint8_t punteggio1 = 0;
 uint8_t punteggio2 = 0;
 char str[10];
 int x1p2=95,x2p2=144;
 uint8_t speedpl2 = 3;
 uint8_t direction = 0;
 
void setScore() {
	if(y1 >= 267) {
	punteggio2 += 1;
	sprintf(str,"%d",punteggio2);
	GUI_TextInverse(231, 174, (uint8_t *) str, White, Black);
	}
	else if(y1 <= 44) {
	punteggio1 += 1;
	sprintf(str,"%d",punteggio1);
	GUI_Text(7, 160, (uint8_t *) str, White, Black);
	}
}

void setSound() {

	if((x1 >= x1p && x2 <= x2p && (y1 == 268 || y1 == 267)) || (x1 >= x1p2 && x2 <= x2p2 && (y1 == 43 || y1 == 44))) init_timer(1, 0x848);
	else init_timer(1, 0x424);
	enable_timer(1);

}
 
void TIMER0_IRQHandler (void)
{		
	if(angolo == 225) {

		for(k=0;k<5;k++) {
			LCD_DrawLine( x1, y1+k, x2, y2+k, Black);
		}	
			
		for(k=0;k<5;k++) {
			LCD_DrawLine( x1-5, y1+5+k, x2-5, y2+5+k, Green);
		}
			
			x1=x1-5;
			y1=y1+5;
			x2=x2-5;
			y2=y2+5;
		
			disable_timer(1);
			reset_timer(1);
	
		if(y1 == 268)	{
		
			if(x1 >= x1p && x2 <= x2p) {
				
				if((x2-x1p) < 15 || (x2p-x1) < 15) angolo = 150;
				else angolo = 135;
				
				setSound();
				}
			else {}
		}
		if(x1 == 5) {
			angolo = 315;
			setSound();
		}
	}
	
	else if(angolo == 135) {
		
		for(k=0;k<5;k++) {
			LCD_DrawLine( x1, y1+k, x2, y2+k, Black);
			}
		
		for(k=0;k<5;k++) {
			LCD_DrawLine( x1-5, y1-5+k, x2-5, y2-5+k, Green);
		}

			x1=x1-5;
			y1=y1-5;
			x2=x2-5;
			y2=y2-5;

			disable_timer(1);
			reset_timer(1);

		if(x1 == 5 && y1 != 43) {
			angolo = 45;
			setSound();
		}
		if(y1 == 43) {
			
			if(x1 >= x1p2 && x2 <= x2p2) {
				
				if((x2-x1p2) < 15 || (x2p2-x1) < 15) angolo = 210;
				else angolo = 225;
			
			setSound();
			}
		}

	}
	
	else if(angolo == 45) {
		
		for(k=0;k<5;k++) {
			LCD_DrawLine( x1, y1+k, x2, y2+k, Black);
		}	 
		
		for(k=0;k<5;k++) {
			LCD_DrawLine( x1+5, y1-5+k, x2+5, y2-5+k, Green);
		}
							
			x1=x1+5;
			y1=y1-5;
			x2=x2+5;
			y2=y2-5;
		
			disable_timer(1);
			reset_timer(1);
	
		if(y1 == 43) {
			
			if(x1 >= x1p2 && x2 <= x2p2) {
				
				if((x2-x1p2) < 15 || (x2p2-x1) < 15) angolo = 330;
				else angolo = 315;
				
			setSound();
			}
		}		
		if(x2 == 234 && y1 != 43) {
			angolo = 135;
			setSound();
		}

	}
		
	else if(angolo == 315) {
		
		for(k=0;k<5;k++) {
				LCD_DrawLine( x1, y1+k, x2, y2+k, Black);
		}	
		
		for(k=0;k<5;k++) {
			LCD_DrawLine( x1+5, y1+5+k, x2+5, y2+5+k, Green);
		}
		
			x1=x1+5;
			y1=y1+5;
			x2=x2+5;
			y2=y2+5;
		
			disable_timer(1);
			reset_timer(1);
	
		if(x2 == 234) {
			angolo = 225;	
			setSound();
		}
		
		if(y1 == 268) {
			if(x1 >= x1p && x2 <= x2p) {
				
				if((x2-x1p) < 15 || (x2p-x1) < 15) angolo = 30;
				else angolo = 45;
				
				setSound();
			}
			else {}
		}
	}
	
	else if(angolo == 150) {
			
		for(k=0;k<5;k++) {
			LCD_DrawLine( x1, y1+k, x2, y2+k, Black);
			}	
			
		for(k=0;k<5;k++) {
			LCD_DrawLine( x1-5, y1-2+k, x2-5, y2-2+k, Green);
		}		
			x1=x1-5;
			y1=y1-2;
			x2=x2-5;
			y2=y2-2;

			disable_timer(1);
			reset_timer(1);
		
		if(x1 == 5 && y1 != 44) {
			angolo = 30;
			setSound();;
		}
		if(y1 == 44) {
			if(x1 >= x1p2 && x2 <= x2p2) {
				
				if((x2-x1p2) < 15 || (x2p2-x1) < 15) angolo = 225;
				else angolo = 210;
				
			setSound();
			}
		}
	}
	
	else if(angolo == 30) {
		
			
		for(k=0;k<5;k++) {
			LCD_DrawLine( x1, y1+k, x2, y2+k, Black);
		}	 	
		
		for(k=0;k<5;k++) {
			LCD_DrawLine( x1+5, y1-2+k, x2+5, y2-2+k, Green);
		}	
		
			x1=x1+5;
			y1=y1-2;
			x2=x2+5;
			y2=y2-2;
		
			disable_timer(1);
			reset_timer(1);
	
		if(y1 == 44) {
			if(x1 >= x1p2 && x2 <= x2p2) {
				
				if((x2-x1p2) < 15 || (x2p2-x1) < 15) angolo = 315;
				else angolo = 330;
				
			setSound();
			}
		}		
		if(x2 == 234 && y1 != 8) {
			angolo = 150;
			setSound();
		}
	}
	
	else if(angolo == 210) {
	
		for(k=0;k<5;k++) {
			LCD_DrawLine( x1, y1+k, x2, y2+k, Black);
		}	 
	
		for(k=0;k<5;k++) {
			LCD_DrawLine( x1-5, y1+2+k, x2-5, y2+2+k, Green);
		}
			x1=x1-5;
			y1=y1+2;
			x2=x2-5;
			y2=y2+2;
		
			disable_timer(1);
			reset_timer(1);
		
		if(y1 == 267)	{
		
			if(x1 >= x1p && x2 <= x2p) {
				
				if((x2-x1p) < 15 || (x2p-x1) < 15) angolo = 135;
				else angolo = 150;
				
				setSound();
			}
			else {}
		}
		
		if(x1 == 5) {
			angolo = 330;
			setSound();
		}
	}
	
	else if(angolo == 330) {
			
		for(k=0;k<5;k++) {
			LCD_DrawLine( x1, y1+k, x2, y2+k, Black);
		}	
		
		for(k=0;k<5;k++) {
			LCD_DrawLine( x1+5, y1+2+k, x2+5, y2+2+k, Green);
		}
			x1=x1+5;
			y1=y1+2;
			x2=x2+5;
			y2=y2+2;
		
			disable_timer(1);
			reset_timer(1);
	
		if(x2 == 234) {
			angolo = 210;	
			setSound();
		}
		
		if(y1 == 267) {
			if(x1 >= x1p && x2 <= x2p) {
				
				if((x2-x1p) < 15 || (x2p-x1) < 15) angolo = 45;
				else angolo = 30;
				
				setSound();	
			}
			else {}
		}
	}
	
	if(y1 == 298 || y1 == 297) {
		setScore();
		for(k=0;k<10;k++) {
			LCD_DrawLine(x1, y1+k, x2, y2+k, Black);
		}
		if(punteggio1 != 5 && punteggio2 != 5) {
		x1=230,y1=158,x2=234,y2=158;
		angolo = 225;
		}
		if(punteggio1 == 5 || punteggio2 == 5) {
			disable_timer(0);
			disable_RIT();
		}
	}
	
	if(y1 == 18 || y1 == 17) {
		setScore();
		for(k=0;k<10;k++) {
			LCD_DrawLine(x1, y1+k, x2, y2+k, Black);
		}
		if(punteggio1 != 5 && punteggio2 != 5) {
		x1=230,y1=158,x2=234,y2=158;
		angolo = 225;
		}
		if(punteggio1 == 5 || punteggio2 == 5) {
			disable_timer(0);
			disable_RIT();
		}
	}
	
	if(direction == 0) {
		for(k=0;k<speedpl2;k++) {
			LCD_DrawLine( x2p2+1+k, 32, x2p2+1+k, 41, Green);
		}

		for(k=0;k<speedpl2;k++) {
			LCD_DrawLine( x1p2+k, 32, x1p2+k, 41, Black);
		}

		x1p2 = x1p2 + k;
		x2p2 = x2p2 + k;
		
		if(x2p2 == 234) direction = 1;
	}

	else if(direction == 1) {
		
		for(k=0;k<speedpl2;k++) {
			LCD_DrawLine( x1p2-k-1, 32, x1p2-k-1, 41, Green);
		}

		for(k=0;k<speedpl2;k++) {
			LCD_DrawLine( x2p2-k, 32, x2p2-k, 41, Black);
		}

		x1p2 = x1p2 - k;
		x2p2 = x2p2 - k;
		
		if(x1p2 == 5) direction = 0;
	}
	
	if(x1 == 215) {
		sprintf(str,"%d",punteggio2);
		GUI_TextInverse(231, 174, (uint8_t *) str, White, Black);
	}
	
	if(x1 == 25) {
		sprintf(str,"%d",punteggio1);
		GUI_Text(7, 160, (uint8_t *) str, White, Black);
	}
	
	if(punteggio1 == 5) {
		GUI_TextInverse(155, 20, (uint8_t *) " You Lose ", White, Black);
		GUI_Text(80, 300, (uint8_t *) " You Win ", White, Black);
	}
	
	if(punteggio2 == 5) {
		GUI_TextInverse(155, 20, (uint8_t *) " You Win ", White, Black);
		GUI_Text(80, 300, (uint8_t *) " You Lose ", White, Black);
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

void TIMER2_IRQHandler (void)
{
}

/******************************************************************************
**                            End Of File
******************************************************************************/
