//
// Created by Hannes Widmoser on 17.08.18.
//

#include "ByteStream.h"

ByteStream::ByteStream(unsigned int capacity) : capacity(capacity) {
    data = position = new uint8_t[capacity];
}

ByteStream& ByteStream::appendInt8(const uint8_t byte) {
    assertCapacity(sizeof(uint8_t));
    *position = byte;
    position += sizeof(uint8_t);
    return *this;
}

ByteStream& ByteStream::appendInt16(const uint16_t word) {
    assertCapacity(sizeof(uint16_t));
    assertCapacity(2);
    *((uint16_t*)position) = word;
    position += sizeof(uint16_t);
    return *this;
}

ByteStream& ByteStream::appendInt32(const uint32_t dword) {
    assertCapacity(sizeof(uint32_t));
    *((uint32_t*)position) = dword;
    position += sizeof(uint32_t);
    return *this;
}

ByteStream& ByteStream::appendInt64(const uint64_t qword) {
    assertCapacity(sizeof(uint64_t));
    *((uint64_t*)position) = qword;
    position += sizeof(uint64_t);
    return *this;
}

const uint8_t* ByteStream::data_ptr() const {
    return data;
}

unsigned long ByteStream::size() const {
    return position - data;
}

void ByteStream::allocate(unsigned int capacity) {
    delete data;
    data = position = new uint8_t[capacity];
    this->capacity = capacity;
}

void ByteStream::assertCapacity(unsigned int additionalCapacity) {
    if (size() + additionalCapacity > capacity) {
        allocate(capacity*2);
    }
}
