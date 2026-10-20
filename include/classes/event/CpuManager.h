#ifndef CLASSES_EVENT_CPUMANAGER_H
#define CLASSES_EVENT_CPUMANAGER_H

namespace event { enum MSG_TYPE : int; }

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
    virtual ~CpuManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
