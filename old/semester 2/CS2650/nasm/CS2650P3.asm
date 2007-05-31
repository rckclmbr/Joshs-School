	;Joshua Braegger CS2650 Assembler Program #3 

[BITS 16]               ; Set code generation to 16 bit mode
%include 'exebin.mac'

EXE_Begin

[ORG 100H]				; set addressing to begin at 100H

main:
	call cls		; clear screen
	call dsnm			; display name
	call cursor
	call day
	call month
	call date
	call year
	call time
	call ampm
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
	mov dh,13  			; row to start writing
	mov dl,00   		; column to start writing
	int 10H
	ret 				; return control up to the top

cursor:
;position cursor
	mov ah,02H
	mov bh,00H
	mov dh,12
	mov dl,00
	int 10h
	ret

day:
;read day from DOS
	mov ah,2aH
	int 21h
	mov bh,al
; convert day into words
bDOW:
		CMP BH,00 
		JNZ cmon 
		LEA DX, [Sunday] 

cmon: 	CMP BH,01 
		JNZ ctue 
		LEA DX,[Monday] 

ctue:	CMP BH,02 
		JNZ cwed 
		LEA DX,[Tuesday] 

cwed: 	CMP BH,03
		JNZ cthurs
		LEA DX,[Wednesday]

cthurs: CMP BH,04
		JNZ cfri
		LEA DX,[Thursday]

cfri: 	CMP BH,05
		JNZ csat
		LEA DX,[Friday]

csat:	CMP BH,06
		JNZ eDOW
		LEA DX,[Saturday]
eDOW: 

; display results
	mov ah,09h
	int 21h
	ret

month:
;read month from DOS
	mov ah,2aH
	int 21h

	mov bh,dh

bmonth:
		CMP BH,01h
		JNZ cFebruary
		LEA DX, [January] 
cFebruary:
		CMP BH,02h
		JNZ cMarch 
		LEA DX, [February] 

cMarch:
		CMP BH,03h
		JNZ cApril 
		LEA DX, [March] 

cApril:
		CMP BH,04h
		JNZ cMay 
		LEA DX, [April] 

cMay:
		CMP BH,05h
		JNZ cJune 
		LEA DX, [May] 

cJune:
		CMP BH,06h
		JNZ cJuly 
		LEA DX, [June] 

cJuly:
		CMP BH,07h
		JNZ cAugust 
		LEA DX, [July] 

cAugust:
		CMP BH,08h
		JNZ cSeptember 
		LEA DX, [August] 

cSeptember:
		CMP BH,09
		JNZ cOctober 
		LEA DX, [September] 

cOctober:
		CMP BH,10h
		JNZ cNovember 
		LEA DX, [October] 

cNovember:
		CMP BH,11h
		JNZ cDecember 
		LEA DX, [cDecember] 

cDecember:
		CMP BH,12h
		JNZ emonth 
		LEA DX, [December] 
emonth:

;display results
	mov ah,09h
	int 21h
	ret
	
date:
;read date from DOS

	mov ah,2aH
	int 21h

	mov ah,00h
	mov al,dl
	mov bl,0Ah
	
	DIV bl
	ADD al,30h
	ADD ah,30h
	mov [dday],al
	mov[dday+1],ah
	lea dx,[dday]

; display results
	mov ah, 09H
	int 21H
	ret
	
year:
;read year from dos

	mov ah,2aH
	int 21h
	
; first one (1000's), dx is used for next one
	mov ah,00h
	mov ax,cx
	mov cx,03E8h
	mov dx,0000h	
	
	DIV cx
	ADD ax,30h
;	ADD dx,30h			;no need for this, we'll do it at the end
	mov [dyear],ax


;second one (100's)
	mov ah,00h
	mov ax,dx 			;move ax into dx for next one
	mov cx,64h
	mov dx,0000h

	DIV cx
	ADD ax,30h
;	ADD dx,30h			;no need for this, we'll do it at the end
	mov [dyear+1],ax


;third one (10's and 1's .... 8-bit this time)
	mov ax,dx			;move dx into ax for next one
	mov bl,0Ah
	mov ah,00h
	
	DIV bl
	ADD al,30h
	ADD ah,30h
	mov [dyear+2],al
	mov [dyear+3],ah

	lea dx,[dyear]
;display results
	mov ah, 09H
	int 21H
	ret


time:
;call time
	mov ah,2Ch
	int 21h

;get hours
	
	cmp ch,13
	jl am
	SUB ch,12
am:	
	mov ah,00h
	mov al,ch
	mov bl,0Ah
		
	DIV bl
	ADD al,30h
	ADD ah,30h
	
	
	mov [dtime],al
	mov[dtime+1],ah


; Get minutes
	mov ah,00h
	mov al,cl
	mov bl,0Ah
	
	DIV bl
	ADD al,30h
	ADD ah,30h
	
	mov [dtime+3],al
	mov [dtime+4],ah
	lea dx,[dtime]
	mov ah, 09H
	int 21H
	ret	
	
; am or pm?
ampm:
	mov ah, 2ch
	int 21h

	cmp ch,13
	jl sam
	lea dx,[dpm]
	mov ah, 09H
	int 21H
	ret		
sam:
	lea dx,[dam]
	mov ah, 09H
	int 21H
	ret	
stop:
;move cursor again to bottom
	mov ah,02H
	mov bh,00H
	mov dh,23
	mov dl,00
	int 10h

	

  	int 20H				; terminate the program

Data:
Name: 	db 'Joshua Braegger'
Sunday:    db 'Sunday, $'
Monday:    db 'Monday, $'
Tuesday:   db 'Tuesday, $'
Wednesday: db 'Wednesday, $'
Thursday:  db 'Thursday, $'
Friday:    db 'Friday, $'
Saturday:  db 'Saturday, $'

January		db	'January $'
February	db	'February $'
March		db	'March $'
April		db	'April $'
May			db	'May $'
June		db	'June $'
July		db	'July $'
August		db	'August $'
September	db	'September $'
October		db	'October $'
November	db	'November $'
December	db	'December $'

dday:		db '00, $'
dyear:      db '0000, $'
dtime:		db	'00:00$'
dam:		db	'am$'
dpm:		db	'pm$'

EXE_End