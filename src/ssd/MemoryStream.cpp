#include "nn/os.h"
#include "nn/fs.h"
#include "ssd/Debug.h"
#include "classes/ssd/Allocator.h"
#include "ssd/MemoryBlock.h"
#include "ssd/Hash.h"
#include "ssd/Text.h"
#include "classes/ssd/Object.h"
#include "classes/ssd/TextRef.h"
#include "classes/ssd/IoStreamBase.h"
#include "classes/ssd/FileStream.h"
#include "classes/ssd/MemoryStream.h"
#include "ssd/AudioContents.h"
#include <string.h>

namespace ssd {

bool MemoryStream::IsOpen() const {
    return data_ != nullptr;
}

Result MemoryStream::Open(void* data, unsigned long size, OpenMode mode) {
    if (mode == OpenMode_Read) {
        data_ = data;
        size_ = size;
        position_ = 0;
        return Result(0);
    }
    return Result(-1);
}

Result MemoryStream::Close() {
    data_ = nullptr;
    return Result(0);
}

Result MemoryStream::Read(unsigned long size, void* buffer, unsigned long* readSize) {
    unsigned long read = CheckAccessSize(size);
    if (read != 0) {
        memcpy(buffer, position_ + static_cast<unsigned char*>(data_), read);
        position_ += read;
    }
    if (readSize != nullptr) {
        *readSize = position_;
    }
    return Result(0);
}

Result MemoryStream::Write(unsigned long, const void*, unsigned long*) {
    return Result(-1);
}

Result MemoryStream::Seek(SeekMode mode, unsigned long offset, unsigned long* position) {
    switch (mode) {
    case SeekMode_Current:
        position_ += CheckAccessSize(offset);
        break;
    case SeekMode_Begin:
        position_ = CheckAccessSize(offset);
        break;
    case SeekMode_End: {
        unsigned long size = CheckAccessSize(offset);
        position_ = size_ - size;
        break;
    }
    }
    if (position != nullptr) {
        *position = position_;
    }
    return Result(0);
}

Result MemoryStream::Tell(unsigned long* position) {
    *position = position_;
    return Result(0);
}

Result MemoryStream::GetSize(unsigned long* fileSize) const {
#line 118 "D:/ssd/ssd51/ssd/sources/io/memory_stream.cpp"
    SSD_ASSERT_NOT_NULL(fileSize);
    *fileSize = size_;
    return Result(0);
}

Result MemoryStream::GetPosition(unsigned long* position) const {
    *position = position_;
    return Result(0);
}

unsigned long MemoryStream::CheckAccessSize(unsigned long size) {
    if (!IsOpen()) {
        return 0;
    }
    if (size_ != 0 && position_ + size >= size_) {
        return size_ - position_;
    }
    return size;
}

}  // namespace ssd
