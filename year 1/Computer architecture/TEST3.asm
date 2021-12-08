%include 'yasmmac.inc'

org 100h

section .text

	startas:
	
	mov dx, abc
	mov ah, 09h
	int 21h
	
	%include 'yasmlib.asm'
	
	exit
	
section .data
	abc:
		db "Asd kalmarasSS_s aaT 89*&^%*&!@#$%^ buh", '$'

section .bss