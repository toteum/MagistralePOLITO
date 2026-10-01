#include "button.h"
#include "LPC17xx.h"


#include "../led/led.h"
#include "../timer/timer.h"


	/* Variabili Globali Gestione De-Bouncing */
	
extern int down_0;
extern int down_1;
extern int down_2;


void EINT0_IRQHandler (void)	  	// INT0
{		
	enable_RIT();
	NVIC_DisableIRQ(EINT0_IRQn);											/* disable Button interrupts	*/
	LPC_PINCON->PINSEL4    &= ~(1 << 20);     				/* GPIO pin selection 			*/
	
	LPC_SC->EXTINT &= (1 << 0);     									/* clear pending interrupt      */
}


void EINT1_IRQHandler (void)	  	// KEY1	
{
	enable_RIT();
	NVIC_DisableIRQ(EINT1_IRQn);											/* disable Button interrupts	*/
	LPC_PINCON->PINSEL4    &= ~(1 << 22);     				/* GPIO pin selection 			*/
	
	LPC_SC->EXTINT &= (1 << 1);     									/* clear pending interrupt      */
}

void EINT2_IRQHandler (void)	  	// KEY2
{
	enable_RIT();
	NVIC_DisableIRQ(EINT2_IRQn);										/* disable Button interrupts	*/	
	LPC_PINCON->PINSEL4    &= ~(1 << 24);    	 			/* GPIO pin selection 			*/
	
	LPC_SC->EXTINT &= (1 << 2);     								/* clear pending interrupt      */    
}


void disable_INT0(){
	NVIC_DisableIRQ(EINT0_IRQn);											/* disable Button interrupts	*/
	LPC_PINCON->PINSEL4    &= ~(1 << 20);     				/* GPIO pin selection 			*/
}

void disable_KEY1(){
	NVIC_DisableIRQ(EINT1_IRQn);											/* disable Button interrupts	*/
	LPC_PINCON->PINSEL4    &= ~(1 << 22);     				/* GPIO pin selection 			*/
}

void disable_KEY2(){
	NVIC_DisableIRQ(EINT2_IRQn);										/* disable Button interrupts	*/	
	LPC_PINCON->PINSEL4    &= ~(1 << 24);    	 			/* GPIO pin selection 			*/
}

void enable_INT0(){
	NVIC_EnableIRQ(EINT0_IRQn);							 			 /* disable Button interrupts			*/
	LPC_PINCON->PINSEL4    |= (1 << 20);     			 /* External interrupt 0 pin selection   */
}

void enable_KEY1(){
	NVIC_EnableIRQ(EINT1_IRQn);							 			 /* disable Button interrupts			*/
	LPC_PINCON->PINSEL4    |= (1 << 22);     			 /* External interrupt 0 pin selection   */
}

void enable_KEY2(){
	NVIC_EnableIRQ(EINT2_IRQn);							 			 /* disable Button interrupts			*/
	LPC_PINCON->PINSEL4    |= (1 << 24);     			 /* External interrupt 0 pin selection  */
}