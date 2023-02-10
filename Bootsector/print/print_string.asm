;****************************************
;   Print a string
;****************************************
;   Parameters:
;       bx - Pointer to string
;   Return:
;       none
;****************************************

print_string:
    mov ah, 0x0e    ; Activate screen output
    cmp byte [bx], byte 0   ; if current character == 0
    je return   ; if equal return
    jne print   ; if not equal print character
    return:
        ret
    print:
        mov al, [bx]    ; move value at pointer into al
        int 0x10    ; call interrupt to print value of al on screen
        inc bx
        jmp print_string
