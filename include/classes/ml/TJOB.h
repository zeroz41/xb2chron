#ifndef CLASSES_ML_TJOB_H
#define CLASSES_ML_TJOB_H

#include "classes/ml/WorkCpu.h"

namespace ml {
// a job a work CPU thread runs: WorkCpu::allocJob hands them out of a fixed_size_alloc<TJOB> (blocks of 0x40 bytes);
// fields not recovered but the CPU
class TJOB {
public:
    // 0x0 the function the thread runs, with m_data and m_extra (entryJobThread's job, data and extra; the names are
    // not the original's)
    unsigned int (*m_func)(void*, void*);
    unsigned char pad_8[0x8];
    void* m_data;   // 0x10
    void* m_extra;  // 0x18
    int m_result;  // 0x20 WorkCpu::getResult's (the name is not the original's)
    int m_group;   // 0x24 the job group's handle (WorkCpu::getResult finds a group's job by it; the name is not the original's)
    // 0x28 the job's colour as 0xAABBGGRR (WorkCpu::wkStandbyLogin colours thRender's job mm::Col3::salmon; the name
    // is not the original's)
    unsigned int m_color;
    unsigned char pad_2c[0x4];
    int pad_30;  // 0x30 WorkCpuThread::transferJob hands over the first job whose value is 0
    unsigned char pad_34[0x4];
    // 0x38 the CPU the job runs on, 0 for any: WorkCpu::wkTail moves a job entered on another CPU's list to this
    // CPU's (the name is not the original's)
    CPUID m_cpu;
    unsigned char pad_3c[0x4];
};
}  // namespace ml

#endif
