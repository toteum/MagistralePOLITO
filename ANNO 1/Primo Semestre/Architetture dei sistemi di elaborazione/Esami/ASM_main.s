				AREA asm_main, CODE, READONLY	
	
;definizione di costanti e register renaming
;MY_CONST EQU 36
;my_register RN 0
; Per leggere 8 bit  ldrb r1, [array, r4]  // Load byte from array + offset (r4) da incrementare di 1
; Per scrivere su 8 bit strb valore_da_scrivere, [array, offset]   
; Per leggere 16 bit  ldrh r1, [array, r0, lsl #1]   // Load byte from array + offset (r4) da incrementare di 1
; Per scrivere su 16 bit strb valore_da_scrivere, [array, contatore, #lsl #1] 
; Per leggere 32 bit  ldr r1, [array, r0, lsl #2]   // Load byte from array + offset (r4) da incrementare di 1
; Per scrivere su 32 bit STR valore_da_scrivere, [array, contatore, lsl #2]


; ======================= FUNCTION REFERENCE GUIDE ===========================
; bsort                  | r0=array size | r1=ptr to array 	-> sorts in-place
; isPrime                | r0=input int  |					-> r0=1 if prime, 0 otherwise
; calc_mod               | r1=dividend   | r2=divisor 		-> r0=dividend % divisor
; count_bit1             | r0=input int  |					-> r0=number of 1-bits in input
; get_max                | r0=ptr  array | r1=size	 		-> r0=max element
; get_min                | r0=ptr  array | r1=size	 		-> r0=min element
; is_monotonic_increasing| r0=ptr  array | r1=size	 		-> r0=1 if increasing, else 0
; fibonacci              | r0=ptr  array | r1=size	 		-> r0=pointer to filled array
; abs_value              | r0=signed int |					-> r0=absolute value of input
; value_is_in_a_range    | r0=value 	 | r1=min | r2=max 	-> r0=1 if in range, else 0
; array_sum              | r0=ptr  array | r1=length	 	-> r0=sum of elements
; my_division            | r0=float  ptr | r1=float ptr b 	-> r0=a / b (float)
; DIVISION               | r0=dividend   | r1=divisor 		-> r0=quotient (int, via subtraction)
; array_avg				 | r0=ptr  array | r1=size			-> r0=float avg
; fib_runtime			 |                                  -> compute fib for checking your array without saving anything
; array_avg_int			 | r0=ptr array  | r1=size			-> compute the division quotient 
; ============================================================================
is_prime_number_or_previous_one PROC
				EXPORT is_prime_number_or_previous_one
				import isPrime
					
				MOV 	r12, SP  ;abilitarlo per ottenere i parametri contenuti sullo stack
				PUSH 	{r4-r8, r10-r11, lr}
				
				;ottengo 5°/6° parametro(r4, r5) dallo stack
				;LDR 	r4, [r12]   	; parameter 4
				;LDR 	r5, [r12, #4]	; parameter 5
				
				;---------------------------------------------------
				; ASSEMBLY PROGRAM START
				;---------------------------------------------------
				
				mov r5, r0 ;OG NUMERO cpy
loop				
				push {r0}
				mov r0, r5
				bl isPrime
				mov r4, r0
				pop {r0}
				;r4 contains the result
				
				cmp r5, r0;check first loop
				beq check_first_loop
				
				cmp r4, #0
				movgt r0, r5
				bgt exit
				
				b decrease_numero
				
check_first_loop
				cmp r4, #0
				movgt r0, 0xff
				bgt exit
				
decrease_numero				
				subeq r5, #1
				beq loop
exit
				
				POP 	{r4-r8,r10-r11,pc} ;restore di tutti i registri utilizzati nel mio codice
				ENDP
	END