//
// Created by Hannes Widmoser on 17.08.18.
//

#ifndef ASM_H
#define ASM_H

#include "ByteStream.h"

void ret(ByteStream& code) {
    code.appendInt8(0xc3);
}

void push(ByteStream& code, int reg) {
    code.appendInt8(0x50 | reg);
}

void pop(ByteStream& code, int reg) {
    code.appendInt8(0x58 | reg);
}

/**
 * Add the provided integer constant to register 0 (EAX).
 */
void add32_const(ByteStream& code, int value) {
    code.appendInt8(0x05);
    code.appendInt32(value);
}

void add32reg_const(ByteStream& code, int reg, int value) {
    code.appendInt8(0x81);
    code.appendInt8(0xC0 | reg); // 11000rrr
    code.appendInt32(value);
}

void add32mem_const(ByteStream& code, int reg, int value) {
    code.appendInt8(0x81);
    code.appendInt8(reg); // 00000rrr
    code.appendInt32(value);
}

void add32reg_reg(ByteStream& code, int dstReg, int srcReg) {
    code.appendInt8(0x03);
    code.appendInt8(0xC0 | (dstReg << 3) | srcReg); // 11dddsss
}

void mov32reg_const(ByteStream& code, int reg, int value) {
    code.appendInt8(0xB8 | reg);
    code.appendInt32(value);
}

#endif