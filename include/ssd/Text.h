#ifndef SSD_TEXT_H
#define SSD_TEXT_H

#include <stdarg.h>

namespace ssd { struct MemoryBlock; }

// the library's character type (string.cpp's assertion "tchar_ == data_.GetAdrs<ssd_tchar>()")
typedef char16_t ssd_tchar;

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

// formatting into a buffer of size characters (the debug log formats its messages and time stamps so); the
// v/plain forms return the characters written, vsprintf_impl the end of the text
int vsprintf(char* buffer, unsigned long size, const char* format, va_list args);
int vsprintf(char16_t* buffer, unsigned long size, const char16_t* format, va_list args);
int sprintf(char* buffer, unsigned long size, const char* format, ...);
int sprintf(char16_t* buffer, unsigned long size, const char16_t* format, ...);
template <typename T>
T* vsprintf_impl(T* buffer, unsigned long size, const T* format, va_list args);
template <typename T>
T* ToDoubleText(T* buffer, double value, int, int, int);
template <typename T>
T* ToSizeText(T* buffer, long long size);

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
    unsigned long last = size - 1;
    while (*text != 0 && static_cast<unsigned int>(out - buffer) < last) {
        *out++ = *text++;
    }
    *out = 0;
}

}  // namespace ssd

#endif
