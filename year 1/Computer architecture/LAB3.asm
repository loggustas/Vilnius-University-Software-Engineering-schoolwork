%include 'yasmmac.inc'

org 100h

section .text
;rezidentine programa, kuri pakeicia 09h int21h funckija taip, kad pakeicia visas mazasias raides i didziasias
    start:
        jmp setting

    oldInterrupt:
        dw 0, 0

    newInterrupt:
        macPushAll
        cmp ah, 09h
        jne .old

        mov bx, dx    ;dx bus adresas stringo
        mov dx, 0    ;dl tures but baitas
        mov si, 0
        .cycle:

            mov dl, [bx + si]
            cmp dl, '$'
            je .endd
            mov ah, 02h
            cmp dl, 97
            jge .maybelowercase
            mov ah, 02h
            int 21h
            inc si
            jmp .cycle

            .maybelowercase:
            cmp dl, 122
            jle .lowercase   ;lowercase
            mov ah, 02h
            int 21h                    ;else normal print
            inc si
            jmp .cycle

            .lowercase:
            sub dl, 32
            mov ah, 02h
            int 21h
            inc si
            jmp .cycle
        
        .endd:

            macPopAll
            iret

    .old:
        pushf
        call far [cs:oldInterrupt]
        macPopAll
        iret

    setting:
        push cs
        pop ds
        mov ah, 35h     ;vektoriaus gavimo funkcija
        mov al, 21h
        int 21h             ;i es:bx grazins interrupto adresa

        mov [cs:oldInterrupt], bx        ;issaugau seno IP
        mov [cs:oldInterrupt + 2], es        ;segmenta saugau
    
        mov dx, newInterrupt    ;adresa imetu naujo interrupto, DS yra lygus cs
        mov ah, 25h             ;naujo interupto vektoriaus adreso setupinimas
        mov al, 21h
        int 21h
    
        mov dx, setting + 1
        int 27h       ;rezidento interruptas

%include 'yasmlib.asm'

    
section .bss