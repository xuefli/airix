[bits 32]

%macro syscall 2

global %2
%2:
    mov     eax, %1
    int     0x80
    ret

%endmacro

syscall 0, prints
syscall 1, fork
syscall 2, exit
