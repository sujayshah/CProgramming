.ORIG x3000

;;R5 - frame pointer
;;R6 - stack pointer

;;MAIN - DO NOT CHANGE ANY CODE HERE
  LD R6, STACK
  LD R5, STACK
  LD R1, X_VAL
  LD R2, Y_VAL
  STR R1, R5, #0    ; push x to stack
  STR R2, R5, #-1   ; push y to stack
  ADD R6, R6, #-2   ; space for z

;IMPLEMENT ME: STACK BUILD-UP FOR FOO1
	ADD R6, R6, #-1 
	STR R7, R6, #0  ; push return address
	ADD R6, R6, #-1
	STR R5, R6, #0  ; push frame pointer
	ADD R5, R6, #-1 ; set new frame pointer
	ADD R6, R6, #-1 ; space for local variable 'total' 


;IMPLEMENT ME: CALL FOO1 SUBROUTINE
	BR FOO1



;IMPLEMENT ME: STACK TEAR-DOWN FOR FOO1
	ADD R6, R6, #1  ; pop local variable
 	LDR R5, R6, #0  ; restore frame pointer 
	ADD R6, R6, #1
	LDR R7, R6, #0  ; pop return address
	ADD R6, R6, #1
	LDR R0, R6, #0  ; store return value in r0
	STR R0, R5, #0   
	ADD R6, R6, #1
	ADD R5, R6, #2  ; pop arguments	


;IMPLEMENT ME: “return 0“
	HALT


;;IMPLEMENT ME: FOO1 SUBROUTINE
	AND R0, R0, #0
	ADD R0, R5, #4  ; store x in r0 

	FOO1
		ADD R0, R0, #0  ; check x value 
		BRp FOO2        ; branch to foo2 subroutine if x > 0
		ADD R0, R0, #-1 ; decrement x
		BRp FOO1        ; loop back if x is still > 0
		STR R5, R4, #0  ; else store return value
		RET              


;;IMPLEMENT ME: FOO2 SUBROUTINE
	AND R3, R3, #0
	ADD R3, R5, #5  ; store y in r3
	AND R4, R4, #0

	FOO2
		ADD R4, R4, R3  ; store 'currentTotal' in r4
		RET


STACK .FILL x6000
X_VAL .FILL x5
Y_VAL .FILL x4

.END 
