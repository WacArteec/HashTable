extern Hash_CRC32
global SearchAsm
section .text
SearchAsm:
    push r12
    push r13
    push r14
    
    mov r12, rdi        ;table
    mov r13, rsi        ;key
    
    ;Вызываем хэш-фуцнкцию
    mov rdi, r13
    mov rsi, [r12 + 16] ;table->capacity

    call Hash_CRC32
    mov r14, rax        ;Сохраняем хэш в r14
    
    ;Находим бакеты
    xor rdx, rdx
    mov rax, r14
    div qword [r12 + 16] ;Делим на table->capacity
                         ;Остаток в rdx (индекс корзины)
    
    ;Получаем указатель на цепочку
    mov rax, [r12]          ;table->buckets
    mov rdi, [rax + rdx*8]  ;bucket[index]
    
    ;Поиск в цепочке
.search_loop:
    test rdi, rdi
    jz .not_found
    
    ;Сравниваем строки
    mov rsi, [rdi]      ;node->key
    mov rdx, r13        ;key

.strcmp_loop:
    mov al, [rsi]
    test al, al
    jz .check_end

    cmp al, [rdx]
    jne .next_node

    inc rsi
    inc rdx
    jmp .strcmp_loop

.check_end:
    cmp byte [rdx], 0
    jne .next_node
    
    ;Нашли совпадение
    mov rax, [rdi + 8] ;node->value
    jmp .end
    
.next_node:
    mov rdi, [rdi + 16] ;node->next
    jmp .search_loop
    
.not_found:
    xor eax, eax        ;Возвращаем NOTFOUND (он же нуль, он же ноль, он же нолик, он не антисимка)
    
.end:
    pop r14
    pop r13
    pop r12
ret