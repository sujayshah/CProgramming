;Reverse Characters
;n characters are provided to you
;in which n is a positive number stored at x4FFF
;characters stored in sequential memory location
;starting at x5000
;Use the subroutine REVERSE to flip the order

.ORIG x3000

LD R2, CHAR_ADDR
NOT R2, R2
ADD R2, R2, #1
LD R3, NUM_ADDR
ADD R3, R2, R3   ; r3 will now contain the ending address of the string  






;REVERSE subroutine:
;reverse the order of n characters starting at x5000
;SWAPMEM subroutine must be called here, not in the main user program
REVERSE
	AND R4, R4, #0
	ADD R4, R4, R3  ; copy ending address to r4
	ADD R3, R3, #-1 ; decrement ending address
	ADD R4, R4, #1  ; increment r4
	AND R5, R5, #0
	ADD R5, R3, R2  ; check that we have not yet reached starting address
	BRz SWAPMEM     ; all addresses have been swapped
	BR REVERSE      ; not yet finished swapping addresses, so loop back

;SWAPMEM subroutine:
;address one is in R0, address two in R1
;if mem[R0]=A and mem[R1]=B, then after subroutine call
;   mem[R0]=B and mem[R1]=A
SWAPMEM

DONE
	HALT




NUM_ADDR    .FILL x4FFF
CHAR_ADDR   .FILL x5000

.END
