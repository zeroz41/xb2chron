#ifndef CLASSES_SSD_STREAMBUFFER_H
#define CLASSES_SSD_STREAMBUFFER_H

#include "ssd/Debug.h"
#include "classes/ssd/Allocator.h"

namespace ssd {
// table 0x7100B82380: a ring buffer streamed audio data is written into (InData*) and read out of (OutData*), in
// 8- to 64-bit units (D:/ssd/ssd51/ssd/sources/stream_buffer.cpp). The getters return 64 bits: InData* compare
// GetFreeSize() with x registers. The field names are not the original's.
class StreamBuffer {
public:
    StreamBuffer() : allocator_(nullptr), buffer_(nullptr), loopPosition_(0) {}
    // not virtual (the table holds no destructor); StreamController's destructor stores the vptr and calls Free
    ~StreamBuffer() { Free(); }

    virtual unsigned long GetBufferSize() const;  // slot 0
    virtual unsigned long GetDataSize() const;  // slot 1
    virtual unsigned long GetFreeSize() const;  // slot 2

    // Alloc and Free return a 32-bit code (w0): Alloc -8 when the stream block cannot be had
    int Alloc(unsigned long size, Allocator* allocator);
    void Clear();
    int Free();
    Result InData8(const void* data, unsigned long size, bool loop);
    Result InData16(const void* data, unsigned long size, bool loop);
    Result InData32(const void* data, unsigned long size, bool loop);
    Result InData64(const void* data, unsigned long size, bool loop);
    Result OutData8(void* data, unsigned long size, unsigned long* outSize, bool* end);
    Result OutData16(void* data, unsigned long size, unsigned long* outSize, bool* end);
    Result OutData64(void* data, unsigned long size, unsigned long* outSize, bool* end);

    Allocator* allocator_;
    unsigned char* buffer_;
    unsigned int bufferSize_;
    unsigned int dataSize_;
    // the write and read positions (Clear zeroes them with the data size)
    unsigned int writePosition_;
    unsigned int readPosition_;
    // the write position InData* records when its loop flag is set (the name is not the original's)
    unsigned int loopPosition_;
    // OutData64 limits a read to loopPosition_ while it is set and reports the end once that is used up (the
    // name is not the original's)
    bool loopLimit_;
};
}  // namespace ssd

#endif
