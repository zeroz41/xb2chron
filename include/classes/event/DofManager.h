#ifndef CLASSES_EVENT_DOFMANAGER_H
#define CLASSES_EVENT_DOFMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::DofManager no evidence names yet
class TUnk_B3CDC0 {
public:
    virtual ~TUnk_B3CDC0();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::DofManager no evidence names yet
class TUnk_B3CDE8 {
public:
    virtual ~TUnk_B3CDE8();
};
// table 0x7100B3CDC0; base at 0x0 unknown (TUnk_B3CDC0), base at 0x8 unknown (TUnk_B3CDE8)
class DofManager : public TUnk_B3CDC0, public TUnk_B3CDE8 {
public:
    virtual ~DofManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
