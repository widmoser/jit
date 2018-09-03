#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <iostream>
#include <vector>

#include "ByteStream.h"
#include "asm.h"

const int DATA_PTR = 3;

void compile(const char* program, size_t len, ByteStream& code) {
    int index = 0;
    const char* ptr = program;
    std::vector<int32_t*> jumpSlots;
    mov64reg_reg(code, DATA_PTR, 7);
    while (index++ < len) {
        switch (*ptr) {
            case '>':
                add64reg_const(code, DATA_PTR, 1);
                break;
            case '<':
                add64reg_const(code, DATA_PTR, -1);
                break;
            case '+':
                add8mem_const(code, DATA_PTR, 1);
                break;
            case '-':
                add8mem_const(code, DATA_PTR, -1);
                break;
            case '.':
                mov64reg_const(code, 0, 0x2000004);
                mov64reg_const(code, 7, 1);
                mov64reg_reg(code, 6, DATA_PTR);
                mov64reg_const(code, 2, 1);
                syscall(code);
                break;
            case ',':
                mov64reg_const(code, 0, 0x2000003);
                mov64reg_const(code, 7, 0);
                mov64reg_reg(code, 6, DATA_PTR);
                mov64reg_const(code, 2, 1);
                syscall(code);
                break;
            case '[':
                test8mem_const(code, DATA_PTR, 0xFF);
                jumpSlots.push_back(jz32_const(code));
            case ']':
                int32_t* jmpLocationPtr = *jumpSlots.end();
                int32_t jmpDiff = code.size() - *jmpLocationPtr;
                jmp32_const(code, jmpDiff);
                *jmpLocationPtr = code.size() - *jmpLocationPtr;
        }
        ptr++;
    }
    mov64reg_reg(code, 0, DATA_PTR);
    ret(code);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: jit1 <program>\n");
        return 1;
    }

    char* program = argv[1];
    size_t len = strlen(program);


    auto* memory = new char[4096];
    memory[0] = 0;

    std::cout << std::hex << (long)memory << std::endl;

    ByteStream code;
    compile(program, len, code);
    // Reg 7 contains data pointer
//    push(code, 12);
//    push(code, 7);

//    test8mem_const(code, 7, 0xFF);
//    jz8_const(code, 12);
//    mov32reg_const(code, 0, 1);
//    ret(code);
//    mov32reg_const(code, 0, 2);
//    ret(code);
//    mov32reg_const(code, 0, 3);
//    ret(code);

    // WRITE
//    mov64reg_const(code, 0, 0x2000004);
//    mov64reg_const(code, 7, 1);
//    mov64reg_const(code, 6, (uint64_t)memory);
//    mov64reg_const(code, 2, 12);
//    syscall(code);

    // READ
//    mov64reg_const(code, 0, 0x2000003);
//    mov64reg_const(code, 7, 0);
//    mov64reg_const(code, 6, (uint64_t)memory);
//    mov64reg_const(code, 2, 1);
//    syscall(code);

//    mov8reg_mem(code, 0, 6);

//    add64reg_const(code, 7, 2);
//    add64reg_const(code, 7, -1);
//    add32mem_const(code, 7, -1);
//    mov64reg_reg(code, 0, 7);
//    mov8reg_mem(code, 0, 7);
//    mov32reg_mem(code, 0, 7);
//    mov32reg_stack(code, 0, 0);
//    mov32reg_stack(code, 1, 4);
//    add32reg_reg(code, 0, 7);
//    ret(code);

    // Allocate writable/executable memory.
    // Note: real programs should not map memory both writable
    // and executable because it is a security risk.
    void *mem = mmap(nullptr, code.size(), PROT_WRITE | PROT_EXEC,
                     MAP_ANON | MAP_PRIVATE, -1, 0);
    memcpy(mem, code.data_ptr(), code.size());

    // The function will return the user's value.
    long (*func)(void*) = reinterpret_cast<long (*)(void*)>(mem);

    auto res = func(memory);
    std::cout << std::endl << std::hex << res << std::endl;
    return 0;
}