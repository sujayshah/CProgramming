;number to print in base 7 is in R3.
;it will be positive.
.ORIG x3000

AND R4, R4, #0
ADD R4, R4, #7 ; set divisor to 7

LD R2, ASCII_0 ; load x0030 into r2

DIVIDE
	JSR DIV
	AND R3, R3, #0 ; clear current value in r3
	ADD R3, R3, R0 ; store quotient in r3
	AND R0, R0, #0
	ADD R0, R0, R1 ; copy remainder into r0	
	JSR PUSH
	ADD R3, R3, #0 ; check if quotient is zero
	BRz GOTOPOP    ; quotient is zero so begin popping from stack	
	BR DIVIDE      ; quotient is not zero so perform division again

GOTOPOP
	JSR POP
	ADD R5, R5, #0 ; check error code
	BRp DONE       ; stack is empty, so we are finished 
	ADD R0, R0, R2 ; convert popped value to ASCII
	OUT	       ; print to screen
	BR GOTOPOP	

DONE
	HALT

ASCII_0 .FILL x30

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4 (R3/R4)
;out R0-quotient, R1-remainder
DIV
	ST R2,DIV_R2
	ST R3,DIV_R3
	NOT R2,R4
	ADD R2,R2,#1
	AND R0,R0,#0
	ADD R0,R0,#-1
DIV_LOOP	
	ADD R0,R0,#1
	ADD R3,R3,R2
	BRzp DIV_LOOP
	ADD R1,R3,R4
	LD R2,DIV_R2
	LD R3,DIV_R3
	RET

DIV_R2 .BLKW #1
DIV_R3 .BLKW #1


;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;

.END
