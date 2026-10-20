#ifndef CLASSES_EVENT_UIMANAGER_H
#define CLASSES_EVENT_UIMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::UIManager no evidence names yet
class TUnk_B3D5C8 {
public:
    virtual ~TUnk_B3D5C8();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::UIManager no evidence names yet
class TUnk_B3D5F0 {
public:
    virtual ~TUnk_B3D5F0();
};
// table 0x7100B3D5C8; base at 0x0 unknown (TUnk_B3D5C8), base at 0x8 unknown (TUnk_B3D5F0)
class UIManager : public TUnk_B3D5C8, public TUnk_B3D5F0 {
public:
    virtual ~UIManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
