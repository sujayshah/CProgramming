.ORIG x3000

LD R1, NUM
AND R3, R3, #0  ; use as a counter

INPUT
	GETC	
	OUT
	LD R2, SPACE
	NOT R2, R2
	ADD R2, R2, #1 ; negate space ascii to make sure this is not part of the input
	ADD R2, R0, R2 	
	BRz INVALID
	LD R2, ASCII_0
	NOT R2, R2
	ADD R2, R2, #1
	ADD R0, R0, R2 ; subtract x0030 from input ascii value to convert into integer 
	STR R1, R0, #0 ; store input character into starting address of number string
	ADD R1, R1, #1 ; increment address
	ADD R3, R3, #1 ; increment digit counter
	AND R5, R5, #0
	NOT R5, R3
	ADD R5, R5, #1 ; store negative of digit count in r5	
	AND R4, R4, #0
	ADD R4, R4, #10 ; initialise max digits to 10
	ADD R4, R4, R5
	BRp INPUT       ; get another digit
	AND R3, R3, #0
	LD R1, NUM

VALIDATE
	STR R6, R1, #0 	; store value at starting address into r6
	ADD R1, R1, #1  ; increment address
	JSR GRZERO
	ADD R3, R3, #1  ; increment counter
	AND R5, R5, #0
	NOT R5, R3
	ADD R5, R5, #1  
	AND R4, R4, #0
	ADD R4, R4, #10 
	ADD R4, R4, R5
	BRp VALIDATE
	JSR VALID

GRZERO
	ADD R6, R6, #0
	BRn INVALID     ; number is negative so invalid	

LENINE
	ADD R6, R6, #-9
	BRp INVALID 	; number is greater than 9 so invalid
	RET		; number is within range so check the next one		
	
INVALID
	LEA R0, INV_MSG
	PUTS
	JSR DONE

VALID
	LEA R0, VAL_MSG
	PUTS
	JSR DONE	

DONE
	HALT	

KBSR    .FILL xFE00
KBDR    .FILL xFE02
DSR     .FILL xFE04
DDR     .FILL xFE06
NUM 	.FILL x5000
ASCII_0 .FILL x0030 
SPACE   .FILL x0020
INV_MSG .STRINGZ "Invalid Phone Number."
VAL_MSG .STRINGZ "Valid Phone Number."

.END
