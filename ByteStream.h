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

    ByteStream& appendUInt8(uint8_t byte);
    ByteStream& appendInt8(int8_t byte);
    ByteStream& appendUInt16(uint16_t word);
    ByteStream& appendUInt32(uint32_t dword);
    ByteStream& appendInt32(int32_t dword);
    int32_t* int32Placeholder(int32_t defaultValue);
    ByteStream& appendUInt64(uint64_t qword);

    const uint8_t* data_ptr() const;
    unsigned long size() const;
};

#endif //JIT_BYTESTREAM_H
