			;NASM-IDE ASM Assistant Assembler Project File
[BITS 16]               ;Set code generation to 16 bit mode
%include 'exebin.mac'

EXE_Begin

[ORG 100H]		;set addressing to begin at 100H

MOV AX,1aceh
AND AH,0FFH
XOR AL,0FFH




int 20h

EXE_End

