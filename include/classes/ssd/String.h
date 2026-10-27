#ifndef CLASSES_SSD_STRING_H
#define CLASSES_SSD_STRING_H

#include "classes/ssd/TextRef.h"
#include "ssd/MemoryBlock.h"

namespace ssd {
// table 0x7100B823C8: a TextRef that owns a copy of its text. sizeof 0x30: StreamController's fields follow a
// WaveSource's path_ 0x30 bytes on; String() sets the encoding to 3 and zeroes the copy (D:/ssd/ssd51/ssd/sources/util/string.cpp).
class String : public ::ssd::TextRef {
public:
    virtual void Set(ssd::TextRef const&);  // slot 0
    virtual void Set(char const*);  // slot 1
    virtual void Set(char16_t const*);  // slot 2
    virtual ~String();  // slot 3

    String();
    // frees the text the string holds
    void FreeImpl();
    // WaveSource::InitWithFile sets its path through the table (slot 0), so the assignment is an inline
    // member (the operator is not known to be the original's)
    String& operator=(const TextRef& text) {
        Set(text);
        return *this;
    }

    // the copy of the text tchar_ points at (FreeImpl gives it back to SoundMemory::allocator_): the name is
    // string.cpp's assertions' ("data_.GetAdrs() != ssd_null")
    MemoryBlock data_;
};
}  // namespace ssd

#endif
