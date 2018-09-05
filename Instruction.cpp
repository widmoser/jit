//
// Created by hannes on 9/5/18.
//

#include "Instruction.h"
#include "asm.h"

const int DATA_PTR = 3;

ByteStream measurementStream(32);

unsigned long Instruction::size() {
    measurementStream.startMeasuringSize();
    write(measurementStream);
    return measurementStream.endMeasuringSize();
}

void Add::write(ByteStream &code) {
    add8mem_const(code, DATA_PTR, value);
}
