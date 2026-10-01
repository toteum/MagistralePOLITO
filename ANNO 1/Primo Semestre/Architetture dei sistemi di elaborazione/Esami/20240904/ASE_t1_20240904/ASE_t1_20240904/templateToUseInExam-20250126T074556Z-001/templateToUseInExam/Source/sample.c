/*----------------------------------------------------------------------------
 * Name:    sample.c
 * Purpose: to control led through debounced buttons and Joystick
 *        	- key1 switches on the led at the left of the current led on, 
 *					- it implements a circular led effect,
 * 					- joystick UP function returns to initial configuration (led11 on) .
 * Note(s): this version supports the LANDTIGER Emulator
 * Author: 	Paolo BERNARDI - PoliTO - last modified 15/12/2020
 *----------------------------------------------------------------------------
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2017 Politecnico di Torino. All rights reserved.
 *----------------------------------------------------------------------------*/
                  
#include <stdio.h>
#include "LPC17xx.h"                    /* LPC17xx definitions                */
#include "led/led.h"
#include "button_EXINT/button.h"
#include "timer/timer.h"
#include "RIT/RIT.h"
#include "joystick/joystick.h"
#include "sample.h"
#include "utils.h"
#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

/*
unsigned char startState = 0xAA;
unsigned char currentState = 0xAA; //0b101010
unsigned char taps = 0x41; //01000001
*/

/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void) {
  	
	SystemInit();  													/* System Initialization (i.e., PLL)  */
	initialize_array();
	// LED
  LED_init();                           /* LED Initialization                 */
	
	// Buttons
  BUTTON_init();												/* BUTTON Initialization              */
	
	// RIT
	init_RIT(0x004C4B40); ///* RIT Initialization 50 msec       */
	
	power_on_timer2(); 	// or LPC_SC -> PCONP |= (1 << 22);  // TURN ON TIMER 2
	//power_on_timer3(); 	// or LPC_SC -> PCONP |= (1 << 23);  // TURN ON TIMER 3	


  //init_timer(2, 0, 2, 1, 0x017D7840);							/* TIMER0 Initialization              */
																										/* K = T*Fr = [s]*[Hz] = [s]*[1/s]	  */
																										/* T = K / Fr = 0x017D7840 / 25MHz    */
																										/* T = K / Fr = 25000000 / 25MHz      */
																										/* T = 1s	(one second)   							*/							
	//enable_timer(2);
	
	//init_timer(1,0,0,3, 0x2FAF080); //2s
	//enable_timer(1);
	
	//init_timer(1, 0, 0, 1, 0x3D090); //MR0
	//init_timer(1, 0, 1, 3, 0xF4240); //MR1
	//enable_timer(1);
	
	init_timer(TIMER1,0,0,CONTROL_RESET|CONTROL_INTERRUPT,0x2887FA0); //1.7 sec
	enable_timer(TIMER1);
	
	init_timer(TIMER2,0,0,CONTROL_RESET,0x2B82EA80); //14.6 sec with 50MHz of clock
	enable_timer(TIMER2);
	
	//to edit frequency of peripherals you should go on lpc17xxx.c and use the configuration wizard
	

	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= 0xFFFFFFFFD;						
		
  while (1) {                           /* Loop forever                       */	
		__ASM("wfi");
  }

}