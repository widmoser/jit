//
// Created by Hannes Widmoser on 17.08.18.
//

#ifndef ASM_H
#define ASM_H

#include "ByteStream.h"

const int STACK_PTR_REGISTER = 4;

void ret(ByteStream& code) {
    code.appendUInt8(0xc3);
}

void push(ByteStream& code, int reg) {
    code.appendUInt8(0x50 | reg);
}

void push(ByteStream& code, uint32_t value) {
    code.appendUInt8(0x68);
    code.appendUInt32(value);
}

void pop(ByteStream& code, int reg) {
    code.appendUInt8(0x58 | reg);
}

/**
 * Add the provided integer constant to register 0 (EAX).
 */
void add32_const(ByteStream& code, int value) {
    code.appendUInt8(0x05);
    code.appendUInt32(value);
}

void add32reg_const(ByteStream& code, int reg, unsigned int value) {
    code.appendUInt8(0x81);
    code.appendUInt8(0xC0 | reg); // 11000rrr
    code.appendUInt32(value);
}

void add64reg_const(ByteStream& code, int reg, int32_t value) {
    code.appendUInt8(0x48);
    code.appendUInt8(0x81);
    code.appendUInt8(0xC0 | reg); // 11000rrr
    code.appendInt32(value);
}

void add32mem_const(ByteStream& code, int addressRegister, unsigned int value) {
    code.appendUInt8(0x81);
    code.appendUInt8(addressRegister); // 00000rrr
    code.appendUInt32(value);
}

void add8mem_const(ByteStream& code, int addressRegister, int8_t value) {
    code.appendUInt8(0x80);
    code.appendUInt8(addressRegister); // 00000rrr
    code.appendInt8(value);
}

void add32reg_reg(ByteStream& code, int dstReg, int srcReg) {
    code.appendUInt8(0x03);
    code.appendUInt8(0xC0 | (dstReg << 3) | srcReg); // 11dddsss
}

void mov32reg_const(ByteStream& code, int reg, int value) {
    code.appendUInt8(0xB8 | reg);
    code.appendUInt32(value);
}

void mov64reg_const(ByteStream& code, int reg, uint64_t value) {
    code.appendUInt8(0x48);
    code.appendUInt8(0xB8 | reg);
    code.appendUInt64(value);
}

void mov32reg_stack(ByteStream& code, int dst, uint8_t displacement) {
//    code.appendUInt8(0x67);
    code.appendUInt8(0x8B);
    code.appendUInt8(0x44 | (dst << 3)); // 00rrr100
    code.appendUInt8(0x24);
    code.appendUInt8(displacement);
}

void mov8reg_mem(ByteStream& code, int dst, int srcAddress) {
    code.appendUInt8(0x8A);
    code.appendUInt8((dst << 3) | srcAddress); // 00rrr100
//    code.appendUInt8(0x24);
}

void mov32reg_mem(ByteStream& code, int dst, int srcAddress) {
    code.appendUInt8(0x8B);
    code.appendUInt8((dst << 3) | srcAddress); // 00rrr100
//    code.appendUInt8(0x24);
}

void mov32reg_reg(ByteStream& code, int dstReg, int srcReg) {
    code.appendUInt8(0x8B);
    code.appendUInt8(0xC0 | (dstReg << 3) | srcReg); // 11dddsss
}

void mov64reg_reg(ByteStream& code, int dstReg, int srcReg) {
    code.appendUInt8(0x48);
    code.appendUInt8(0x8B);
    code.appendUInt8(0xC0 | (dstReg << 3) | srcReg); // 11dddsss

}

void interrupt(ByteStream& code, uint8_t vector) {
    code.appendUInt8(0xCD);
    code.appendUInt8(vector);
}

void syscall(ByteStream& code) {
    code.appendUInt8(0x0F);
    code.appendUInt8(0x05);
}

void jmp32_const(ByteStream& code, int32_t diff) {
    code.appendUInt8(0xE9);
    code.appendInt32(diff);
}

void jmp8_const(ByteStream& code, int8_t diff) {
    code.appendUInt8(0xEB);
    code.appendInt8(diff);
}

int32_t* jz32_const(ByteStream& code) {
    code.appendUInt8(0x0F);
    code.appendUInt8(0x84);
    return code.int32Placeholder((int32_t)code.size() - 2);
}

void jz8_const(ByteStream& code, int8_t diff) {
    code.appendUInt8(0x74);
    code.appendInt8(diff);
}

void test8mem_const(ByteStream& code, uint8_t memReg, uint8_t value) {
    code.appendUInt8(0xF6);
    code.appendUInt8(memReg); // 00000rrr
    code.appendUInt8(value);
}

#endif