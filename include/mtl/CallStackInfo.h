#ifndef MTL_CALLSTACKINFO_H
#define MTL_CALLSTACKINFO_H

#include "ml/ml_misc.h"

namespace mtl {

// one recorded allocation call stack (CallStackManager::regist hands it out, DlAllocator keeps it in an
// allocation's footer). 1.0.0 names the class and log(); the field names and m_trace's extent are not the original's
class CallStackInfo {
public:
    // 1.0.0 has it out of line (0x710077E34C); 3.0.1 inlines it in DlAllocator::log_callSTack
    void log() {
        if (m_traceCount != 0) {
            mlStackTrace(m_trace);
        }
    }

    unsigned char pad_0[0x18];
    unsigned long m_trace[16];  // the return addresses mlStackTrace logs (extent inferred)
    unsigned char pad_98[0xC];
    unsigned short m_traceCount;  // +0xA4
};

}  // namespace mtl

#endif
