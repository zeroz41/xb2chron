#ifndef CLASSES_SSD_MEMORYSTREAM_H
#define CLASSES_SSD_MEMORYSTREAM_H

#include "classes/ssd/IoStreamBase.h"

namespace ssd {
// table 0x7100B82198: a stream over memory (D:/ssd/ssd51/ssd/sources/io/memory_stream.cpp). Its destructor is
// trivial: the table's complete-object slot holds Object's.
class MemoryStream : public ::ssd::IoStreamBase {
public:
    // 1.0.0 has it out of line; 3.0.1 keeps no copy (WaveSource::Init constructs one inline, type 12)
    MemoryStream() : IoStreamBase(ObjectType::Id(12)), data_(nullptr), size_(0) {}
    virtual ~MemoryStream() {}  // slot 0
    virtual bool IsOpen() const;  // slot 2
    virtual Result Open(void* data, unsigned long size, OpenMode mode);  // slot 4
    virtual Result Close();  // slot 5
    virtual Result GetSize(unsigned long* fileSize) const;  // slot 6
    virtual Result Read(unsigned long size, void* buffer, unsigned long* readSize);  // slot 7
    virtual Result Write(unsigned long size, const void* buffer, unsigned long* writeSize);  // slot 8
    virtual Result Seek(SeekMode mode, unsigned long offset, unsigned long* position);  // slot 9
    virtual Result GetPosition(unsigned long* position) const;  // slot 10
    virtual Result Tell(unsigned long* position);  // slot 11
    virtual unsigned long CheckAccessSize(unsigned long size);  // slot 12

    // the memory, its size (Open) and the read position (the names are not the original's)
    void* data_;
    unsigned long size_;
    unsigned long position_;
};
}  // namespace ssd

#endif
