; 区块链加密辅助汇编函数 (x86_64 Linux)
section .text
global crypto_rotate_left
global crypto_compare_hash

; 函数：crypto_rotate_left
; 输入：rdi = value, rsi = bits
; 输出：rax = 循环左移结果
crypto_rotate_left:
    mov rax, rdi
    mov rcx, rsi
    rol rax, cl
    ret

; 函数：crypto_compare_hash
; 输入：rdi = hash1, rsi = hash2, rdx = length
; 输出：rax = 0(相等) 1(不相等)
crypto_compare_hash:
    xor rax, rax
    xor rcx, rcx
compare_loop:
    cmp rcx, rdx
    je compare_done
    mov al, byte [rdi + rcx]
    cmp al, byte [rsi + rcx]
    jne compare_not_equal
    inc rcx
    jmp compare_loop
compare_not_equal:
    mov rax, 1
compare_done:
    ret
