#ifndef CLASSES_SSD_FILESTREAM_H
#define CLASSES_SSD_FILESTREAM_H

#include "classes/ssd/IoStreamBase.h"

namespace ssd { class TextRef; }

namespace ssd {
// table 0x7100B82120
class FileStream : public ::ssd::IoStreamBase {
public:
    virtual ~FileStream();  // slot 0
    virtual void IsOpen() const;  // slot 2
    virtual void Open(ssd::TextRef const&, ssd::IoStreamBase::OpenMode);  // slot 3
    virtual void Close();  // slot 5
    virtual void GetSize(unsigned long*) const;  // slot 6
    virtual void Read(unsigned long, void*, unsigned long*);  // slot 7
    virtual void Write(unsigned long, void const*, unsigned long*);  // slot 8
    virtual void Seek(ssd::IoStreamBase::SeekMode, unsigned long, unsigned long*);  // slot 9
    virtual void GetPosition(unsigned long*) const;  // slot 10
    virtual void Tell(unsigned long*);  // slot 11
    virtual void CheckAccessSize(unsigned long);  // slot 12
};
}  // namespace ssd

#endif
