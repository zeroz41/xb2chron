#ifndef CLASSES_ML_BASEOBJECTM_H
#define CLASSES_ML_BASEOBJECTM_H

#include "mm/mtl/FixStr.h"
#include "ml/CriticalSection.h"

namespace ml {
// table 0x7100B77720
class BaseObjectM {
public:
    // inline: FileResTh's constructor builds it in place (count 1, empty name, critical section)
    BaseObjectM() : m_refCount(1) {}
    // inline: its D1/D0 sit in th_dev_file_nx's weak tail, ~FileResTh inlines it
    virtual ~BaseObjectM() {}  // slot 0
    // inline: the weak copies sit in AssetData.cpp's range (its fw::AssetLoader table is the first to reference them)
    // the count after the increment
    virtual int AddRef() {  // slot 2
        CS cs(m_cs);
        return ++m_refCount;
    }
    // the count after the decrement; deleted (D0) when it reaches 0
    virtual int Release() {  // slot 3
        int count;
        {
            CS cs(m_cs);
            count = --m_refCount;
        }
        if (count == 0) {
            delete this;
        }
        return count;
    }
    virtual void SetName(char const* name) {  // slot 4
        CS cs(m_cs);
        m_name = name;
    }
    int m_refCount;  // 0x8: 1 when built (the name is not the original's)
    mm::mtl::FixStr<128> m_name;  // SetName's
    CriticalSection m_cs;  // 0x90 (~BaseObjectM destroys it; the name is not the original's)
};
}  // namespace ml

#endif
