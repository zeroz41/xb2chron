#ifndef CLASSES_EVENT_RANDMANAGER_H
#define CLASSES_EVENT_RANDMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::RandManager no evidence names yet
class TUnk_B3D3C0 {
public:
    virtual ~TUnk_B3D3C0();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::RandManager no evidence names yet
class TUnk_B3D3E8 {
public:
    virtual ~TUnk_B3D3E8();
};
// table 0x7100B3D3C0; base at 0x0 unknown (TUnk_B3D3C0), base at 0x8 unknown (TUnk_B3D3E8)
class RandManager : public TUnk_B3D3C0, public TUnk_B3D3E8 {
public:
    virtual ~RandManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
