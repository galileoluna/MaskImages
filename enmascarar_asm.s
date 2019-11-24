%include "io.inc"

section .data

section .text
    global _enmascarar_asm  
_enmascarar_asm:
    push ebp
    push eax
    push ebx
    push ecx
    push edx    
    mov ebp, esp 
    mov eax, 0
    mov ebx, 0
    mov ecx, 0
    mov edx, 0
    xor edx, edx
    mov eax, dword[ebp+20]
    add ebx, 8
    div ebx
    mov ecx, eax
    _mmxLoop:
    _mmxMask:
    _Endmmx:

     ret




ret


