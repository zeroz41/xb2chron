#ifndef CLASSES_ML_BASEOBJECTM_H
#define CLASSES_ML_BASEOBJECTM_H

#include "mm/mtl/FixStr.h"

namespace ml {
// table 0x7100B77720
class BaseObjectM {
public:
    virtual ~BaseObjectM();  // slot 0
    virtual void AddRef();  // slot 2
    virtual void Release();  // slot 3
    virtual void SetName(char const*);  // slot 4
    unsigned char pad_8[0x4];
    mm::mtl::FixStr<128> m_name;  // SetName's
    unsigned char pad_90[0x28];  // fields: size from its derived classes
};
}  // namespace ml

#endif
