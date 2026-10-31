#ifndef CLASSES_ML_TJOB_H
#define CLASSES_ML_TJOB_H

#include "classes/ml/WorkCpu.h"

namespace ml {
// a job a work CPU thread runs: WorkCpu::allocJob hands them out of a fixed_size_alloc<TJOB> (blocks of 0x40 bytes);
// fields not recovered but the CPU
class TJOB {
public:
    unsigned char pad_0[0x38];
    // 0x38 the CPU the job runs on, 0 for any: WorkCpu::wkTail moves a job entered on another CPU's list to this
    // CPU's (the name is not the original's)
    CPUID m_cpu;
    unsigned char pad_3c[0x4];
};
}  // namespace ml

#endif
