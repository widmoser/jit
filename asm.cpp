#include "asm.h"

void ret(ByteStream& code) {
    code.append<uint8_t>(0xc3);
}

void push(ByteStream& code, int reg) {
    code.append<uint8_t>(0x50 | reg);
}

void push(ByteStream& code, uint32_t value) {
    code.append<uint8_t>(0x68);
    code.append<uint32_t>(value);
}

void pop(ByteStream& code, int reg) {
    code.append<uint8_t>(0x58 | reg);
}

/**
 * Add the provided integer constant to register 0 (EAX).
 */
void add32_const(ByteStream& code, int value) {
    code.append<uint8_t>(0x05);
    code.append<uint32_t>(value);
}

void add32reg_const(ByteStream& code, int reg, unsigned int value) {
    code.append<uint8_t>(0x81);
    code.append<uint8_t>(0xC0 | reg); // 11000rrr
    code.append<uint32_t>(value);
}

void add64reg_const(ByteStream& code, int reg, int32_t value) {
    code.append<uint8_t>(0x48);
    code.append<uint8_t>(0x81);
    code.append<uint8_t>(0xC0 | reg); // 11000rrr
    code.append<int32_t>(value);
}

void add32mem_const(ByteStream& code, int addressRegister, unsigned int value) {
    code.append<uint8_t>(0x81);
    code.append<uint8_t>(addressRegister); // 00000rrr
    code.append<uint32_t>(value);
}

void add8mem_const(ByteStream& code, int addressRegister, int8_t value) {
    code.append<uint8_t>(0x80);
    code.append<uint8_t>(addressRegister); // 00000rrr
    code.append<int8_t>(value);
}

void add32reg_reg(ByteStream& code, int dstReg, int srcReg) {
    code.append<uint8_t>(0x03);
    code.append<uint8_t>(0xC0 | (dstReg << 3) | srcReg); // 11dddsss
}

void mov32reg_const(ByteStream& code, int reg, int value) {
    code.append<uint8_t>(0xB8 | reg);
    code.append<uint32_t>(value);
}

void mov64reg_const(ByteStream& code, int reg, uint64_t value) {
    code.append<uint8_t>(0x48);
    code.append<uint8_t>(0xB8 | reg);
    code.append<uint64_t>(value);
}

void mov32reg_stack(ByteStream& code, int dst, uint8_t displacement) {
//    code.append<uint8_t>(0x67);
    code.append<uint8_t>(0x8B);
    code.append<uint8_t>(0x44 | (dst << 3)); // 00rrr100
    code.append<uint8_t>(0x24);
    code.append<uint8_t>(displacement);
}

void mov8reg_mem(ByteStream& code, int dst, int srcAddress) {
    code.append<uint8_t>(0x8A);
    code.append<uint8_t>((dst << 3) | srcAddress); // 00rrr100
//    code.append<uint8_t>(0x24);
}

void mov32reg_mem(ByteStream& code, int dst, int srcAddress) {
    code.append<uint8_t>(0x8B);
    code.append<uint8_t>((dst << 3) | srcAddress); // 00rrr100
//    code.append<uint8_t>(0x24);
}

void mov32reg_reg(ByteStream& code, int dstReg, int srcReg) {
    code.append<uint8_t>(0x8B);
    code.append<uint8_t>(0xC0 | (dstReg << 3) | srcReg); // 11dddsss
}

void mov64reg_reg(ByteStream& code, int dstReg, int srcReg) {
    code.append<uint8_t>(0x48);
    code.append<uint8_t>(0x8B);
    code.append<uint8_t>(0xC0 | (dstReg << 3) | srcReg); // 11dddsss

}

void interrupt(ByteStream& code, uint8_t vector) {
    code.append<uint8_t>(0xCD);
    code.append<uint8_t>(vector);
}

void syscall(ByteStream& code) {
    code.append<uint8_t>(0x0F);
    code.append<uint8_t>(0x05);
}

void jmp32_const(ByteStream& code, int32_t diff) {
    code.append<uint8_t>(0xE9);
    code.append<int32_t>(diff);
}

void jmp8_const(ByteStream& code, int8_t diff) {
    code.append<uint8_t>(0xEB);
    code.append<int8_t>(diff);
}

int32_t* jz32_const(ByteStream& code) {
    code.append<uint8_t>(0x0F);
    code.append<uint8_t>(0x84);
    return code.placeholder<int32_t>((int32_t)code.size() + 4);
}

void jz8_const(ByteStream& code, int8_t diff) {
    code.append<uint8_t>(0x74);
    code.append<int8_t>(diff);
}

void test8mem_const(ByteStream& code, uint8_t memReg, uint8_t value) {
    code.append<uint8_t>(0xF6);
    code.append<uint8_t>(memReg); // 00000rrr
    code.append<uint8_t>(value);
}