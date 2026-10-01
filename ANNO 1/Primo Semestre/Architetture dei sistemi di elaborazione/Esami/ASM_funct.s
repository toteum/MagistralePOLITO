				AREA asm_functions, CODE, READONLY				
                EXPORT  is_prime_number_or_previous_one
					
is_prime_number_or_previous_one
				; save current SP for a faster access 
				; to parameters in the stack
				MOV   r12, sp
				; save volatile registers
				STMFD sp!,{r4-r8,r10-r11,lr}				
							
							
				; r0 = numero
				MOV r1, r0 ; r1 = dividendo
				MOV r2, #2 ; r2 = divisore
			
loop_1
				SUB r1, r1, r2 	; r1 dividendo, r2 divisore
				CMP r1, #0		; comparo il dividendo con 0
				MOVEQ r5, #0	; se è uguale a 0, il numero non è primo
				BEQ is_not_primo		; e quindi restituisco 0
				
				BGT loop_1			; se è maggiore di zero, continuo la divisione
				
				
				MOV r1, r0		; resetto il dividendo
				ADD r2, r2, #1	; incremento il divisore
				CMP r2, r0		; vedo se il divisore è minore del dividendo. Se si, continuo
				BLT loop_1
				
				
				MOV r5, #1		; se il divisore è maggiore o uguale al dividendo, e il risultato non è mai stato 0, il numero è primo
				
is_primo
				MOV r0, #255	; ritorno 0xFF
				B fine
				
is_not_primo
				SUB r0, r0, #1		;r0 = r0 - 1 (numero = numero--)
				MOV r1, r0 			; r1 = dividendo
				MOV r2, #2 			; r2 = divisore

loop_2			
						
				SUB r1, r1, r2 	; r1 dividendo, r2 divisore
				CMP r1, #0		; comparo il dividendo con 0
				MOVEQ r5, #0	; se è uguale a 0, il numero non è primo
				BEQ is_not_primo		; e quindi riprovo con NUMERO--
				
				BGT loop_2			; se è maggiore di zero, continuo la divisione
				
				
				MOV r1, r0		; resetto il dividendo
				ADD r2, r2, #1	; incremento il divisore
				CMP r2, r0		; vedo se il divisore è minore del dividendo. Se si, continuo
				BLT loop_2
				
				
				;MOV r0, r0		; se il divisore è maggiore o uguale al dividendo, e il risultato non è mai stato 0, il numero è primo
				

fine				
				; restore volatile registers
				LDMFD sp!,{r4-r8,r10-r11,pc}
				
                END