%include 'yasmmac.inc'
org 100h

section .text

start:

    mov ah, 09h
    mov dx, pranesimas
    int 21h
    
    macPutString 'Iveskite pirma skaiciu: ', crlf, '$'
    call procGetUInt16
    mov [sk1], ax
    macNewLine
    macPutString 'Iveskite antra skaiciu: ', crlf, '$'
    call procGetUInt16
    mov [sk2], ax
    macNewLine
    macPutString 'Iveskite trecia skaiciu: ', crlf, '$'
    call procGetUInt16
    mov [sk3], ax
    macNewLine
    macPutString 'Iveskite ketvirta skaiciu: ', crlf, '$'
    call procGetUInt16
    mov [sk4], ax
    macNewLine

    mov ax, [sk1]
    mov dx, 0000h
    mov bx, 19               
    div bx
    mov [ats1], ax       ;a/19 ats
    
    mov ax, [sk2]
    mov dx, 0000h
    mov bx, 17
    div bx
    mov [ats2], dx       ;b%17 ats
    
    mov ax, [sk4]
    mov bx, 0003h
    add ax, bx
    mov [ats3], ax       ;d+3 ats

    mov ax, [ats1]
    mov bx, [ats2]
    call findMaxUInt      ;lygininsiu skaicius, rasau funkcija, kad isvengt pasikartojimo
    mov bx, [ats3]        ;ax bus saugomas mazesnis skaicius
    call findMaxUInt
    
    mov [ats4], ax        ;issisaugau ax, nes 100*c yra pirmesnis veiksmas
    mov ax, [sk3]
    mov bx, 100
    mul bx                ;ax yra issaugotas ats
    mov bx, [ats4]        ;i bx ikeliu maziausia skaiciu ir priededu prie 100*c
    add ax, bx            ;atsakymas ax registre

    macPutString 'Atsakymas:  ', '$'
    call procPutUInt16
    
    exit
    
    findMaxUInt:
    cmp ax, bx
    jl skip
    xchg ax, bx
    skip:
    ret

%include 'yasmlib.asm'
section .data

    pranesimas:
        db 'Programai reikia keturiu bezenkliu skaiciu, nedidesniu nei 16 bitu', 0Ah, 0Dh, '$'
    
    sk1:
        dw 00
    
    sk2:
        dw 00
    
    sk3:
        dw 00
    sk4:
        dw 00
    ats1:
        dw 00
    ats2:
        dw 00
    ats3:
        dw 00
    ats4:
        dw 00

