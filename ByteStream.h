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

    uint8_t* sizeMeasurementReference;

    void assertCapacity(unsigned int additionalCapacity);
    void allocate(unsigned int capacity);
public:
    explicit ByteStream(unsigned int capacity = 4096);

    template <class T> ByteStream& append(T value) {
        if (sizeMeasurementReference != nullptr) {
            assertCapacity(sizeof(T));
            *((T *) position) = value;
        }
        position += sizeof(T);
        return *this;
    }

    template <class T> T* placeholder(T defaultValue) {
        append(defaultValue);
        return (T*)(position - sizeof(T));
    }

    void startMeasuringSize();
    unsigned long endMeasuringSize();

    const uint8_t* data_ptr() const;
    unsigned long size() const;
};

#endif //JIT_BYTESTREAM_H
