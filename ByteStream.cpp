//
// Created by Hannes Widmoser on 17.08.18.
//

#include "ByteStream.h"

ByteStream::ByteStream(unsigned int capacity) : capacity(capacity), sizeMeasurementReference(nullptr) {
    data = position = new uint8_t[capacity];
}

ByteStream::~ByteStream() {
    delete data;
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

void ByteStream::startMeasuringSize() {
    sizeMeasurementReference = position;
}

unsigned long ByteStream::endMeasuringSize() {
    unsigned long size = position - sizeMeasurementReference;
    position = sizeMeasurementReference;
    return size;
}
