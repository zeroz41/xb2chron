#ifndef CLASSES_EVENT_CAMMANAGER_H
#define CLASSES_EVENT_CAMMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::CamManager no evidence names yet
class TUnk_B3C9A8 {
public:
    virtual ~TUnk_B3C9A8();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::CamManager no evidence names yet
class TUnk_B3C9D0 {
public:
    virtual ~TUnk_B3C9D0();
};
// table 0x7100B3C9A8; base at 0x0 unknown (TUnk_B3C9A8), base at 0x8 unknown (TUnk_B3C9D0)
class CamManager : public TUnk_B3C9A8, public TUnk_B3C9D0 {
public:
    virtual ~CamManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
