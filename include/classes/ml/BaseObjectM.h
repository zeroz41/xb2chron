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
    virtual void AddRef();  // slot 2
    virtual void Release();  // slot 3
    virtual void SetName(char const*);  // slot 4
    int m_refCount;  // 0x8: 1 when built (the name is not the original's)
    mm::mtl::FixStr<128> m_name;  // SetName's
    CriticalSection m_cs;  // 0x90 (~BaseObjectM destroys it; the name is not the original's)
};
}  // namespace ml

#endif
