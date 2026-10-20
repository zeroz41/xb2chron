#ifndef CLASSES_EVENT_MEMORYMANAGER_H
#define CLASSES_EVENT_MEMORYMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::MemoryManager no evidence names yet
class TUnk_B3BE68 {
public:
    virtual ~TUnk_B3BE68();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::MemoryManager no evidence names yet
class TUnk_B3BE90 {
public:
    virtual ~TUnk_B3BE90();
};
// table 0x7100B3BE68; base at 0x0 unknown (TUnk_B3BE68), base at 0x8 unknown (TUnk_B3BE90)
class MemoryManager : public TUnk_B3BE68, public TUnk_B3BE90 {
public:
    virtual ~MemoryManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
