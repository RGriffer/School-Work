; Author: Fritz Sieker
;
; ------------------------------------------------------------------------
; Begin reserved section - do not change ANYTHING is this section
; except the .FILL values of option, data1, data2

               .ORIG x3000
               BR Main

option         .FILL 0          ; select routine to test
data1          .FILL 0          ; use ONLY for testing
data2          .FILL 0          ; use ONLY for testing

stackBase      .FILL X4000      ; initial sttack pointer

Main           LD R6,stackBase  ; initialize stack pointer
               LD R0,option     ; select routine to test
               BRZ testPrintNum ; option = 0 means test printNum

               ADD R0,R0,#-1
               BRZ testGetDigit ; option = 1 means test getDidit

               ADD R0,R0,#-1
               BRZ testDivRem   ; option = 2 means test divRem

               HALT             ; invalid option if here

testPrintNum                    ; call printNum(x, base)
               LD R0,data2
               PUSH R0          ; push base argument
               LD R0,data1
               PUSH R0          ; push value argument
               JSR printNum
               ADD R6,R6,#2     ; caller clean up 2 parameters
               BR endTest

testGetDigit                    ; call getChar(val)
               LD R0,data1
               PUSH R0          ; push argument (val to convert to ASCII)
               JSR getDigit     ; 
               POP R0           ; get the corresponding character
               ADD R6,R6,#1     ; caller clean up 1 parameter
               OUT              ; print the digit
               NEWLN
               BR endTest

testDivRem                      ; call divRem(num, denom, *quotient, *remainder)
               LEA R0,data2     ; get pointer to remainder (&data2)
               PUSH R0
               LEA R0,data1     ; get pointer to quotient (&data1)
               PUSH R0
               LD R0,data2
               PUSH R0          ; push demoninator
               LD R0,data1
               PUSH R0          ; push numerator
               JSR divRem       ; call routine
               ADD R6,R6,#4     ; caller clean up 4 parameters

endTest        LEA R0,endMsg
               PUTS
theEnd         HALT             ; look at data1/data2 for quotient/remainder

                                ; useful constants
endMsg         .STRINGz "\nTest complete!\n"

negSign        .FILL    x2D     ; ASCII '-'
digits         .STRINGZ "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" ; up to base 36

; end reserved section

; ------------------------------------------------------------------------
; Author: your name goes here
; ------------------------------------------------------------------------
;
; C declaration: char getDigit (int val);

getDigit                        ; callee setup
            ADD R6, R6, #-1; Make space for return value
            PUSH R7; Save return address
            PUSH R5; save Frame pointer
            ADD R5, R6, #-1; set Frame pointer
            ADD R6, R6, #-1 ;make space for local variable
                                ; code for getDigit
            LEA R0,digits;
            LDR R1,R5,#4; gets base
            ADD R0,R0,R1;
            LDR R2,R0,#0;
            STR R2,R5,#3;
                                ; callee cleanup
            ADD R6,R6,#1; remove local var
            POP R5; pop FP
            POP R7; Pop return addr
            RET              ; return
; ------------------------------------------------------------------------
;
; C declaration: void divRem(int num, int denom, int*quotient, int*remainder);

divRem                          ; callee setup
            PUSH R7; return addr
            PUSH R5; callers frame pointer
            ADD R5,R6,#-1; set FP
            ADD R6,R6,#-1; space for negDenominator
                                ; code for dicRem
            LDR R1,R5,#4; Denominator to R1
            NOT R1,R1;
            ADD R1,R1,#1; Negate Denominator
            STR R1,R5,#0; store negDenominator to FP position
            LDR R0,R5,#3; Load Numerator to R0
            .ZERO R3; R3 = quotient
DivSub      ADD R3,R3,#1; increments quotient
            ADD R0,R0,R1; subtracts denominator from numerator
            BRzp DivSub;
            NOT R1,R1;
            ADD R1,R1,#1; make denom positive
            ADD R3,R3,#-1; subtract 1 from quotient
            ADD R0,R0,R1;Add back the denominator to numerator
            LDR R4,R5,#6; Remainder pointer addr
            STR R0,R4,#0; store remainder
            LDR R4,R5,#5; quotient pointer0
            STR R3,R4,#0; store quotient
                                ; callee cleanup
            ADD R6,R6,#1; remove negDenominator
            POP R5; callers FP
            POP R7; return addr
            RET              ; return
; ------------------------------------------------------------------------
;
; C declaration: void printNum (int val, int base);

printNum                        ; callee setup
            PUSH R7;
            PUSH R5;
            ADD R5,R6,#-1; FP points to quotient
            ADD R6,R6,#-2; room for Quotient and Remainder
                                ; code for printNum
            LDR R1,R5,#3;
            BRzp NegPR
            PUSH R7
            LD R0,negSign;
            OUT
            POP R7
            NOT R1,R1;
            ADD R1,R1,#1
            STR R1,R5,#3
NegPR
            ADD R0,R5,#-1;
            PUSH R0;push remainder pointer
            ADD R0,R5,#0;
            PUSH R0; push pointer to quotient
            LDR R0,R5,#4
            PUSH R0;push denominator
            LDR R0,R5,#3
            PUSH R0;push numerator
            JSR divRem; call divRem quotient and remainder now have values
            ADD R6,R6,#4; clear numerator->quotient pointer storage

            LDR R1,R5,#0; Load quotient
            BRnz DONE
            LDR R2,R5,#4;
            PUSH R2; add base
            PUSH R1; add x (quotient)
            JSR printNum
            ADD R6,R6,#2;
DONE; when quotient=0	
            ;get digit
            ADD R0,R5,#-1;
            LDR R1,R0,#0
            PUSH R1
            JSR getDigit
            POP R0
            ADD R6,R6,#1
            OUT
                                ; callee cleanup
            ADD R6,R6,#2
            POP R5
            POP R7
            RET              ; return
; ------------------------------------------------------------------------
               .END
