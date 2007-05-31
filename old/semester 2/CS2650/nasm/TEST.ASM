			;NASM-IDE ASM Assistant Assembler Project File
[BITS 16]               ;Set code generation to 16 bit mode
%include 'exebin.mac'

EXE_Begin

[ORG 100H]		;set addressing to begin at 100H

cls: 	mov ah,06
    	mov cx,0000
    	mov dx,184fH
    	mov al,00
    	mov bh,1fH
    	int 10H

 	mov dx,0C22H
	lea bp,[Hi]
	mov cx,12
wst:   	mov al,00
    	mov bh,00
    	mov bl,1fH
	mov ah,13H
	push dx
    	int 10H
	pop dx
	cmp dh,0Ch
	jnz stop
	inc dh
	lea bp,[Bye]
	mov cx,8
	jmp wst
stop:  	int 20H

Data:
Hi:  	db 'Joshua Braegger'
Bye: 	db 'CS2650... bleh'

EXE_End






