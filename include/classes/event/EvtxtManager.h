#ifndef CLASSES_EVENT_EVTXTMANAGER_H
#define CLASSES_EVENT_EVTXTMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::EvtxtManager no evidence names yet
class TUnk_B3D9D8 {
public:
    virtual ~TUnk_B3D9D8();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::EvtxtManager no evidence names yet
class TUnk_B3DA00 {
public:
    virtual ~TUnk_B3DA00();
};
// table 0x7100B3D9D8; base at 0x0 unknown (TUnk_B3D9D8), base at 0x8 unknown (TUnk_B3DA00)
class EvtxtManager : public TUnk_B3D9D8, public TUnk_B3DA00 {
public:
    virtual ~EvtxtManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
