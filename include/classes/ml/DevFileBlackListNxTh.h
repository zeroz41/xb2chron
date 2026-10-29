#ifndef CLASSES_ML_DEVFILEBLACKLISTNXTH_H
#define CLASSES_ML_DEVFILEBLACKLISTNXTH_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace ml { class DevFileBlackListNxTh; }

namespace ml {
// table 0x7100B76BC0
class DevFileBlackListNxTh : public ::mm::mtl::PtrSingleton< ::ml::DevFileBlackListNxTh> {
public:
    virtual ~DevFileBlackListNxTh();  // slot 0

    void* m_buffer;  // 0x8: the destructor frees it with mtl::MemManager (the name is not the original's)
};
}  // namespace ml

#endif
