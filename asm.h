//
// Created by hannes on 9/5/18.
//

#ifndef JIT_ASM_H
#define JIT_ASM_H

#include "ByteStream.h"

void ret(ByteStream& code);
void push(ByteStream& code, int reg);
void push(ByteStream& code, uint32_t value);
void pop(ByteStream& code, int reg);

/**
 * Add the provided integer constant to register 0 (EAX).
 */
void add32_const(ByteStream& code, int value);
void add32reg_const(ByteStream& code, int reg, unsigned int value);
void add64reg_const(ByteStream& code, int reg, int32_t value);
void add32mem_const(ByteStream& code, int addressRegister, unsigned int value);
void add8mem_const(ByteStream& code, int addressRegister, int8_t value);
void add32reg_reg(ByteStream& code, int dstReg, int srcReg);
void mov32reg_const(ByteStream& code, int reg, int value);
void mov64reg_const(ByteStream& code, int reg, uint64_t value);
void mov32reg_stack(ByteStream& code, int dst, uint8_t displacement);
void mov8reg_mem(ByteStream& code, int dst, int srcAddress);
void mov32reg_mem(ByteStream& code, int dst, int srcAddress);
void mov32reg_reg(ByteStream& code, int dstReg, int srcReg);
void mov64reg_reg(ByteStream& code, int dstReg, int srcReg);
void interrupt(ByteStream& code, uint8_t vector);
void syscall(ByteStream& code);
void jmp32_const(ByteStream& code, int32_t diff);
void jmp8_const(ByteStream& code, int8_t diff);
int32_t* jz32_const(ByteStream& code);
void jz8_const(ByteStream& code, int8_t diff);
void test8mem_const(ByteStream& code, uint8_t memReg, uint8_t value);

#endif //JIT_ASM_H
