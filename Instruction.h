//
// Created by hannes on 9/5/18.
//

#ifndef JIT_INSTRUCTION_H
#define JIT_INSTRUCTION_H


#include "ByteStream.h"

class Instruction {
public:
    virtual void write(ByteStream& code) = 0;
    unsigned long size();
};

class Add : public Instruction {
public:
    void write(ByteStream& code) override;
private:
    int8_t value;
};

#endif //JIT_INSTRUCTION_H
