#ifndef CLASSES_EVENT_HIDEMANAGER_H
#define CLASSES_EVENT_HIDEMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::HideManager no evidence names yet
class TUnk_B3D178 {
public:
    virtual ~TUnk_B3D178();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::HideManager no evidence names yet
class TUnk_B3D1A0 {
public:
    virtual ~TUnk_B3D1A0();
};
// table 0x7100B3D178; base at 0x0 unknown (TUnk_B3D178), base at 0x8 unknown (TUnk_B3D1A0)
class HideManager : public TUnk_B3D178, public TUnk_B3D1A0 {
public:
    virtual ~HideManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
