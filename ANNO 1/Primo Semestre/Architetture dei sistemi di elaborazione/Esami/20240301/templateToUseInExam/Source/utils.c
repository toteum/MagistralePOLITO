#include "utils.h"

volatile unsigned char VETT[N];
volatile unsigned int index = 0;
volatile unsigned char countPressureKEY1 = 0;
volatile unsigned char VAL;
volatile unsigned int discardedCount = 0;
extern unsigned char check_fibonacci(volatile unsigned char* VETT, volatile unsigned char dimVett, unsigned char dimmFib, volatile unsigned char VAL, unsigned char boundary);

void clear_array(){
	unsigned int i;
	for(i=0;i<N;i++) VETT[i]=0;
}

void handle_KEY1(){
	if(countPressureKEY1==0){
		enable_timer(TIMER2);
		countPressureKEY1++;
	}else if(countPressureKEY1>=1){
		VAL = extract_bits(get_timer_value(TIMER2),10,3);
		unsigned char status = check_validity();
		if(status==0){
			discardedCount++;
			LED_OnAll();
		}
	}
}

unsigned char check_validity(){
	unsigned char status;
	status = check_evenOrOdd_inArray();
	if(status==0) return status;
	status = check_fib();
	return status;
}			

unsigned char check_evenOrOdd_inArray(){
	if(index==0){
		if(VAL%2==0){
			return 1;
		}
		return 0;
	}
	if(index>0){
		if( (VETT[index-1]%2==0 && VAL%2!=0) || (VETT[index-1]%2!=0 && VAL%2==0 )) return 1;
		return 0;
	}
	return 0;
}

void clear_all(){
	unsigned int i;
	for(i=0;i<N;i++) VETT[i]=0;
	index = 0;
	VAL = 0;
	countPressureKEY1 = 0;
	discardedCount = 0;
}

void handle_timer0MR0(){
	static unsigned char tickCount = 0;
	
	if(tickCount%2==0){
		LED_OnAll();
	}else{
		LED_OffAll();
	}
	
	tickCount++;
	if(tickCount>=8){
		//sono passati all incirca 2 secondi, poco piu
		tickCount=0;
		disable_timer(TIMER0);
		enable_RIT();
		if(index>=N) clear_all();
	}
}

void handle_timer1MR0(){
	static unsigned char tickCount = 0;
	
	if(tickCount%2==0){
		LED_Out(discardedCount);
	}else{
		LED_OffAll();
	}
	
	tickCount++;
	if(tickCount>=8){
		//sono passati all incirca 2 secondi, poco piu
		tickCount=0;
		disable_timer(TIMER1);
		enable_RIT();
		if(index>=N) clear_all();
	}
}

void show_res(){
	disable_RIT();
	init_timer(TIMER0,0,0,CONTROL_INTERRUPT|CONTROL_RESET,0x5D75C8); //245ms
	reset_timer(TIMER0);
	enable_timer(TIMER0);
}

unsigned char check_fib(){
	unsigned char status = check_fibonacci(VETT,index,M,VAL,BOUNDARY);
	if(index<N){
		if(status){
			index++;
			show_res();
		}
	}else if(index>=N){
		init_timer(TIMER1,0,0,CONTROL_RESET,0x7F2815); //0.33333 sec
		disable_RIT();
		reset_timer(TIMER1);
		enable_timer(TIMER1);
	}
	return status;
}