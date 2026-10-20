#ifndef CLASSES_EVENT_SHAKEMANAGER_H
#define CLASSES_EVENT_SHAKEMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::ShakeManager no evidence names yet
class TUnk_B3D4F8 {
public:
    virtual ~TUnk_B3D4F8();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::ShakeManager no evidence names yet
class TUnk_B3D520 {
public:
    virtual ~TUnk_B3D520();
};
// table 0x7100B3D4F8; base at 0x0 unknown (TUnk_B3D4F8), base at 0x8 unknown (TUnk_B3D520)
class ShakeManager : public TUnk_B3D4F8, public TUnk_B3D520 {
public:
    virtual ~ShakeManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
