#ifndef CLASSES_ML_THREADVAL_H
#define CLASSES_ML_THREADVAL_H

#include <string.h>

#include "classes/ml/WorkCpu.h"

namespace ml {
// what WorkCpu swaps every frame (WorkCpu::removeSwap takes one); its table has no copy of its own in the module
class IThreadValue {
public:
    virtual ~IThreadValue() {}  // slot 0
    virtual void tvSwap() = 0;  // slot 2
    virtual unsigned char getCpuBank() const = 0;  // slot 3
    virtual void setCpuBank(unsigned char) = 0;  // slot 4
};

// a template: 6 instances in the module. A value kept twice: tvSwap copies the calculation thread's copy over
// the render thread's and swaps the two buffers (threadval<ScnObjCam::RENDER_INFO>::tvSwap)
template <typename T0>
class threadval : public IThreadValue {
public:
    virtual ~threadval() { WorkCpu::removeSwap(this); }  // slot 0
    virtual void tvSwap() {  // slot 2
        if (m_state.isCopy()) {
            // a byte copy (threadval<ScnObjCam::RENDER_INFO> copies its 0x380 bytes with memcpy although the
            // camera's information holds mm::Vec3s, whose own copies skip their padding)
            memcpy(m_render, m_cpu, sizeof(T0));
        }
        m_state.m_bank = 1 - m_state.m_bank;
        m_render = &m_buf[m_state.m_bank];
        m_cpu = &m_buf[1 - m_state.m_bank];
    }
    virtual unsigned char getCpuBank() const { return m_state.m_cpuBank; }  // slot 3
    virtual void setCpuBank(unsigned char bank) { m_state.m_cpuBank = bank; }  // slot 4

    T0* m_render;  // what tvSwap copies m_cpu into (the name is not the original's)
    T0* m_cpu;     // what ScnObjCam::setLookAt writes (the name is not the original's)
    // the two copies m_render and m_cpu point into, at 0x18, or 0x20 when T0 is 16-aligned (WinView's 8-aligned
    // RENDER_INFO's are at 0x18) (the name is not the original's)
    T0 m_buf[2];
    // the four bytes after the buffers. tvSwap's read of the copy flag is a 1-aligned bit test the next byte's
    // read is not merged with (no load widening), which a bitfield read through a 1-aligned type's own inline
    // accessor gives; a plain member of threadval does not (the struct and its names are not the original's)
    struct STATE {
        bool isCopy() const { return m_copy; }
        bool m_copy : 1;          // tvSwap copies m_cpu over m_render first (the name is not the original's)
        unsigned char pad_1[1];
        unsigned char m_bank;     // which of m_buf m_render points at (the name is not the original's)
        unsigned char m_cpuBank;  // getCpuBank/setCpuBank (the name is not the original's)
    } m_state;
};
}  // namespace ml

#endif
