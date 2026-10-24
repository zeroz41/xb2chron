#ifndef CLASSES_SSD_IOSTREAMBASE_H
#define CLASSES_SSD_IOSTREAMBASE_H

#include "classes/ssd/Object.h"
#include "ssd/Debug.h"

namespace ssd { class TextRef; }

namespace ssd {
// table none (its derived classes'): a stream the library reads audio from. 1.0.0 has every virtual out of
// line in IoStreamBase.cpp; 3.0.1 keeps only the two Opens its derived tables use (global, in IoStreamBase's
// unit), so those are out of line and the rest are inline here.
class IoStreamBase : public ::ssd::Object {
public:
    // how a stream opens: MemoryStream::Open accepts only 1
    enum OpenMode : unsigned char {
        OpenMode_Read = 1,  // the name is not the original's
    };
    // where Seek counts from: 1 the start, 2 the position, 3 the end (MemoryStream::Seek)
    enum SeekMode : unsigned char {
        SeekMode_Begin = 1,    // the name is not the original's
        SeekMode_Current = 2,  // the name is not the original's
        SeekMode_End = 3,      // the name is not the original's
    };

    IoStreamBase(ObjectType::Id type) : Object(type), pad_18(0) {}

    virtual ~IoStreamBase() {}  // slot 0
    virtual bool IsOpen() const {  // slot 2
        return false;
    }
    virtual Result Open(const TextRef& path, OpenMode mode);  // slot 3
    virtual Result Open(void* data, unsigned long size, OpenMode mode);  // slot 4
    virtual Result Close() {  // slot 5
        return Result(-1);
    }
    virtual Result GetSize(unsigned long* fileSize) const {  // slot 6
        return Result(-1);
    }
    virtual Result Read(unsigned long size, void* buffer, unsigned long* readSize) {  // slot 7
        return Result(-1);
    }
    virtual Result Write(unsigned long size, const void* buffer, unsigned long* writeSize) {  // slot 8
        return Result(-1);
    }
    virtual Result Seek(SeekMode mode, unsigned long offset, unsigned long* position) {  // slot 9
        return Result(-1);
    }
    virtual Result GetPosition(unsigned long* position) const {  // slot 10
        return Result(-1);
    }
    virtual Result Tell(unsigned long* position) {  // slot 11
        return Result(-1);
    }
    // how much of size can be accessed from the position
    virtual unsigned long CheckAccessSize(unsigned long size) {  // slot 12
        return 0;
    }

    // reads size bytes from offset
    Result GetData(unsigned long offset, unsigned long size, void* buffer, unsigned long* readSize);

    // zeroed by FileStream's constructor; nothing found reads it yet
    unsigned long pad_18;
};
}  // namespace ssd

#endif
