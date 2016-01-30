;modified POP to store value in R6.
;R0 is being used to store the input character

.ORIG x3000

AND R0, R0, #0                  ;clear r0

GETCHAR 
        GETC	                ;character into r0
        OUT                     ;echo
        LD R1, SPACE            ;get ascii for space
        NOT R1, R1
        ADD R1, R1, #1          ;negate space ascii
        ADD R1, R0, R1          ;add them together
        BRz GETCHAR             ;if the input is a space, branch back to get another character

LINECHECK  
        LD R1, NEW_LINE         ;get ascii for \n (linecheck)
        NOT R1, R1
        ADD R1, R1, #1          ;negate newline
        ADD R1, R0, R1          ;add them together
        BRz CHECKSTACK          ;if a new line was entered then user is done and we need to check for balanced parentheses

JSR IS_BALANCED                 ;if neither a space nor enter has been input, then we have a valid character and need to run it through the algorithm  

CHECKSTACK
        JSR POP
        AND R1, R1, #0
        ADD R1, R5, R1
        BRp BALANCED            ;if pop failed due to underflow, there are no remaining elements in stack and parentheses are balanced
        AND R1, R1, #0          ;reinitialise r1
        LD R1, OPEN_BRACKET   
        NOT R1, R1
        ADD R1, R1, #1
        ADD R1, R6, R1          ;subtract open bracket ascii from popped character and store in r1
        BRz UNBALANCED          ;since there is a left parentheses left in the stack, we have an unbalanced situation

UNBALANCED
        AND R6, R6, #0         
        ADD R6, R6, #-1         ;set r6 to -1 if a starting bracket is detected in the stack as this means that parentheses are unbalanced
        BR DONE

BALANCED
        AND R6, R6, #0
        ADD R6, R6, #1          ;set r6 to 1 for balanced and exit programme
        BR DONE
                              
DONE    HALT

SPACE	        .FILL x0020
NEW_LINE	.FILL x000A
CHAR_RETURN	.FILL x000D     ;carriage return --> used to move cursor to beginning of same line of text
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;if ( push onto stack if ) pop from stack and check if popped value is (
;input - R0 holds the input
;output - R6 set to -1 if unbalanced. else not modified.

IS_BALANCED                     ;this will be one of our subroutines to check balanced parentheses (steps a and b, call this each time we have input)
        LD R1, OPEN_BRACKET
        NOT R1, R1
        ADD R1, R1, #1          
        ADD R1, R0, R1          ;subtract ascii value for left parentheses from current character
        BRz GOTOPUSH            ;if result is zero then go to push subroutine
        LD R1, CLOSED_BRACKET   ;if input was not a left parentheses then check for right parentheses
        NOT R1, R1
        ADD R1, R1, #1          
        ADD R1, R0, R1          
        BRz GOTOPOP             ;if result is zero then go to push subroutine

GOTOPOP
        JSR POP
        AND R1, R1, #0
        ADD R1, R5, R1
        BRp UNBALANCED         ;pop failed, no elements left in stack --> unbalanced
        LD R1, OPEN_BRACKET   
        NOT R1, R1
        ADD R1, R1, #1         
        ADD R1, R6, R1         ;subtract open bracket ascii from popped character and store in r1
        BRz GETCHAR            ;if popped value=starting bracket, everything is fine so fetch next character
        AND R6, R6, #0         
        ADD R6, R6, #-1
        BR DONE                ;else unbalanced so set r6 to -1 and exit the programme
        
GOTOPUSH
        JSR PUSH                ;pushes r0 onto stack for left parentheses
        BR GETCHAR              ;read the next character         

OPEN_BRACKET   .FILL x0028
CLOSED_BRACKET .FILL x0029

NEG_OPEN .FILL xFFD8

;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;initialise r5 --> will be used to determine success or failure
	LD R3, STACK_END	
	LD R4, STACK_TOP	
	ADD R3, R3, #-1		;decrement stack end address so it corresponds to the topmost position on the stack
	NOT R3, R3		
	ADD R3, R3, #1		
	ADD R3, R3, R4		;subtract end memory address from top address
	BRz OVERFLOW		;stack is full as top=end
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		

OVERFLOW
	ADD R5, R5, #1		;set r5 to failed

DONE_PUSH
	LD R3, PUSH_SaveR3	
	LD R4, PUSH_SaveR4	;restore values originally in r3 and r4
	RET                     ;programme escapes this block and continues


PUSH_SaveR3	.BLKW #1	
PUSH_SaveR4	.BLKW #1	;reserve memory locations for original values in r3 and r4 before push


;OUT: R6, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	
	LD R4, STACK_TOP	
	NOT R3, R3		
	ADD R3, R3, #1		
	ADD R3, R3, R4		
	BRz UNDERFLOW		;if start=stop
	ADD R4, R4, #1		;increment top address
	LDR R6, R4, #0		;store popped value into r6             
	ST R4, STACK_TOP	
	BRnzp DONE_POP		

UNDERFLOW
	ADD R5, R5, #1		;indicate failure

DONE_POP
	LD R3, POP_SaveR3	
	LD R4, POP_SaveR4	;load back original register values
	RET                     ;programme escapes this block and continues


POP_SaveR3	.BLKW #1	
POP_SaveR4	.BLKW #1	;reserves memory space for original values in r3 and r4 before pop
STACK_END	.FILL x3FF0	;last memory address available
STACK_START	.FILL x4000	;first memory address available
STACK_TOP	.FILL x4000	;top of stack pointer (currently same as start)

.END


