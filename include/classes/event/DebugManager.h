#ifndef CLASSES_EVENT_DEBUGMANAGER_H
#define CLASSES_EVENT_DEBUGMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::DebugManager no evidence names yet
class TUnk_B3BFD0 {
public:
    virtual ~TUnk_B3BFD0();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::DebugManager no evidence names yet
class TUnk_B3BFF8 {
public:
    virtual ~TUnk_B3BFF8();
};
// table 0x7100B3BFD0; base at 0x0 unknown (TUnk_B3BFD0), base at 0x8 unknown (TUnk_B3BFF8)
class DebugManager : public TUnk_B3BFD0, public TUnk_B3BFF8 {
public:
    virtual ~DebugManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
