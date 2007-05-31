;JOSHUA BRAEGGER CS2650 Assembler Program #1 
[BITS 16] ;Set code generation to 16 bit mode 
%include 'exebin.mac' 
EXE_Begin 
[ORG 100H] ;set addressing to begin at 100H 



cls: 	mov ah,06H   ; we're gonna write a color to the whole area
        mov cx,0000  ; set points
        mov dx,184fH ; to write the dark to
        mov al,00H   ; entire window is blanked
    	mov bh,0fH   ; attribute for blanked area
        int 10H      ; do it now


	lea bp,[name]   ; do this name
		mov cx,15   ; number of characters in my name
		mov al,00H  ; write mode (use 0)
		mov bh,00H  ; video page (use 0)
		mov bl,0fH  ; white on black
		mov dh,12;  ; row 12
		mov dl,00;  ; column 0
		mov ah,13H  ; use the 'write' function
		int 10h     ; do it now
		
	lea bp,[class]  ; print this class/year
		mov cx,18   ; number of characters in class name
		mov al,00H  ; write mode (use 0) *could use jmp?, but baby steps...
		mov bh,00H  ; video page (use 0)
		mov bl,0fH  ; white on black
		mov dh,13   ; on row 13
		mov ah,13H  ; use the 'write' function
		int 10h     ; do it now


stop:  INT 20H      ; we're all done

Data:

name:    db 'Joshua Braegger'
class:   db 'CS2650 Spring 2005'

EXE_End 

