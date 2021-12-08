
%include 'yasmmac.inc'
org 100h

section .text

start:  

    macPutString 'Iveskite skaiciu seka, kuri baigiasi 0', crlf, '$'
    mov di, 0      ;kiek geru skaiciu
.cycle:            ;vedam skaicius
    call procGetUInt16
    macNewLine
    cmp ax, 0
    je .pab        ;sokam i pabaiga, jei ivestas nulis
    
    push ax        ;else
    call arSkaiciusGeras
    cmp al, 2
    jne .NE
    add di, 1  ;else

    .NE:
    jmp .cycle

.pab:

    
    macPutString crlf, 'Skaiciu keikis, kuriu triju jauniausiu bitu suma yra 2 kiekis:      $'
    mov ax, di
    call procPutInt16
    macNewLine
    exit



    arSkaiciusGeras:
    push bp
    mov bp, sp
    sub sp, 2
    %define SUM byte [bp-2]
    mov SUM, 0
    mov ax, 0
    mov ax, [bp+4]      ;isimetu skaiciu i bx
    
    mov bx, ax
    and bx, 0x0001    ;bitas stovi jau tinkamoj vietoje, nereikia shiftint
    add SUM, bl       ;pridedu bl, nes jame bus skaicius, o grazinti reikia 1baito skaiciu, todel bl pridedu, nes define yra baitas

    mov bx, ax
    and bx, 0x0002
    mov cl, 1
    shr bx, cl
    add SUM, bl

    mov bx, ax
    and bx, 0x0004
    mov cl, 2
    shr bx, cl
    add SUM, bl

    mov ax, 0
    mov al, SUM   ;return the answer
    add sp, 2
    pop bp
    ret 2     



    

%include 'yasmlib.asm'
section .data

    




section .bss