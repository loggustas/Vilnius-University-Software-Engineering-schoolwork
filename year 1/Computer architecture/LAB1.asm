%include 'yasmmac.inc'
org 100h

section .text

start:                  

    mov ah, 09h
	  mov dx, duomenys
	  int 21h
    macNewLine
    
    mov ah, 09h			;vartotojo sasaja
    mov dx, prasymas      
    int 21h     
       
    mov ah, 0Ah              ; vartotojas iveda eilute
    mov dx, bufferis 
    int 21h
    
    mov ah, 09h				;paprasau 3 skaiciu
    mov dx, prasymas3
    int 21h
    mov dx, newline
    int 21h
    
    macPutString 'Iveskite pirmaji skaiciu: ','$'
    call procGetUInt16		;vartotojas veda tris skaicius atskirose eilutese
    mov [a], ax
    macNewLine
    macPutString 'Iveskite antraji skaiciu: ','$'
    call procGetUInt16
    mov [b], ax
    macNewLine
    macPutString 'Iveskite treciaji skaiciu: ','$'
    call procGetUInt16
    mov [c], ax
    macNewLine
    
    
    mov ah, [bufferis+1]
    mov [bufferis2+1], ah
    mov cx, 0000h
    mov bx, 0000h
    mov dx, 0000h
    mov bl, 1
    mov cl, [bufferis+1]
    ciklas:
    mov al, [bufferis+bx+1]
    mov [bufferis2+bx+1], al
    inc bl
    cmp bl, cl
    jle ciklas
  
    mov byte [bufferis+bx+1], 0Dh
    mov byte [bufferis+bx+2], 0Ah
    mov byte [bufferis+bx+3], '$'
  
    mov ah, 09h
    mov dx, newline
    int 21h
       
    mov al, [bufferis2+5]   ;ketvirtas simbolis
    mov ah, [bufferis2+6]   ;penktas simbolis  
    mov [bufferis2+5], ah
    mov [bufferis2+6], al   ;keiciu vietomis
    
    mov bx, 0h
    mov bl, [bufferis2+1]
    mov byte [bufferis2+bx+2], '|'
    mov byte [bufferis2+bx+3], 0Dh
    mov byte [bufferis2+bx+4], 0Ah	; apkeiciu 4 ir 5 simbolius
    mov byte [bufferis2+bx+5], '$'
    mov ah, 09h
    mov dx, newline
    int 21h  
    mov dx, pranesimas
    int 21h
    mov dx, bufferis2+2
    int 21h                 ;antro stepo pabaiga
    
    mov bx, 0000h
    mov ax, 0000h
    mov cx, 0000h
    mov dx, 0000h
    mov ch, [bufferis+1]
    mov bl, 1
    macPutString 'Kiekvieno simbolio antro, trecio ir priespaskutiniu bitu sumos:', crlf, '$' 
    bitai:
    mov ax, [bufferis+bx+1]    ;isikeliu simboli einamaji
    
    mov dx, ax
    and dx, 0040h
    mov cl, 6
    shr dx, cl
    add word [sum], dx

    mov dx, ax
    and dx, 0008h
    mov cl, 3
    shr dx, cl
    add word [sum], dx
    
    mov dx, ax
    and dx, 0004h
    mov cl, 2
    shr dx, cl
    add word [sum], dx
    
    mov ax, [sum]
    call procPutUInt16
    macPutString ' $'
    mov byte [sum], 00h
    inc bl
    cmp bl, ch
    jle bitai
    
    macNewLine           ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;C uzdavinys
  
    mov ax, 3E8h                 ;1000/a ats
    mov dx, 0000h
    mov bx, [a]
    div bx
    add ax, 15
    mov [rez1], ax   

    mov ax, [b]                  ;b%c ats
    mov dx, 0000h
    mov bx, [c]
    div bx

    mov [rez2], dx 
    mov ax, [a]               ; a/2+1 ats
    mov bx, 2h
    mov dx, 0000h
    div bx

    inc ax
    mov [rez3], ax

    mov bx, [rez3]
    mov ax, 17h
    cmp ax, bx
    jge .rezultatas
    mov ax, bx

    .rezultatas:
    mov [rez4], ax
    mov ax, [rez1]
    mov bx, [rez2]
    call procMinUInt16
    mov bx, [rez4]
    call procMinUInt16
    
    macPutString crlf, 'Maziausias yra : $'
    call procPutUInt16
    macNewLine
    
    mov ah, 4Ch
    int 21h
    
    
procMinUInt16:
cmp ax, bx
jb .pab
xchg ax, bx
.pab:
ret

%include 'yasmlib.asm'
section .data
      
      duomenys:
		    db 'Gustas Logvinovas, 1kursas, 2 grupe', 0Dh, 0Ah, '$'
      prasymas:
        db 'Iveskite nuo 10 iki 80 simboliu,apsikeis 4 ir 5 simboliai bei gale prisides "|": ', 0Dh, 0Ah, '$'
      prasymas3:
        db 'Iveskite tris sveikus skaicius a,b,c nuo 1 iki 65536: ', 0Dh, 0Ah, '$'
      bufferis:
        db 60h, 00h  ,'****************************************************************************************************************************************************************************************************************************'      
      bufferis2:
        db 60h, 00h  ,'****************************************************************************************************************************************************************************************************************************'        
       newline:
        db 0Dh, 0Ah, '$'   
       pranesimas:
        db 'Gauta tokia eilute: ', 0Dh, 0Ah, '$'
       sum:
        dw 00
      a:
        dw 00
      b:
        dw 00
      c:
        dw 00
      rez1:
        dw 00
      rez2:
        dw 00
      rez3:
        dw 00
      rez4:
        dw 00       ;didziausias
        
        
section .bss