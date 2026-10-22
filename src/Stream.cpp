#include "ml/font/Stream.h"

Stream::Stream(File* file) : m_file(file), m_bits(0), m_bitsLeft(0) {}

Stream::~Stream() {}

unsigned char Stream::read_u8() {
    m_bits = 0;
    m_bitsLeft = 0;
    return m_file->read_byte();
}

unsigned short Stream::read_u16() {
    m_bits = 0;
    m_bitsLeft = 0;
    return m_file->read_le16();
}

unsigned int Stream::read_u32() {
    m_bits = 0;
    m_bitsLeft = 0;
    return m_file->read_le32();
}

unsigned long Stream::pos() {
    return m_file->pos();
}

unsigned long Stream::pos(unsigned long pos) {
    m_bits = 0;
    m_bitsLeft = 0;
    return m_file->pos(pos);
}
