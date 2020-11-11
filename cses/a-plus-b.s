;;;  https://cses.fi/howto
        section .text
        global _start
atoi:   xor rax,rax
        xor rdx,rdx
        lodsb
        cmp al,'-'
        sete bl
        jne .lpv
.lp:    lodsb
.lpv:   sub al,'0'
        jl .end
        imul rdx,10
        add rdx,rax
        jmp .lp
.end:   test bl,bl
        jz .p
        neg rdx
.p      ret
itoa:   std
        mov r9,10
        bt rax,63
        setc bl
        jnc .lp
        neg rax
.lp:    xor rdx,rdx
        div r9
        xchg rax,rdx
        add rax,'0'
        stosb
        xchg rax,rdx
        test rax,rax
        jnz .lp
        test bl,bl
        jz .p
        mov al,'-'
        stosb
.p:     cld
        inc rdi
        ret
_start: xor rax,rax
        xor rdi,rdi
        mov rsi,buff
        mov rdx,100
        syscall
        mov rsi,buff
        lodsb
        mov rsi,buff
        call atoi
        mov rcx,rdx
        call atoi
        add rcx,rdx
        mov rdi,buff+99
        mov rsi,rdi
        std
        mov rax,10
        stosb
        mov rax,rcx
        call itoa
        sub rsi,rdi
        mov rdx,rsi
        mov rsi,rdi
        inc rdx
        mov rax,1
        mov rdi,rax
        syscall
        mov rax,60
        xor rdi,rdi
        syscall
        section .bss
buff:   resb 100
