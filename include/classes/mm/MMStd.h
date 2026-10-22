#ifndef CLASSES_MM_MMSTD_H
#define CLASSES_MM_MMSTD_H

#include "mm/MMStdBase.h"

namespace mm {
// table 0x7100B75960: mm_lib's own output, through the SDK's log
class MMStd : public ::mm::MMStdBase {
public:
    virtual void customOutput(const char* text);  // slot 2
    virtual void customAssert(const char* expression, const char* file, unsigned int line);  // slot 3
    virtual void customAssertMsg(const char* expression, const char* file, unsigned int line,
                                 const char* message);  // slot 4
};

// the output the library starts with (MMStdBase::s_pCurrentStd's first value)
extern MMStd s_mm_std;
}  // namespace mm

#endif
