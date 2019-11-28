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
        mov eax, ecx
        mov ebx, 8
        mul ebx
        sub eax, 8
        mov ebx,[ebp+8]
        add ebx, eax
        movd mm0 ,[ebx]
        mov ebx, [ebp+12]
        add ebx, eax
        movd mm1,[ebx]
    _mmxMask:
        mov ebx, [ebp+16]
        add ebx, eax
        movd mm2,[ebx]

        pand mm1, mm2   
        pand mm2, mm0  
        por mm1, mm2    
        mov ebx, [ebp+8] ; img1
        add ebx, eax
        movd [ebx], mm1
        loop mmxLoop
    _Endmmx:
    emms 
    mov esp, ebp 
    pop ebp 
    ret
