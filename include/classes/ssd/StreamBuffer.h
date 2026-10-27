#ifndef CLASSES_SSD_STREAMBUFFER_H
#define CLASSES_SSD_STREAMBUFFER_H

#include "ssd/Debug.h"

namespace ssd { class Allocator; }

namespace ssd {
// table 0x7100B82380: a ring buffer streamed audio data is written into (InData*) and read out of (OutData*), in
// 8- to 64-bit units. The field names are not the original's.
class StreamBuffer {
public:
    StreamBuffer() : allocator_(nullptr), buffer_(nullptr), pad_28(0) {}

    virtual unsigned int GetBufferSize() const;  // slot 0
    virtual unsigned int GetDataSize() const;  // slot 1
    virtual unsigned int GetFreeSize() const;  // slot 2

    Result Alloc(unsigned long size, Allocator* allocator);
    void Clear();
    void Free();
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
    unsigned int pad_28;
};
}  // namespace ssd

#endif
