#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <iostream>

#include "ByteStream.h"
#include "asm.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: jit1 <integer>\n");
        return 1;
    }

    // Overwrite immediate value "0" in the instruction
    // with the user's value.  This will make our code:
    //   mov eax, <user's value>
    //   ret
    int num = atoi(argv[1]);

    ByteStream code;
    mov32reg_const(code, 0, num);
    mov32reg_const(code, 1, num);
    add32reg_const(code, 0, 11);
    add32reg_reg(code, 0, 1);
    ret(code);

    // Allocate writable/executable memory.
    // Note: real programs should not map memory both writable
    // and executable because it is a security risk.
    void *mem = mmap(nullptr, code.size(), PROT_WRITE | PROT_EXEC,
                     MAP_ANON | MAP_PRIVATE, -1, 0);
    memcpy(mem, code.data_ptr(), code.size());

    // The function will return the user's value.
    int (*func)() = reinterpret_cast<int (*)()>(mem);

    std::cout << func() << std::endl;
    return 0;
}