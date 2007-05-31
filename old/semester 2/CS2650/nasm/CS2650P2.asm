			;Joshua Braegger CS2650 Assembler Program #2 

[BITS 16]               ; Set code generation to 16 bit mode
%include 'exebin.mac'

EXE_Begin

[ORG 100H]				; set addressing to begin at 100H

main:	call cls		; clear screen
	call dsnm			; display name
	call gdate			; get date
	call ddate			; display date
	call gtime			; get time
	call dtime			; display time
	call stop 			; terminate the program


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

;display the name
dsnm:	lea bp,[Name]
	mov cx,15           ; number of characters in my name
   	mov al,00H 			; write Mode
    	mov bh,00H 		; video Page
    	mov bl,0fH 		; attribute byte
	mov ah,13H 
;	mov dh,13  			; row to start writing
;	mov dl,00   		; column to start writing
	int 10H
	ret 				; return control up to the top

;Get and Convert the system date from BCD to ASCII
gdate:
	mov ah,04h
	int 1AH				; retrieve system date

day:
	mov bh,dl			; move month value into bh
	times 4 shr bh,1
	add bh,30h			; convert to ascii
	mov [Date+3],bh

	mov bh,dl
	and bh,0fh	
	add bh,30h
	mov [Date+4],bh

month:
	mov bh,dh			; get hours
	times 4 shr bh,1	; move upper nibble to lower
	add bh,30h			; convert to ascii
	mov [Date],bh		; move into masked area
	
	mov bh,dh			; get hours
	and bh,0fh			; zero high nibble
	add bh,30h			; convert to ascii
	mov [Date+1],bh		; move into masked area
	
cent:
	mov bh,ch
	times 4 shr bh,1
	add bh,30h
	mov [Date+6],bh
	
	mov bh,ch
	and bh,0fh			; zero high nibble
	add bh,30h
	mov [Date+7],bh

year:
	mov bh,cl
	times 4 shr bh,1
	add bh,30h
	mov [Date+8],bh

	mov bh,cl
	and bh,0fh
	add bh,30h
	mov [Date+9],bh
	ret 				; return control up to the top

; Get and Convert the Time from BCD to ASCII

gtime:
	mov ah,02h			; retreive system time
	int 1ah

hour:
	mov bh, ch			; get hours BCD
	times 4 shr bh,1
	add bh,30h
	mov [Time],bh

	mov bh,ch
	and bh,0fh			; mask off upper byte
	add bh,30h
	mov [Time+1],bh

minute:	
	mov bh,cl			; get minutes BCD
	times 4 shr bh,1	; shift upper nibble to lower nibble of byte
	add bh,30h			; add 30h to create ascii
	mov [Time+3],bh		; mov ascii number into masked area

	mov bh,cl	
	and bh,0fh			; mask off upper part of byte
	add bh,30h
	mov [Time+4],bh

second:
	mov bh,dh			; get seconds BCD
	times 4 shr bh,1	; shift upper nibble to lower nibble of byte
	add bh,30h
	mov [Time+6],bh

	mov bh,dh
	and bh,0fh			; mask off upper part of byte
	add bh,30h			; make ascii value
	mov [Time+7],bh	
	ret					; return to main

; print the system date

ddate:
	lea bp,[Date]
	mov cx,10
	mov al,00H 			; write Mode
    	mov bh,00H 		; video Page
    	mov bl,0fH 		; attribute byte
	mov ah,13H 
	mov dh,14  			; row to start writing
	mov dl,00   		; column to start writing
	int 10H		
	ret 				; return control up to the top

; print the system time

dtime:
	lea bp,[Time]
	mov cx,8
	mov al,00H 			; write Mode
    	mov bh,00H 		; video Page
    	mov bl,0fH 		; attribute byte
	mov ah,13H 
	mov dh,15  			; row to start writing
	mov dl,00		   	; column to start writing
	int 10H		
	ret 				; return control up to the top
	
	
cent2:
	mov bh,ch
	times 4 shr bh,1
	add bh,30h
	mov [Date+6],bh
	
	mov bh,ch
	and bh,0fh			; zero high nibble
	add bh,30h
	mov [Date+7],bh
	
dtime2:
	lea bp,[Time]
	mov cx,8
	mov al,00H 			; write Mode
    	mov bh,00H 		; video Page
    	mov bl,0fH 		; attribute byte
	mov ah,13H 
	mov dh,15  			; row to start writing
	mov dl,00		   	; column to start writing
	int 10H		
	
	
	

stop:  	int 20H			; terminate the program

Data:
Name: 	db 'Joshua Braegger'
Date:	db '00/00/0000'
Time:	db '00:00:00'
EXE_End