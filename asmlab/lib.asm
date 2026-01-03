
global strClone
global strPrint
global strCmp
global strLen
global strDelete

global arrayNew
global arrayDelete
global arrayPrint
global arrayGetSize
global arrayAddLast
global arrayGet
global arrayRemove
global arraySwap

global cardCmp
global cardClone
global cardAddStacked
global cardDelete
global cardGetSuit
global cardGetNumber
global cardGetStacked
global cardPrint
global cardNew

extern malloc
extern free
extern fprintf
extern getCloneFunction
extern getDeleteFunction
extern getPrintFunction
extern intCmp
extern strPrint
extern listPrint
extern listClone
extern intClone
extern listNew
extern listDelete
extern listAddFirst
extern intPrint

%define OFFSET_ARRAY_TYPE 0
%define OFFSET_ARRAY_SIZE 4
%define OFFSET_ARRAY_CAPACITY 5
%define OFFSET_ARRAY_DATA 8

%define OFFSET_CARD_SUIT 0
%define OFFSET_CARD_NUMBER 8
%define OFFSET_CARD_STACKED 16

%define OFFSET_LIST_FIRST 8
%define OFFSET_LIST_ELEM_NEXT 8
%define OFFSET_LIST_ELEM_PREV 16
%define OFFSET_LIST_SIZE 4

%define TYPE_INT 1
%define TYPE_STR 2
section .data
TEXT_NULL: db "NULL", 0
TEXT: db "%s", 0
TEXT_LLAVE_ABRE: db '{', 0
TEXT_LLAVE_CIERRA: db '}', 0
TEXT_CORCHETE_ABRE: db '[', 0
TEXT_CORCHETE_CIERRA: db ']', 0
TEXT_COMA: db ',', 0
TEXT_GUION: db '-', 0

section .text

; ** String **
;char* strClone(char* a);
strClone:
    push rbp
    mov rbp, rsp
    push r12
    push r13

    mov r12, 0

    .counter:
    mov dl, [rdi + r12]
    inc r12
    cmp dl, 0
    jne .counter

    mov r13, rdi
    mov rdi, r12
    call malloc

    mov r12, 0
    .clone:
    mov dl, [r13 + r12]
    mov [rax + r12], dl
    inc r12
    cmp dl, 0
    jne .clone

    pop r13
    pop r12
    pop rbp 
ret

;void strPrint(char* a, FILE* pFile) ; rdi = a, rsi = pFile
strPrint:
    .prologo:
    push rbp
    mov rbp, rsp
    push r12
    push r13
    mov r12, rdi 
    mov r13, rsi

    .string_vacio:
    cmp byte [r12], 0
    je .print_string_vacio
    jmp .print_string

    .print_string_vacio:
    mov rdi, r13
    mov rsi, TEXT_NULL
    mov al, 0
    call fprintf
    jmp .epilogo

    .print_string:
    mov rdi, r13
    mov rsi, TEXT
    mov rdx, r12
    mov al, 0
    call fprintf
    jmp .epilogo

    .epilogo:
    pop r13
    pop r12
    pop rbp
    ret

;uint32_t strLen(char* a);
strLen:
    push rbp
    mov rbp, rsp

    mov rax, 0
    .loop:
        mov dl, [rdi + rax]
        inc rax
        cmp dl, 0
        jne .loop
        dec rax
    .fin:
        pop rbp
        ret

;int32_t strCmp(char* a, char* b);
strCmp:
    push rbp
    mov rbp, rsp
    push r12

    mov r12, 0
    .loop:
    mov al, [rdi + r12]
    mov bl, [rsi + r12]

    cmp al, 0
    jne .check_b
    cmp bl,0
    je .iguales
    jmp .menor

    .check_b:
    cmp bl, 0
    jne .compare
    jmp .mayor

    .compare:
    cmp al, bl
    je .next_char
    ja .mayor
    jb .menor

    .next_char:
    inc r12
    jmp .loop

    .iguales:
    mov rax, 0
    jmp .fin

    .menor:
    mov rax, 1
    jmp .fin

    .mayor:
    mov rax, -1
    jmp .fin

    ;epilogo
    .fin:
    pop r12
    pop rbp
ret

;void strDelete(char* a);
strDelete:
    push rbp
    mov rbp, rsp

    call free

    pop rbp
    ret
; ** Array **

; uint8_t arrayGetSize(array_t* a)
arrayGetSize:
    push rbp
    mov rbp, rsp

    mov al, [rdi + OFFSET_ARRAY_SIZE]

    pop rbp
    ret

; void arrayAddLast(array_t* a, void* data)
arrayAddLast:
    push rbp
    mov rbp, rsp
    movzx eax, byte [rdi + OFFSET_ARRAY_SIZE]
    movzx ecx, byte [rdi + OFFSET_ARRAY_CAPACITY]
    cmp eax, ecx
    jge .fin

    push rbx
    push r12
    push r13
    sub rsp, 8

    mov r12, rdi
    mov rbx, [r12 + OFFSET_ARRAY_DATA]
    mov edx, [r12]
    mov edi, edx
    call getCloneFunction
    test rax, rax
    jz .restore
    mov r13, rax
    mov rdi, rsi 
    call r13
    test rax, rax
    jz .restore
    movzx r8d, byte [r12 + OFFSET_ARRAY_SIZE]
    mov [rbx + r8 * 8], rax
    inc byte [r12 + OFFSET_ARRAY_SIZE]

    .restore:
        add rsp, 8
        pop r13
        pop r12
        pop rbx

    .fin:
        pop rbp
        ret

; void* arrayGet(array_t* a, uint8_t i)
arrayGet:
    push rbp
    mov rbp, rsp

    cmp sil, [rdi + OFFSET_ARRAY_SIZE]
    jb .get_element
    jmp .not_get

    .get_element:
    mov rax, [rdi + OFFSET_ARRAY_DATA]
    mov rax, [rax + rsi*OFFSET_ARRAY_DATA]
    jmp .fin

    .not_get:
    mov rax, 0
    jmp .fin

    ;epilogo
    .fin:
    pop rbp
ret

; array_t* arrayNew(type_t t, uint8_t capacity)
arrayNew:
    push rbp
    mov rbp, rsp
    push rbx
    push r12
    push r13
    push r14

    mov r12b, sil
    mov r14d, edi

    mov edi, 16
    call malloc
    mov rbx, rax

    movzx eax, r12b
    shl rax, 3
    mov rdi, rax
    call malloc
    mov r13, rax
    mov dword [rbx + OFFSET_ARRAY_TYPE], r14d
    mov byte [rbx + OFFSET_ARRAY_SIZE], 0
    mov byte [rbx + OFFSET_ARRAY_CAPACITY], r12b
    mov [rbx + OFFSET_ARRAY_DATA], r13
    mov rax, rbx

    pop r14
    pop r13
    pop r12
    pop rbx
    pop rbp
    ret

; void* arrayRemove(array_t* a, uint8_t i)
arrayRemove:
    push rbp
    mov rbp, rsp
    push r12
    mov r12, 0 

    cmp sil, [rdi + OFFSET_ARRAY_SIZE]
    jb .L1
    jmp .not_remove

    .L1:
    mov rdx, [rdi + OFFSET_ARRAY_DATA]
    mov rdx, [rdx + rsi*8]
    dec byte [rdi + OFFSET_ARRAY_SIZE]
    je .remove_element
    mov r12, rsi
    jmp .loop 

    .remove_element:
    mov rax, rdx
    jmp .fin
    
    .loop:
    cmp r12b, [rdi + OFFSET_ARRAY_SIZE]
    je .remove_element
    mov rbx, [rdi + OFFSET_ARRAY_DATA]
    mov rcx, [rbx + r12*8 + 8] 
    mov [rbx + r12*8], rcx
    inc r12b
    jmp .loop

    .not_remove:
    mov rax, 0
    jmp .fin

    .fin:
    pop r12
    pop rbp
ret

; void arraySwap(array_t* a, uint8_t i, uint8_t j)
arraySwap:
    push rbp
    mov rbp, rsp

    cmp sil, [rdi + OFFSET_ARRAY_SIZE]
    jge .epilogo
    cmp dl, [rdi + OFFSET_ARRAY_SIZE]
    jge .epilogo

    mov rbx, [rdi + OFFSET_ARRAY_DATA]

    .swap:
    mov rax, [rbx + rsi * 8]
    mov rcx, [rbx + rdx * 8]
    mov [rbx + rsi * 8], rcx
    mov [rbx + rdx * 8], rax

    .epilogo:
    pop rbp
    ret

; void arrayDelete(array_t* a) {
arrayDelete:
    push rbp
    mov rbp, rsp
    push rbx
    push r12
    push r13
    push r14
    mov rbx, rdi

    mov eax, [rbx + OFFSET_ARRAY_TYPE]
    mov edi, eax
    call getDeleteFunction
    mov r12, rax

    movzx ecx, byte [rbx + OFFSET_ARRAY_SIZE]
    mov r13, [rbx + OFFSET_ARRAY_DATA]
    test ecx, ecx
    jz .fin

    mov r14d, ecx
    dec r14d

    .loop:
    cmp r14d, 0
    jl .fin
    mov rdi, [r13 + r14 * 8]
    call r12
    dec r14d
    jmp .loop

    .fin:
    mov rdi, r13
    call free
    mov rdi, rbx
    call free

    pop r14
    pop r13
    pop r12
    pop rbx
    pop rbp
ret

;void arrayPrint(array_t* a, FILE* pFile)
arrayPrint:
    push rbp 
    mov rbp, rsp
    push r12
    push r13
    push r14
    push r15 
    push rbx
    sub rsp, 8
    mov r12, rdi
    mov r13, rsi
    mov r14, 0 

    mov rdi, [rdi]
    call getPrintFunction 
    mov r15, rax

    mov rdx, TEXT_CORCHETE_ABRE 
    mov rdi, rdx 
    mov rsi, r13 
    call strPrint

    cmp byte [r12 + OFFSET_ARRAY_SIZE], 0
    je .end_print

    .loop:
    cmp r14b, [r12 + OFFSET_ARRAY_SIZE] 
    je .end_print 
    mov rcx, [r12 + OFFSET_ARRAY_DATA]
    mov rbx, [rcx + r14*OFFSET_ARRAY_DATA] 
    mov rdi, rbx
    mov rsi, r13
    call r15 

    inc r14
    cmp r14b, [r12 + OFFSET_ARRAY_SIZE]
    je .skip_coma
     
    mov rdx, TEXT_COMA 
    mov rdi, rdx 
    mov rsi, r13 
    call strPrint 

    .skip_coma:
    jmp .loop

    .end_print:
    mov rdx, TEXT_CORCHETE_CIERRA
    mov rdi, rdx  
    mov rsi, r13 
    call strPrint 

    .fin:
    add rsp, 8
    pop rbx
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbp
ret

; ** Card **

; card_t* cardNew(char* suit, int32_t* number)
cardNew:
    .prologo:
    push rbp
    mov rbp, rsp
    push r12
    push r13
    push r14
    sub rsp, 8
    mov r12, rdi
    mov r13, rsi

    .copiar_suit:
    call strClone
    mov r12, rax 

    .copiar_number:
    mov rdi, r13 
    call intClone
    mov r13, rax

    .crear_stacked:
    mov rdi, 3 
    call listNew
    mov r14, rax

    .crear_card:
    mov rdi, 24
    call malloc
    mov [rax + OFFSET_CARD_SUIT], r12
    mov [rax + OFFSET_CARD_NUMBER], r13
    mov [rax + OFFSET_CARD_STACKED], r14

    .epilogo:
    add rsp, 8
    pop r14
    pop r13
    pop r12
    pop rbp
ret

;char* cardGetSuit(card_t* c)
cardGetSuit:
    mov rax, [rdi]
    ret

;int32_t* cardGetNumber(card_t* c)
cardGetNumber:
    push rbp
    mov rbp, rsp

    mov rax, [rdi + OFFSET_CARD_NUMBER]

    .fin:
    pop rbp
ret

;list_t* cardGetStacked(card_t* c)
cardGetStacked:
    push rbp
    mov rbp, rsp

    mov rax, [rdi + OFFSET_CARD_STACKED]

    pop rbp
    ret

;void cardPrint(card_t* c, FILE* pFile)
cardPrint:
    push rbp
    mov rbp, rsp
    push r12
    push r13
    push r14
    sub rsp, 8
    mov r12, rdi
    mov r13, rsi

    mov rdi, TEXT_LLAVE_ABRE 
    mov rsi, r13
    call strPrint

    mov rdi, [r12 + OFFSET_CARD_SUIT]
    mov rsi, r13
    call strPrint
    
    mov rdi, TEXT_GUION
    mov rsi, r13
    call strPrint 

    mov rdi, [r12 + 8]
    mov rsi, r13
    call intPrint

    mov rdi, TEXT_GUION
    mov rsi, r13
    call strPrint

    mov rdi, [r12 + OFFSET_CARD_STACKED]
    mov rsi, r13
    call listPrint

    mov rdi, TEXT_LLAVE_CIERRA
    mov rsi, r13
    call strPrint

    add rsp, 8
    pop r14
    pop r13
    pop r12
    pop rbp
    ret
    
;int32_t cardCmp(card_t* a, card_t* b)
cardCmp:
    .prologo:
    push rbp
    mov rbp, rsp
    sub rsp, 8
    push rbx
    push r12
    push r13
    mov r12, rdi
    mov r13, rsi

    .cmp_suit:
    mov rdi, [r12 + OFFSET_CARD_SUIT]
    mov rsi, [r13 + OFFSET_CARD_SUIT]
    call strCmp
    mov ebx, eax
    cmp ebx, 0
    je .cmp_number 
    jge .b_es_mayor 
    jmp .a_es_mayor 

    .cmp_number:
    mov rdi, [r12 + OFFSET_CARD_NUMBER] 
    mov rsi, [r13 + OFFSET_CARD_NUMBER] 
    call intCmp
    mov ebx, eax
    cmp ebx, 0
    je .a_igual_b
    jge .b_es_mayor
    jmp .a_es_mayor

    .b_es_mayor:
    mov eax, 1
    jmp .epilogo

    .a_es_mayor:
    mov eax, -1
    jmp .epilogo

    .a_igual_b:
    mov eax, 0
    jmp .epilogo

    .epilogo:
    pop r13
    pop r12
    pop rbx
    add rsp, 8
    pop rbp
    ret

;card_t* cardClone(card_t* c)
cardClone:
    push rbp
    mov rbp, rsp
    push rbx
    push r12

    mov rbx, rdi
    mov rdi, 24
    call malloc
    mov r12, rax

    mov rdi, [rbx]
    call strClone
    mov [r12], rax

    mov rdi, [rbx + OFFSET_CARD_NUMBER]
    call intClone
    mov [r12 + OFFSET_CARD_NUMBER], rax

    mov rdi, [rbx + OFFSET_CARD_STACKED]
    call listClone
    mov [r12 + OFFSET_CARD_STACKED], rax

    mov rax, r12

    pop r12
    pop rbx
    pop rbp
    ret

;void cardAddStacked(card_t* c, card_t* card)
cardAddStacked:
    push rbp
    mov rbp, rsp
    push r12
    push r13
    
    mov r12, rdi 
    mov r13, rsi 

    mov rdi, [r12 + OFFSET_CARD_STACKED] 
    mov rsi, r13
    call listAddFirst

    .fin:
    pop r13
    pop r12
    pop rbp
ret

;void cardDelete(card_t* c)
cardDelete:
    push rbp 
    mov rbp, rsp
    push r12 
    sub rsp, 8 

    mov r12, rdi 

    mov rdi, [r12 + OFFSET_CARD_STACKED] 
    call listDelete

    mov rdi, TYPE_INT 
    call getDeleteFunction
    mov rdi, [r12 + OFFSET_CARD_NUMBER] 
    call rax 

    mov rdi, TYPE_STR
    call getDeleteFunction 
    mov rdi, [r12] 
    call rax 

    mov rdi, r12 
    call free 

    .fin:
    add rsp, 8
    pop r12
    pop rbp
ret




