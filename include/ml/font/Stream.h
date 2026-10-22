#ifndef ML_FONT_STREAM_H
#define ML_FONT_STREAM_H

#include "ml/font/File.h"

// monolib's bit and byte reader over a File (Stream.cpp). 1.0.0 also had read_bool, read_uint(int),
// read_sint(int), read_fixed, read_float16, read_float, read_double, align, read_s8/s16/s32; 3.0.1's
// linker dropped them.
// The field names are not the original's: read_bool keeps the byte it reads bits from at 0x8 and the
// count of its bits left at 0x9, and every byte-aligned read clears both.
class Stream {
public:
    Stream(File* file);
    ~Stream();

    unsigned char read_u8();
    unsigned short read_u16();
    unsigned int read_u32();
    unsigned long pos();
    unsigned long pos(unsigned long pos);

    File* m_file;                 // 0x0
    unsigned char m_bits;         // 0x8
    unsigned char m_bitsLeft;     // 0x9
};

#endif
