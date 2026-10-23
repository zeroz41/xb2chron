#ifndef SSD_TEXT_H
#define SSD_TEXT_H

namespace ssd { struct MemoryBlock; }

namespace ssd {

// how a text is encoded: TextRef(const char*) sets 2, InitImpl(const char16_t*) 3
enum TextEncodeType : unsigned char {
    TextEncodeType_Utf8 = 2,   // the name is not the original's
    TextEncodeType_Utf16 = 3,  // the name is not the original's
};

void Utf8ToUTF16(const char* text, char16_t* buffer, unsigned long size);
void Utf16ToUTF8(const char16_t* text, char* buffer, unsigned long size);
bool Utf8ToUTF16(const char* text, MemoryBlock* block);
bool Utf16ToUTF8(const char16_t* text, MemoryBlock* block);

// the characters before text's terminator (the name is not the original's)
template <typename T>
inline unsigned long GetTextLength(const T* text) {
    const T* end = text;
    while (*end != 0) {
        end++;
    }
    return end - text;
}

// copies text into buffer, at most size - 1 characters and a terminator (the name is not the original's)
template <typename T>
inline void CopyText(T* buffer, const T* text, unsigned long size) {
    T* out = buffer;
    while (*text != 0 && static_cast<unsigned int>(out - buffer) < size - 1) {
        *out++ = *text++;
    }
    *out = 0;
}

}  // namespace ssd

#endif
