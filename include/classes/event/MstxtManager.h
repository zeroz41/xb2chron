#ifndef CLASSES_EVENT_MSTXTMANAGER_H
#define CLASSES_EVENT_MSTXTMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::MstxtManager no evidence names yet
class TUnk_B3C5C8 {
public:
    virtual ~TUnk_B3C5C8();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::MstxtManager no evidence names yet
class TUnk_B3C5F0 {
public:
    virtual ~TUnk_B3C5F0();
};
// table 0x7100B3C5C8; base at 0x0 unknown (TUnk_B3C5C8), base at 0x8 unknown (TUnk_B3C5F0)
class MstxtManager : public TUnk_B3C5C8, public TUnk_B3C5F0 {
public:
    virtual ~MstxtManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
