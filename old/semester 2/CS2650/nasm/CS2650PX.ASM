	;Joshua Braegger CS2650 Assembler Program EXTRA CREDIT
	;I didn't finish it, sorry

[BITS 16]               ; Set code generation to 16 bit mode
%include 'exebin.mac'

EXE_Begin

[ORG 100H]				; set addressing to begin at 100H

main:
		call cls			; clear screen
	
		;move cursor and display my name
		mov dh,01
		call cursor
		
		call showquery
		call display
		
		call inputquery
		;move cursor to next line
		mov dh,02
		call cursor
		call gowhere

		call stop 
	
	

display:				; gives output
		mov ah, 09H
		int 21H
		ret
		
cursor:					; position cursor
		mov ah,02H
		mov bh,00H
		mov dl,00
		int 10h
		ret
	
cls: 					;clear the screen
		mov ah,06H
    	mov al,0
    	mov bh,0fH
		mov ch,0
		mov cl,0
		mov dh,25
		mov dl,80
    	int 10H
    	ret				; return control up to the top
    	

showquery:
		lea dx,[dquery]
		ret

inputquery:		
		mov ah,0Ah
		lea dx,[buff]
		int 21h
		ret
		
gowhere:
		mov ah,[buff+2]
		
		cmp ah,'Q'
		jz stop
		cmp ah,'q'
		jz stop
		cmp ah,'F'
		jz fromdec
		cmp ah,'f'
		jz fromdec
		cmp ah,'T'
		jz todec
		cmp ah,'t'
		jz todec
		ret
		
fromdec:
		lea dx,[enternum]
		call display
		
		mov ah,0Ah
		lea dx,[number]
		int 21h
		
		jmp main

todec:
		lea dx,[enternum]
		call display
		
		mov ah,0Ah
		lea dx,[number]
		int 21h
		jmp main
		

stop:
		
		;move cursor to bottom again (to be pretty) and end the program
		mov dh, 23
		call cursor
		int 20H				; terminate the program
	
Data:
name: 		db 'Joshua Braegger $'
dquery:		db 'Convert (F)rom decimal or (T)o decimal or (Q)uit $'
buff:		db '11x$'
enternum:	db 'Enter number to convert $'
number:		db '      $'
