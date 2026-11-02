#ifndef MTL_CALLSTACKINFO_H
#define MTL_CALLSTACKINFO_H

#include "ml/ml_misc.h"
#include "mm/mtl/IntrusiveList.h"

namespace mtl {

// one recorded allocation call stack (CallStackManager::regist hands it out, DlAllocator keeps it in an
// allocation's footer). 1.0.0 names the class, log() and release(); the field names and m_trace's extent are not the
// original's. Linked in CallStackManager's list through its base (remove unlinks the record itself)
class CallStackInfo : public mm::mtl::IntrusiveListNodeBase {
public:
    // 1.0.0 has it out of line (0x710077E34C); 3.0.1 inlines it in DlAllocator::log_callSTack
    void log() {
        if (m_traceCount != 0) {
            mlStackTrace(m_trace);
        }
    }

    // 1.0.0 has it out of line (0x710077EDA0, 0x14 bytes); 3.0.1 inlines it in CallStackManager::remove. What it
    // returns is inferred
    int release() { return --m_refCount; }

    unsigned char pad_10[0x4];
    int m_refCount;  // +0x14: CallStackManager::remove unlinks the record at 1 and frees it at 0
    unsigned long m_trace[16];  // the return addresses mlStackTrace logs (extent inferred)
    unsigned char pad_98[0xC];
    unsigned short m_traceCount;  // +0xA4
};

}  // namespace mtl

#endif
