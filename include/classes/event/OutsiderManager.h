#ifndef CLASSES_EVENT_OUTSIDERMANAGER_H
#define CLASSES_EVENT_OUTSIDERMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::OutsiderManager no evidence names yet
class TUnk_B3D350 {
public:
    virtual ~TUnk_B3D350();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::OutsiderManager no evidence names yet
class TUnk_B3D378 {
public:
    virtual ~TUnk_B3D378();
};
// table 0x7100B3D350; base at 0x0 unknown (TUnk_B3D350), base at 0x8 unknown (TUnk_B3D378)
class OutsiderManager : public TUnk_B3D350, public TUnk_B3D378 {
public:
    virtual ~OutsiderManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
