.ORIG x3000

LD R3, DATA
LD R4, DIGITS
LD R5, ASCII_OFFSET_INRANGE
LD R6, ASCII_OFFSET_OUTRANGE

AND R0, R0, #0 ; initialise digit counter to 0 
AND R1, R1, #0 ; initialise bit counter to 0
AND R2, R2, #0 ; initialise r2 to 0 (will be used to check if digit is within range)

DIGCHECK ADD R0, R0, #-4 ; check if we have 4 digits yet by subtracting this from digit counter
         BRn BITCOUNT    ; move to bitcount if we do not

DONE TRAP x25            ; exit the programme once we have all the digits

BITCOUNT ADD R1, R1, #-4 ; check if we have all the bits in the same way we checked for digits 
         BRn SHIFTLEFT   ; shift r4 left if we do not have all bits

CHECKRANGE ADD R2, R4, #-16
           ADD R2, R4, #-16 
           ADD R2, R4, #-16 
           ADD R2, R4, #-9  ; subtract total of 57 (9) from digit to check if it is in range
           BRnz CONVERT
           ADD R4, R4, R6   ; if number is out of range then add 'A'
           TRAP x21         ; display
           ADD R0, R0, #1   ; increment digit counter
           BR DIGCHECK      ; check back for number of digits displayed so far

CONVERT ADD R4, R4, R5      ; number in range so add '0'
        TRAP x21
        ADD R0, R0, #1          
        BR DIGCHECK       

SHIFTLEFT ADD R4, R4, R4  ; shift r4 left to make room for incoming bit

DATAMSB AND R3, R3, R3    ; check the MSB of r3
        BRp INCDIGITS     ; if it is a 1, add 1 to r4
        ADD R4, R4, #0    ; else add zero to r4
        BR SHIFTDATALEFT  ; shift r3 left
  
INCDIGITS ADD R4, R4, #1          

SHIFTDATALEFT ADD R3, R3, R3
              ADD R1, R1, #1 ; increment bit counter
              BR BITCOUNT    ; go back to check if bitcount is <= 4        

   HALT

ASCII_OFFSET_INRANGE .FILL x0030  ; offset for values less than 9
ASCII_OFFSET_OUTRANGE .FILL x0037 ; offset for values greater than 9
DATA .FILL x00e0                  ; input data
DIGITS .FILL x0000                ; MSB from r3 will be moved to LSB of this location 

   .END

