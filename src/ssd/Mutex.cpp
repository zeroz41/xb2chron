#include "ssd/Mutex.h"
#include "ssd/Text.h"

namespace ssd {

// the lock the debug output stream takes (1.0.0's ssd::InitDebug/QuitDebug set it up and tear it down)
Mutex OutStreamLock;

int vsprintf(char* buffer, unsigned long size, const char* format, va_list args) {
    return vsprintf_impl(buffer, size, format, args) - buffer;
}

int vsprintf(char16_t* buffer, unsigned long size, const char16_t* format, va_list args) {
    return vsprintf_impl(buffer, size, format, args) - buffer;
}

int sprintf(char* buffer, unsigned long size, const char* format, ...) {
    va_list args;
    va_start(args, format);
    int length = vsprintf_impl(buffer, size, format, args) - buffer;
    va_end(args);
    return length;
}

int sprintf(char16_t* buffer, unsigned long size, const char16_t* format, ...) {
    va_list args;
    va_start(args, format);
    int length = vsprintf_impl(buffer, size, format, args) - buffer;
    va_end(args);
    return length;
}

}  // namespace ssd
