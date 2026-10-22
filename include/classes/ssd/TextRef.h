#ifndef CLASSES_SSD_TEXTREF_H
#define CLASSES_SSD_TEXTREF_H

#include "ssd/Hash.h"
#include "ssd/Text.h"

namespace ssd { struct MemoryBlock; }

namespace ssd {
// table 0x7100B82098: a reference to a text in either encoding, with its hash; a reference cannot be Set
class TextRef {
public:
    TextRef(const char* text);
    TextRef(const char16_t* text) {
        InitImpl(text);
    }

    virtual void Set(const TextRef& text);  // slot 0
    virtual void Set(const char* text);  // slot 1
    virtual void Set(const char16_t* text);  // slot 2

    // 1.0.0 has this out of line; 3.0.1 keeps no copy (TextRef(const char*) inlines it)
    void InitImpl(const char* text) {
        utf8_ = text;
        type_ = TextEncodeType_Utf8;
        hash_.Clear();
        hash_.CalcTextHash(text);
    }
    void InitImpl(const char16_t* text);
    // the text in encoding type, in a buffer block takes from SoundMemory::allocator_
    void GetText(MemoryBlock* block, TextEncodeType type) const;
    // the text in encoding type, in buffer (size characters at most)
    void GetText(void* buffer, unsigned long size, TextEncodeType type) const;

    static const char16_t* EmptyText;

    Hash hash_;
    // the text, in the encoding type_ names (the names are not the original's)
    union {
        const char* utf8_;
        const char16_t* utf16_;
    };
    TextEncodeType type_;
};
}  // namespace ssd

#endif
