#ifndef CLASSES_EVENT_LIPSYNCMANAGER_H
#define CLASSES_EVENT_LIPSYNCMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::LipsyncManager no evidence names yet
class TUnk_B3D2C0 {
public:
    virtual ~TUnk_B3D2C0() {}
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::LipsyncManager no evidence names yet
class TUnk_B3D2E8 {
public:
    virtual ~TUnk_B3D2E8() {}
};
// table 0x7100B3D2C0; base at 0x0 unknown (TUnk_B3D2C0), base at 0x8 unknown (TUnk_B3D2E8)
class LipsyncManager : public TUnk_B3D2C0, public TUnk_B3D2E8 {
public:
    virtual ~LipsyncManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    void clear();
};
}  // namespace event

#endif
