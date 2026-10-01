#include "utils.h"

volatile unsigned int VAR;
volatile unsigned int VETT[N];
volatile unsigned int index = 0;
extern unsigned int avg_vett(volatile unsigned int VETT[], volatile unsigned int dim, volatile char* flag);
volatile unsigned int res;
volatile char flag;

void initialize_array(){
	unsigned int i;
	for(i=0;i<N;i++) VETT[i]=0;
	index = 0;
}

void handle_TIMER1MR0(){
	VAR = get_timer_value(TIMER2);
}

void handle_INT0(){
	
	if(index>0){
		if(VETT[index-1]==VAR) return;
	}
	
	VETT[index++]=VAR;
	
	if(index>=N){
		res = avg_vett(VETT,index,&flag);
		show_res();
		initialize_array();
	}
}

void show_res(){
	if(flag==0){
		disable_timer(TIMER0);
		LED_Out(~extract_bits(res,7,0));
	}else if(flag==1){
		blink_led6();
	}
}

void blink_led6(){
	init_timer(TIMER0,0,0,CONTROL_INTERRUPT|CONTROL_RESET,0x10B0760); //700ms
	LED_OffAll();
	reset_timer(TIMER0);
	enable_timer(TIMER0);
}

void handle_TIMER0MR0(){
	static unsigned int flagBlink = 0;
	if( flagBlink%2 == 0){
			LED_On(6);
			flagBlink = 1;
		} else {
			LED_Off(6);
			flagBlink = 0;
	} 
}