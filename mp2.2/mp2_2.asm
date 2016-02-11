;Assuming user will only enter ' ' 0-9 *+/-
;----------------------
;INTRODUCTORY PARAGRAPH
;----------------------
;The following code is used to implement some basic calculator operations using the stack in LC-3 Assembly. The available functions are addition, subtraction, multiplication, division and power. The user must provide an input
;expression in postfix notation. When an operand is identified, it is pushed onto the stack. When an operator is identified, two values are popped from the stack. If the input expression causes an error, either because there was an
;invalid input character or because two values could not be popped from the stack following detection of an operator, an error message is printed and the programme halts. Otherwise, it continues by accessing the relevant subroutine
;to perform the computation for each operator on its operands. The result of each operation is pushed back onto the stack until there are no longer any operations to perform. The final result is then popped and stored in R6 and printed 
;to the console in hexadecimal format.

.ORIG x3000
	
AND R0, R0, #0                  ;clear r0
AND R1, R1, #0                  ;initialise r1
AND R6, R6, #0                  ;initialise r6
AND R7, R7, #0

GETCHAR 
        GETC	                ;store input character into r0 	
        OUT                     ;echo the user input

LINECHECK  
        LD R1, NEW_LINE         
        NOT R1, R1
        ADD R1, R1, #1          
        ADD R1, R0, R1          
        BRz GOTOPOP             ;if a new line is entered, access the pop subroutine to validate expression

SPACECHECK        
        LD R1, SPACE                       
        NOT R1, R1
        ADD R1, R1, #1          
        ADD R1, R0, R1          
        BRz GETCHAR             ;if the input is a space, loop back to get another character

CHARCHECK
        LD R1, PLUS             ;check for addition operator
        NOT R1, R1
        ADD R1, R1, #1
        ADD R1, R0, R1
        BRz POPOPERANDS1                 
        LD R1, MINUS            ;check for subtraction operator
        NOT R1, R1
        ADD R1, R1, #1
        ADD R1, R0, R1
        BRz POPOPERANDS2        
        LD R1, SLASH            ;check for division operator
        NOT R1, R1
        ADD R1, R1, #1
        ADD R1, R0, R1
        BRz POPOPERANDS3
        LD R1, ASTERISK         ;check for multiplication operator
        NOT R1, R1
        ADD R1, R1, #1
        ADD R1, R0, R1
        BRz POPOPERANDS4
        LD R1, HAT              ;check for power operator
        NOT R1, R1
        ADD R1, R1, #1
	ADD R1, R0, R1
	BRz POPOPERANDS5

GRZERO
        LD R1, ZERO
        NOT R1, R1
        ADD R1, R1, #1
        ADD R1, R0, R1        
        BRzp LENINE             ;check for an input digit greater than or equal to zero. If it is there, check if it is less than or equal to nine
        JSR INVALID             ;since input is neither an operator nor an operand, print error

LENINE
        LD R1, NINE
        NOT R1, R1
        ADD R1, R1, #1
        ADD R1, R0, R1
        BRnz GOTOPUSH           ;since the number is within the range 0-9, we can push it onto the stack
        JSR INVALID             ;out of range so print error

GOTOPUSH
        ADD R0, R0, #-15
	ADD R0, R0, #-15
	ADD R0, R0, #-15
	ADD R0, R0, #-3         ;subtract x0030 from inpit value to get it within range
        JSR PUSH           
        JSR GETCHAR             ;get the next character

SPACE .FILL x0020
NEW_LINE .FILL x000A
PLUS .FILL x002B 
MINUS .FILL x002D
SLASH .FILL x002F
ASTERISK .FILL x002A
HAT .FILL x005E
ZERO .FILL x0030
NINE .FILL x0039

PRINT_SaveR7 .BLKW #1

POPOPERANDS1                     
        AND R3, R3, #0
        AND R4, R4, #0          ;initialise r3 and r4 to 0 as these will be used to store the popped values
        JSR POP                
        ADD R3, R3, R0          ;copy the result of the first pop into r3
        JSR POP
        ADD R4, R4, R0          ;copy the result of the second pop into r4
        AND R1, R1, #0
        ADD R1, R5, R1
        BRp INVALID             ;pop failed
        JSR ADDITION            ;both pops succeeded so apply the operator

POPOPERANDS2                     
        AND R3, R3, #0
        AND R4, R4, #0          
        JSR POP                
        ADD R3, R3, R0          
        JSR POP
        ADD R4, R4, R0          
        AND R1, R1, #0
        ADD R1, R5, R1
        BRp INVALID            
        JSR SUBTRACTION

POPOPERANDS3                     
        AND R3, R3, #0
        AND R4, R4, #0          
        JSR POP                
        ADD R3, R3, R0          
        JSR POP
        ADD R4, R4, R0          
        AND R1, R1, #0
        ADD R1, R5, R1
        BRp INVALID            
        JSR DIVISION

POPOPERANDS4                     
        AND R3, R3, #0
        AND R4, R4, #0          
        JSR POP                
        ADD R3, R3, R0          
        JSR POP
        ADD R4, R4, R0          
        AND R1, R1, #0
        ADD R1, R5, R1
        BRp INVALID            
        JSR MULTIPLICATION

POPOPERANDS5                     
        AND R3, R3, #0
        AND R4, R4, #0          
        JSR POP                
        ADD R3, R3, R0          
        JSR POP
        ADD R4, R4, R0          
        AND R1, R1, #0
        ADD R1, R5, R1
        BRp INVALID            
        JSR POWER

GOTOPOP
        JSR POP
        AND R1, R1, #0          
        ADD R1, R5, R1
        BRp INVALID             ;pop failed, no elements left in stack so the expression is invalid
        JSR VALID

INVALID
        LEA R0, ERROR
        PUTS
        JSR DONE

ERROR .STRINGZ " Invalid Expression. "

VALID 
        ADD R6, R6, R0          ;store popped value into r6
        JSR PRINT_HEX           ;access subroutine to convert this value to hex and print
        JSR DONE

DONE
        HALT

PRINT_HEX
	AND R3, R3, #0
        AND R4, R4, #0

	ADD R3, R6, #0                    ;copy value in r6 to r3
	LD R4, DIGITS

	AND R0, R0, #0                    ; initialise output register to 0
	AND R5, R5, #0                    ; initialise digit counter to 0 
	AND R1, R1, #0                    ; initialise bit counter to 0
	AND R2, R2, #0                    ; initialise r2 to 0 (will be used to check how many digits we have)

	DIGCHECK      ADD R2, R5, #-4     ; check if we have 4 digits yet by subtracting this from digit counter
		      BRn BITCOUNT        ; move to bitcount if we do not

	COMPLETE      RET                 ; go back to 'valid' block

	BITCOUNT      ADD R1, R1, #-4     ; check if we have all the bits in the same way we checked for digits 
		      BRn SHIFTLEFT       ; shift r4 left if we do not have all bits

	CHECKRANGE    ADD R4, R4, #-10    ; subtract total of 10 from digit to check if it is in range
		      BRn CONVERT
		      ADD R4, R4, #15
		      ADD R4, R4, #15
		      ADD R4, R4, #15
		      ADD R4, R4, #15
		      ADD R4, R4, #5      ; if number is out of range then add 'A' (x0041 or decimal 65)
		      ADD R0, R4, #0      ; copy the output digit to r0 
                      ST R7, PRINT_SaveR7 ; save value in r7 before calling 'out' subroutine
		      OUT                 ; display
                      LD R7, PRINT_SaveR7 ; reload r7 
		      ADD R5, R5, #1      ; increment digit counter
		      AND R4, R4, #0      ; reset r4 to 0
		      BR DIGCHECK         ; check back for number of digits displayed so far

	CONVERT       ADD R4, R4, #10     ; add back the 10 that was removed earlier before adding offset
		      ADD R4, R4, #15
		      ADD R4, R4, #15
		      ADD R4, R4, #15
		      ADD R4, R4, #3       ; number in range so add '0' (x0030 or decimal 48)
		      ADD R0, R4, #0
                      ST R7, PRINT_SaveR7         
		      OUT
                      LD R7, PRINT_SaveR7
		      ADD R5, R5, #1
		      AND R4, R4, #0           
		      BR DIGCHECK       

	SHIFTLEFT     ADD R1, R1, #4      ; add back the 4 that was subtracted to check if we have correct number of bits
		      ADD R4, R4, R4      ; shift r4 left to make room for incoming bit

	DATAMSB       AND R3, R3, R3      ; check the MSB of r3
		      BRn INCDIGITS       ; if it is a 1, add 1 to r4
		      ADD R4, R4, #0      ; else add zero to r4
		      BR SHIFTDATALEFT    ; shift r3 left
	  
	INCDIGITS     ADD R4, R4, #1        

	SHIFTDATALEFT ADD R3, R3, R3
		      ADD R1, R1, #1      ; increment bit counter
		      BR BITCOUNT         ; go back to check if bitcount is <= 4        

	DIGITS .FILL x0000                ; MSB from r3 will be moved to LSB of this location 

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
;EVALUATE

;your code goes here --> my 'evaluate' code is at the top


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
ADDITION
        AND R0, R0, #0
        ADD R0, R3, R4                     ;add the two inputs and store the result in r0
        JSR PUSH                           ;push value in r0 back onto the stack
        JSR GETCHAR	                   ;read the next input
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
SUBTRACTION
        AND R0, R0, #0	
	NOT R3, R3
        ADD R3, R3, #1                     ;negate result of first pop
        ADD R0, R4, R3                     ;perform subtraction and store result in r0
        JSR PUSH
        JSR GETCHAR
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MULTIPLICATION	
	AND R1, R1, #0 			    ;check if either of the values to be multiplied are zero
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R4, R1
	BRz ZEROIN		            ;set result to zero and push onto stack if one of the inputs is zero
   	AND R1, R1, #0   		    ;check if either of the values to be multiplied are zero
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R3, R1
	BRz ZEROIN	
	AND R0, R0, #0
        MULTLOOP
        	ADD R0, R0, R4              ;keep adding second value to itself and store result in r0
                ADD R3, R3, #-1             ;use first value as a counter
                BRp MULTLOOP                ;break from loop once value 2 has been added to it self value 1 times
        JSR PUSH
        JSR GETCHAR
	ZEROIN
		AND R0, R0, #0
		JSR PUSH
		JSR GETCHAR
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIVISION	
	AND R0, R0, #0
        AND R1, R1, #0
	NOT R4, R4
	ADD R4, R4, #1
	AND R2, R2, #0
        DIVLOOP
        	ADD R1, R1, R3               ;add denominator to itself until numerator value is reached or exceeded
                ADD R0, R0, #1               ;increment counter to keep track of number of additions, as this will be the final result
		ADD R2, R1, R4               ;subtract numerator from cumulative sum so we know when to break from the loop
		BRn DIVLOOP
	JSR PUSH
	JSR GETCHAR
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
POWER
	AND R1, R1, #0
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R3, R1
	BRz EXPZERO                           ;check if the exponent is zero
        AND R1, R1, #0
	ADD R1, R1, #-1
	ADD R1, R3, R1
	BRz EXPONE                            ;check if the exponent is one
	EXPLOOP
		AND R1, R1, #0
		ADD R1, R1, R4		      ;will be used as a counter for multloop
		AND R2, R2, #0
		ADD R2, R2, #1		      ;will be used to count number of multiplications (external counter)
		AND R5, R5, #0
		NOT R3, R3
		ADD R3, R3, #1		      ;negate exponent to keep track of how many times a number has been multiplied
		AND R0, R0, #0			
		INNERLOOP		
			ADD R0, R0, R4             
                	ADD R1, R1, #-1             
                	BRp INNERLOOP         ;modified version of mult loop
		ADD R2, R2, #1                ;increment external counter
		ADD R5, R2, R3
		BRn INNERLOOP
		JSR PUSH
		JSR GETCHAR 
	EXPZERO
		AND R0, R0, #0
		ADD R0, R0, #1                ;if the exponent is zero, return 1
		JSR PUSH
		JSR GETCHAR
	EXPONE
		AND R0, R0, #0
		ADD R0, R0, R4
		JSR PUSH
		JSR GETCHAR		      ;if the exponent is one, return base
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
	ST R4, POP_SaveR4	;save R4
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
STACK_TOP       .FILL x4000     ;

.END
