#include <stdio.h>
#include "classes/mm/MMStd.h"
#include "nn/diag.h"

namespace mm {

MMStd s_mm_std;

MMStdBase* MMStdBase::s_pCurrentStd = &s_mm_std;

void MMStdBase::mmPrint(const char* format, ...) {
    char text[0x400];
    va_list arguments;
    va_start(arguments, format);
    vsnprintf(text, sizeof(text), format, arguments);
    va_end(arguments);
    s_pCurrentStd->customOutput(text);
}

void MMStd::customOutput(const char* text) {
#line 67
    NN_LOG(text);
}

void MMStdBase::mmAssert(const char* expression, const char* file, unsigned int line) {
    s_pCurrentStd->customAssert(expression, file, line);
}

void MMStd::customAssert(const char* expression, const char* file, unsigned int line) {
    mmPrint("Failed assertion at %s:%d\n  ", file, line);
    mmPrint(expression);
    mmPrint("\n");
    asm volatile(".inst 0xe7ffdefe");  // stops here: an undefined instruction
}

void MMStd::customAssertMsg(const char* expression, const char* file, unsigned int line, const char* message) {
    mmPrint("Failed assertion at %s:%d\n  ", file, line);
    mmPrint(expression);
    mmPrint("\n");
    mmPrint("%s\n", message);
    asm volatile(".inst 0xe7ffdefe");  // stops here: an undefined instruction
}

}  // namespace mm
