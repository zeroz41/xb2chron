#ifndef CLASSES_EVENT_SKIPMANAGER_H
#define CLASSES_EVENT_SKIPMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::SkipManager no evidence names yet
class TUnk_B3E1F0 {
public:
    virtual ~TUnk_B3E1F0() {}
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::SkipManager no evidence names yet
class TUnk_B3E218 {
public:
    virtual ~TUnk_B3E218() {}
};
// table 0x7100B3E1F0; base at 0x0 unknown (TUnk_B3E1F0), base at 0x8 unknown (TUnk_B3E218)
class SkipManager : public TUnk_B3E1F0, public TUnk_B3E218 {
public:
    virtual ~SkipManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
