/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "LPC17xx.h"
#include "RIT.h"
#include "../led/led.h"
#include "../sample.h"

/* User Imports */

//#include "../main/user_RIT.h"

	/* Variabili Globali Gestione De-Bouncing */
	
volatile int down_0 = 0;
volatile int down_1 = 0;
volatile int down_2 = 0;
volatile int toRelease_down_0 = 0;
volatile int toRelease_down_1 = 0;
volatile int toRelease_down_2 = 0;
int const long_press_count_1 = 0;		// => count = x / 50ms ; where x = time long press
//int const long_press_count_2 = 0;


/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void RIT_IRQHandler(void) 
{			
	
	/* INT0 */
	
	if((LPC_PINCON->PINSEL4 & (1 << 20)) == 0){
		down_0++;
		if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){ /* button premuto */
			reset_RIT();
			switch(down_0) {
				case 1:				
					// short press
				  // your_code	
					toRelease_down_0 = 1;
					handle_INT0();
					break;
				case long_press_count_1:					
					// your code here (for long press)				
					break;
				default:
					break;
			}
		}
		else {	/* button released */
			if(toRelease_down_0){
				//add code to manage release.
				toRelease_down_0=0;
			}
			down_0=0;		
			disable_RIT();
			reset_RIT();			
			NVIC_EnableIRQ(EINT0_IRQn);							 			 /* disable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 20);     			 /* External interrupt 0 pin selection   */
		}
	} 	// end INT0

	///////////////////////////////////////////////////////////////////
	
	/* KEY1 */
	
	if((LPC_PINCON->PINSEL4 & (1 << 22)) == 0){			/* KEY1 */
		down_1++;
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){ /* button premuto */
			reset_RIT();
			switch(down_1){
				case 1:
					// short press
					// your code here
					toRelease_down_1=1;
					break;
				case long_press_count_1:
					// your code here (for long press)
					break;
				default:
					break;
			}
		}
		else {	/* button released */
			if(toRelease_down_1){
				//add code to manage release.
				toRelease_down_1=0;
			}			
			down_1=0;	
			disable_RIT();
			reset_RIT();
			NVIC_EnableIRQ(EINT1_IRQn);							 			 /* disable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 22);     			 /* External interrupt 0 pin selection   */
		}
	}	// end KEY1
	
	///////////////////////////////////////////////////////////////////
	
	/* KEY2 */

	if((LPC_PINCON->PINSEL4 & (1 << 24)) == 0){			/* KEY1 */
		down_2++;
		if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){ /* button premuto */
			reset_RIT();
			switch(down_2){
				case 1:
					// short press
					// your code here
					toRelease_down_2=1;
					break;
				case long_press_count_1:
					// your code here (for long press)
					break;
				default:
					break;
			}
		}
		else {	/* button released */
			if(toRelease_down_2){
				//add code to manage release.
				toRelease_down_2=0;
			}	
			down_2=0;	
			disable_RIT();
			reset_RIT();			
			NVIC_EnableIRQ(EINT2_IRQn);							 			 /* disable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 24);     			 /* External interrupt 0 pin selection  */
		}
	}	// end KEY2
		
	
		//reset_RIT(); se ci sono cose strane come il rit che si ferma
		LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
		return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/