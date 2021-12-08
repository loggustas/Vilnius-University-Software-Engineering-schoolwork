%include 'yasmmac.inc'
org 100h
;Takes csv file as parameter and prints results to output file
section .text

start:                  

    mov bx, 82h        ;command prompt parameter of filename for reading
    mov si, 0h
    jmp a

    a:
    mov cl, [bx+si]
    cmp cl, 20h   ;maziausias galimas simbolis (tarpas)
    jl b
    inc si
    jmp a
    int 21h
    
    b :
    mov byte [bx+si], '$'
    mov ah, 09
    mov dx, bx
    int 21h

    macNewLine
    macPutString 'Gustas Logvinovas, 1kursas, 2 grupe', crlf, '$'
    macPutString 'Si programa isves jusu pateikto faile esanciu stulpeliuose nr. 1,2 esanciu $'
    macPutString '     4 raidziu zodziu kieki ir grazins ji i sukurta jusu pavadinimo vardu faila. $'
    macNewLine
    macNewLine
    
    macPutString 'Iveskite isvedamu duomenu failo varda ir prievardi: $'
    mov al, 250             ;longest possible string
    mov dx, string        ;adress of filename     
    call procGetStr

    macNewLine
    
    mov ah, 3Dh     ;opening the file
    mov al, 00h     ;for reading
    mov dx, 82h     ;the filename adress
    int 21h
    mov si, ax      ;saving the file handle, si has it

    mov ah, 3fh     ;read file
    mov bx, si
    mov cx, 0xB7A0  ;amount of bytes to read
    mov dx, readingFile
    int 21h
    mov si, ax      ;saving how many bytes were read, si used for seeking symbol amount left in the file 
    mov ah, 3Eh
    int 21h         ;closing reading file

    mov bx, readingFile  ;pointer to the location in the string, si the amount of chars left in it
    mov cx, 1            ;the number of the collumn
    mov di, 0            ;for counting the amount of words of 4 letters
    mov bp, 0            ;used for counting letters
    mov dx, 0            ;used to determine wether a word has a number
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    .cycle:
      cmp si, 0        ;check if end of file
      je .endOfFile
      cmp byte [bx], 20h    ;lyginti su tarpu simboli
      je .space
      jg .symbol
      jl .trash
      
      .symbol:
        cmp byte [bx], 59    ;kabliataskis
        je .endOfCollumn
        cmp byte [bx], 57
        jle .number

        inc bp   ;else if (is a letter)
        dec si
        inc bx
        jmp .cycle
      .number:
        mov dx, 1
        inc bp
        dec si
        inc bx
        jmp .cycle

      .space:
        cmp bp, 4
        jne .not4
        cmp dx, 0
        jne .not4

        inc di    ;4 letter word found
      
      .not4:
        mov bp, 0
        mov dx, 0
        inc bx
        dec si

        jmp .cycle


      .endOfCollumn:
        cmp bp, 4
        jne .nnot
        cmp dx, 0
        jne .nnot
        inc di     ;4 letter word found
           
        .nnot:
        mov bp, 0
        mov dx, 0
        inc bx
        dec si
        inc cx
        cmp cx, 3
        je .callClear
        jmp .cycle
        
        .trash:
        mov bp, 0
        inc bx
        dec si
        jmp .cycle
        
        .callClear 
          push bx           ;pushing the adress of current location
          call cleanRow
          mov bp, 0
          mov cx, 1
          jmp .cycle

    .endOfFile:
     mov ax, di 
     mov dx, answer     ;saving the answer into the memory   
     call procUInt16ToStr
     mov ah, 3Ch       ;creating a file
     mov dx, string
     mov cx, 0h
     int 21h       

     mov ah, 3Dh      ;open file
     mov al, 1h
     mov dx, string
     int 21h
     mov si, ax       ;saving file handler

     mov ah, 40h      ;writing to file
     mov bx, si       ;moving file handler back to bx for writing function
     mov cx, 6h
     mov dx, answer
     int 21h
     
     macPutString 'Zodziu kiekis sekmingai irasytas i jusu faila ', crlf ,'$'

    exit ;end program


    cleanRow: ;skippint skaicius visokius
    push bp
    mov bp, sp
    mov bx, [bp+4]
    
    .cycle2:
      cmp byte [bx], 0Ah
      je .cleaned
      cmp si, 0
      je .cleanedFile
      inc bx
      dec si
      jmp .cycle2
    .cleaned:
    inc bx
    dec si
    .cleanedFile:
    pop bp
    ret 2


%include 'yasmlib.asm'
section .data
      
      answer:
        dw 00, 00, 00, 00, 00, 00, 00, 00
      string:
        db '*****************************************************************************************************************************************************************************************************************************************************'
      readingFile:
        times 47008 db 00, '$'




section .bss