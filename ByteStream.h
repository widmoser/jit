//
// Created by Hannes Widmoser on 17.08.18.
//

#ifndef JIT_BYTESTREAM_H
#define JIT_BYTESTREAM_H

#include <cstdint>

class ByteStream {
private:
    unsigned int capacity;
    const uint8_t* data;
    uint8_t* position;

    void assertCapacity(unsigned int additionalCapacity);
    void allocate(unsigned int capacity);
public:
    explicit ByteStream(unsigned int capacity = 4096);

    ByteStream& appendInt8(uint8_t byte);
    ByteStream& appendInt16(uint16_t word);
    ByteStream& appendInt32(uint32_t dword);
    ByteStream& appendInt64(uint64_t qword);

    const uint8_t* data_ptr() const;
    unsigned long size() const;
};

#endif //JIT_BYTESTREAM_H
