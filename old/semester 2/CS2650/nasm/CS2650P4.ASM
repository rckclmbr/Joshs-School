	;Joshua Braegger CS2650 Assembler Program #4

[BITS 16]               ; Set code generation to 16 bit mode
%include 'exebin.mac'

EXE_Begin

[ORG 100H]				; set addressing to begin at 100H

main:
	call cls			; clear screen
	
	;move cursor and display my name
	mov dh,20
	call cursor
	lea dx,[name]
	call display
	
	;move cursor and display serial number
	mov dh,21			; line for serial number
	call cursor			; the rest of the cursor attributes
	call getname		; gets name of computer
	call display		; displays serial number

	;get and display volume serial number
	mov dh, 22
	call cursor
	call getserial
	call printserial
	call display

	;move cursor to bottom again (to be pretty) and end the program
	mov dh, 23
	call cursor
	call stop 

;clear the screen
cls: 	mov ah,06H
    	mov al,0
    	mov bh,0fH
		mov ch,0
		mov cl,0
		mov dh,25
		mov dl,80
    	int 10H
    	ret				; return control up to the top


display:
	mov ah, 09H
	int 21H
	ret
		
; position cursor
cursor:
	mov ah,02H
	mov bh,00H
	mov dl,00
	int 10h
	ret

getname:
	mov ah, 5Eh
	mov al,0h
	lea dx,[compname]
	int 21h
	ret

getserial:
	mov ah, 02h
	mov al, 1h
	mov ch, 0h
	mov cl, 1h
	mov dh, 0h
	mov dl, 0h
	lea bx,[serial]
	int 13h
	ret

convertnum:
	cmp ah, 9		; checks if it's <= 9 or not
	jle lessthan9	; jumps to "lessthan9" if it's a number (jump less than or equal to)
	add ah, 37h		; if it's alphabet
	ret
	
lessthan9:			; if less than (in other words a number)
	add ah,30h
	ret

printserial:

	
	mov ah,[serial+27h]	
	and ah,0fh
	call convertnum
	mov [serialnum+8],ah
	
	mov ah,[serial+27h]
	times 4 shr ah, 1
	call convertnum
	mov [serialnum+7],ah

	mov ah,[serial+28h]
	and ah,0fh
	call convertnum
	mov [serialnum+6],ah
	
	mov ah,[serial+28h]
	times 4 shr ah, 1
	call convertnum
	mov [serialnum+5],ah

	mov ah,[serial+29h]
	and ah,0fh
	call convertnum
	mov [serialnum+3],ah
	
	mov ah,[serial+29h]
	times 4 shr ah, 1
	call convertnum
	mov [serialnum+2],ah
	
	mov ah,[serial+2Ah]
	and ah,0fh
	call convertnum
	mov [serialnum+1],ah

	mov ah,[serial+2Ah]
	times 4 shr ah, 1
	call convertnum
	mov [serialnum],ah

	lea dx,[serialnum]
	ret

stop:
;move cursor again to bottom

  	int 20H				; terminate the program
	
Data:
name: 		db 'Joshua Braegger $'
compname:	db '                 $'
serial: 	times 512 db 0
serialnum: 	db 'xxxx-xxxx $'
