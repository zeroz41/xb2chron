#ifndef CLASSES_EVENT_CPUMANAGER_H
#define CLASSES_EVENT_CPUMANAGER_H

namespace event { enum MSG_TYPE : int; }

#include "ml/TimeCount.h"
#include <math.h>

namespace event {
// a base of event::CpuManager no evidence names yet
class TUnk_B3C6A8 {
public:
    virtual ~TUnk_B3C6A8();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::CpuManager no evidence names yet
class TUnk_B3C6D0 {
public:
    virtual ~TUnk_B3C6D0();
};
// table 0x7100B3C6A8; base at 0x0 unknown (TUnk_B3C6A8), base at 0x8 unknown (TUnk_B3C6D0)
class CpuManager : public TUnk_B3C6A8, public TUnk_B3C6D0 {
public:
    virtual ~CpuManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    // 1.0.0's CpuManager::init/end (0x71000AB610/0x71000AB61C), update (0x71000AB628), calcCpuFrame
    // (0x71000AB680) and tailAlways (0x71000AB6A8); 3.0.1 inlines them into OnEventProc
    void init() { m_flags = 0; m_frame = 0.0f; m_cpuFrame = 0.0f; }
    void end() { m_flags = 0; m_frame = 0.0f; m_cpuFrame = 0.0f; }
    float calcCpuFrame() const { return (int)(m_timer.getSecLap() * 30.0f); }
    void update() {
        if ((m_flags & 7) == 1) {
            m_cpuFrame = fmaxf(calcCpuFrame() - m_startFrame, 0.0f);
        }
    }
    void tailAlways() {
        if ((m_flags & 7) == 1) {
            m_frame = m_cpuFrame;
        }
    }
    // bit 0: started, bit 1: paused, bit 2: paused by the home menu (the name is not the original's)
    unsigned int m_flags;  // 0x10
    float m_frame;  // 0x14 getFrame's
    float m_startFrame;  // 0x18 start keeps calcCpuFrame (the name is not the original's)
    float m_pauseFrame;  // 0x1c pause keeps calcCpuFrame (the name is not the original's)
    float m_cpuFrame;  // 0x20 update's (the name is not the original's)
    unsigned int pad_24;
    ml::TimeCount m_timer;  // 0x28 (the name is not the original's)
};
}  // namespace event

#endif
