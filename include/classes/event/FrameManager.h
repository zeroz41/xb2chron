#ifndef CLASSES_EVENT_FRAMEMANAGER_H
#define CLASSES_EVENT_FRAMEMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::FrameManager no evidence names yet
class TUnk_B3E1A8 {
public:
    virtual ~TUnk_B3E1A8();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::FrameManager no evidence names yet
class TUnk_B3E1D0 {
public:
    virtual ~TUnk_B3E1D0();
};
// table 0x7100B3E1A8; base at 0x0 unknown (TUnk_B3E1A8), base at 0x8 unknown (TUnk_B3E1D0)
class FrameManager : public TUnk_B3E1A8, public TUnk_B3E1D0 {
public:
    virtual ~FrameManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
