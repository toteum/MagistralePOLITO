	;PRESERVE8
    ;THUMB
					
	;AREA input_data, READONLY, ALIGN=4
    ;LTORG       ; Inserisce il literal pool qui
	;ALIGN 2
;DATA_IN  	DCB  0x0A,	0x01, 0x13, 0x02, 0x04, 0x06, 0x0F, 0x0A ; Dati definiti nel literal pool
	;ALIGN 2
;N 		 	DCD 8
	;ALIGN 2
	
	;EXPORT DATA_IN
	;EXPORT N
	;EXPORT BEST_3	
	;NOTA BENE, LA AREA READONLY NON � ASSOLUTAMENTE MODIFICALE E RISCRIVIBILE
	
	
	
	AREA asm_functions, CODE, READONLY	
	
	EXPORT  check_fibonacci
check_fibonacci FUNCTION
	
	;RO = address of VETT
	;R1 = dimVett
	;R2 = dimFibonacci
	;R3 =  VAL
	;R4 = BOUNDARY (in stack)
		
	; save current SP for a faster access 
	; to parameters in the stack
	MOV   r12, sp
	; save volatile registers
	STMFD sp!,{r4-r8,r10-r11,lr}				
	
	;STMFD sp!,{R0-R3}
	;MOV R1,R0 ; ho bisogno di VETT address in R1
	;MOV R0,R2 ; bsort ha bisogno di N in R0
	;BL bsort
	;LDMFD sp!,{R0-R3}
	;; extract argument 4 into R4
	LDR   r4, [r12] 
	
	;calcolo vettore di fibonacci
	LDR R5,=fibVett
	MOV R6,#0
	TEQ R3,R6
	MOVEQ R0,#0
	BEQ exitFunc
	STR R6,[R5]
	MOV R6,#1
	TEQ R3,R6
	MOVEQ R0,#0
	BEQ exitFunc
	STR R6,[R5,#4]
	MOV R7,R2 ;dimVettFib
	SUB R7,R7,#2
	MOV R12,#0
loopFib
	LDR R6,[R5]
	LDR R8,[R5,#4]!
	ADD R9,R6,R8
	
	TEQ R3,R9
	MOVEQ R0,#0
	BEQ exitFunc
	
	ADD R10,R9,R4
	SUB R11,R9,R4
	;num se compreso tra R11<=R3<=R10 non va bene
	CMP R3,R11
	ADDGE R12,R12,#1
	CMP R3,R10
	ADDLE R12,R12,#1
	
	MOV R10,#2
	TEQ R12,R10
	MOVEQ R0,#0
	BEQ exitFunc
	
	MOV R12,#0
	
continueLoopFib
	STR R9,[R5,#4]
	SUBS R7,R7,#1
	BNE loopFib
	; setup a value for R0 to return
	
	ADD R0,R0,R1
	STR R3,[R0]
	MOV   r0, #1
	
	; restore volatile registers
exitFunc
	LDMFD sp!,{r4-r8,r10-r11,pc}	
	
	ENDFUNC			
		
	AREA output_data, READWRITE, ALIGN=4
fibVett SPACE 4096 ;spazio sovradimensionato	
	END	

	