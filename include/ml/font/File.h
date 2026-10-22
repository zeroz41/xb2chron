#ifndef ML_FONT_FILE_H
#define ML_FONT_FILE_H

// monolib's reader over a block of memory (1.0.0's File::*, placed after WriteStr and the vmMl* functions).
// The field names are not the original's: they are named from what File's accessors do with them.
class File {
public:
    File();
    File(void* data, unsigned long size);
    ~File();

    unsigned char read_byte();
    unsigned short read_le16();
    unsigned int read_le32();
    // the read position
    unsigned long pos();
    // moves the read position; always returns 0
    unsigned long pos(unsigned long pos);
    bool is_eof();

    void* m_data;         // 0x00 the block read from (null once destroyed)
    int m_err;            // 0x08 1 when constructed over a block, 0 over none (err() returns it)
    unsigned long m_pos;  // 0x10 the read position
    unsigned long m_size; // 0x18 the block's size (size() returns it)
};

#endif
