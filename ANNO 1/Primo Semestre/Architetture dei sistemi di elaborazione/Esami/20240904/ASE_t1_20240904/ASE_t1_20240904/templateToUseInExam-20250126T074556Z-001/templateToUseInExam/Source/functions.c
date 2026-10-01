// Funzione per estrarre i bit tra gli indici start ed end
unsigned char extract_bits(unsigned int value, int start, int end) {
    if (start < end || start >= 32 || end < 0) {
        return 0;
    }

    // Calcolo del numero di bit da estrarre
    int num_bits = start - end + 1;

    // Creazione di una maschera per isolare i bit desiderati
    unsigned int mask = ((1U << num_bits) - 1) << end;

    // Isolamento e shift dei bit estratti
    unsigned char result = (value & mask) >> end;

    return result;
}

/* Rappresentare sui led il valore res di 32 bit, 8 bit alla volta, partendo da LSB */
void represent_on_leds(unsigned int res, int position) {
    if (position < 0 || position > 3) {
        // Invalid position; do nothing
        return;
    }

    // Extract 8 bits from the 32-bit value
    unsigned char aus = (res >> (8 * position)) & 0xFF;

    // Output the extracted value to the LEDs
    LED_Out(aus);
}

/*
chiamare vettori e cose definite in assembly
extern char DATA_IN; //primo valore del vettore DATA_IN
extern int N; //dim
extern char BEST_3; //primo valore del vettore BEST_3

extern int find_best_3(char DATA_IN[], int N, char BEST_3[]);

void handle_KEY1(){
	int res;
	res = find_best_3(&DATA_IN,N,&BEST_3); //indirizzo prima cella di data_in, passo N cosi come è, passo indirizzo prima cella di BEST_3
																					////ho bisogno dell'indirizzo di memoria della prima cella che prelevo con &, ricordiamoci la dualità puntatore-vettore!!!!
	init_timer(TIMER2,0,0,3,0x1312D00); //0.8 s
	enable_timer(TIMER2);
}

void handle_timer2MR0(){
	static unsigned char tickCount=0;
	LED_Out(*(&(BEST_3)+tickCount++));
	if(tickCount==3) tickCount=0;
}
*/

/*
static unsigned int flagBlink = 0;
	if( flagBlink%2 == 0){
				//qua è zero,
			LED_Out_Range(15,D11,D8);
			flagBlink = 1;
		} else {
			LED_Out_Range(0,D11,D8);
			flagBlink = 0;
	} 
*/

/*
void		handle_timer0_MR0(){
	LED_Off(D4);
}

void 		handle_timer0_MR1(){
	LED_On(D4);
}



void blink_type1(){
	init_timer(0,0,0,1,0x1EFE920); //1.3s
	init_timer(0,0,1,3,0x3473BC0); //1.3s+0.9s = 2.2s per MR1
	enable_timer(0);
}
*/
//se dice ON per X secondi, devi mettere X secondi dentro il MR0


/*
void set_led_brightness(uint32_t led, uint32_t mr0, uint32_t mr1)
{
	led_brightness[led].match0 = mr0;
	led_brightness[led].match1 = mr1;

	TIMER_set_callable(TIMER1, MATCH0, led_match0_callable);
	TIMER_set_callable(TIMER1, MATCH1, led_match1_callable);

	TIMER_match_reg(TIMER1, MATCH0, CONTROL_INTERRUPT, led_brightness[led].match0, false);
	TIMER_match_reg(TIMER1, MATCH1, CONTROL_INTERRUPT | CONTROL_RESET, led_brightness[led].match1, false);

	TIMER_enable(TIMER1);
}

void set_led_brightness_micro(uint32_t led, uint32_t micro_mr0, uint32_t micro_mr1)
{
	bright_selected_led = led;
	led_brightness[led].match0 = TIMER_CLK / 1000000 * micro_mr0;
	led_brightness[led].match1 = TIMER_CLK / 1000000 * micro_mr1;

	TIMER_set_callable(TIMER1, MATCH0, led_match0_callable);
	TIMER_set_callable(TIMER1, MATCH1, led_match1_callable);

	TIMER_match_reg(TIMER1, MATCH0, CONTROL_INTERRUPT, led_brightness[led].match0, false);
	TIMER_match_reg(TIMER1, MATCH1, CONTROL_INTERRUPT | CONTROL_RESET, led_brightness[led].match1, false);

	TIMER_enable(TIMER1);
}

led_bright_t *get_led_brighness(uint32_t led)
{
	return (led_bright_t *)&led_brightness[led];
}

*/

/*
to generate random number 

#include "button.h"
#include "lpc17xx.h"
#include "../led/led.h"

extern unsigned char next_state(unsigned char currentState, unsigned char taps, int *output_bit); //parameters are currentState, position of taps, addres of outputBits that passed by rerefence
//void EINT0_IRQHandler (void)	  
//{
//	LED_On(0);
//  LPC_SC->EXTINT &= (1 << 0);     // clear pending interrupt         
//}//


void EINT1_IRQHandler (void)	  
{
	extern unsigned char currentState;
	extern unsigned char taps;
	int output_bit;
	volatile unsigned char nextState;

  nextState = next_state(currentState, taps, &output_bit); 
	currentState = nextState;
	
	LED_Out(currentState);
	LPC_SC->EXTINT &= (1 << 1);     // clear pending interrupt         
}

void EINT2_IRQHandler (void)	  
{
	extern unsigned char currentState;
	extern unsigned char taps;
	int output_bit;
	volatile unsigned char nextState;
	unsigned int count = 0;
	extern unsigned char startState;
  
	do {
		nextState = next_state(currentState, taps, &output_bit); 
		currentState = nextState;
		count++;
	} while(currentState!=startState);
	LED_Out(count);

  LPC_SC->EXTINT &= (1 << 2);     // clear pending interrupt           
}



*/