#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <iostream>
#include <stack>
#include <fstream>

#include "ByteStream.h"
#include "asm.h"

const int DATA_PTR = 3;

void compile(std::istream& input, ByteStream& code) {
    std::stack<int32_t*> jumpSlots;
    mov64reg_reg(code, DATA_PTR, 7);
    while (!input.eof()) {
        int ch = input.get();
        switch (ch) {
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
//              OSX: mov64reg_const(code, 0, 0x2000004);
                mov64reg_const(code, 0, 0x01);
                mov64reg_const(code, 7, 1);
                mov64reg_reg(code, 6, DATA_PTR);
                mov64reg_const(code, 2, 1);
                syscall(code);
                break;
            case ',':
//              OSX: mov64reg_const(code, 0, 0x2000003);
                mov64reg_const(code, 0, 0x00);
                mov64reg_const(code, 7, 0);
                mov64reg_reg(code, 6, DATA_PTR);
                mov64reg_const(code, 2, 1);
                syscall(code);
                break;
            case '[':
                test8mem_const(code, DATA_PTR, 0xFF);
                jumpSlots.push(jz32_const(code));
                break;
            case ']':
                int32_t* jmpLocationPtr = jumpSlots.top();
                int32_t jmpDiff = code.size() - *jmpLocationPtr;
                jmp32_const(code, -(jmpDiff + 6 + 5 + 3));
                *jmpLocationPtr = code.size() - *jmpLocationPtr;
                jumpSlots.pop();
                break;
        }
    }
    mov64reg_reg(code, 0, DATA_PTR);
    ret(code);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: jit1 <program>\n");
        return 1;
    }

    std::ifstream input(argv[1]);

    auto* memory = new char[3000000];

    ByteStream code;
    compile(input, code);

    // Allocate writable/executable memory.
    // Note: real programs should not map memory both writable
    // and executable because it is a security risk.
    void *mem = mmap(nullptr, code.size(), PROT_WRITE | PROT_EXEC,
                     MAP_ANON | MAP_PRIVATE, -1, 0);
    memcpy(mem, code.data_ptr(), code.size());

    // The function will return the user's value.
    auto func = reinterpret_cast<long (*)(void*)>(mem);

    func(memory);

    return 0;
}