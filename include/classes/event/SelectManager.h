#ifndef CLASSES_EVENT_SELECTMANAGER_H
#define CLASSES_EVENT_SELECTMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::SelectManager no evidence names yet
class TUnk_B3D748 {
public:
    virtual ~TUnk_B3D748();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::SelectManager no evidence names yet
class TUnk_B3D770 {
public:
    virtual ~TUnk_B3D770();
};
// table 0x7100B3D748; base at 0x0 unknown (TUnk_B3D748), base at 0x8 unknown (TUnk_B3D770)
class SelectManager : public TUnk_B3D748, public TUnk_B3D770 {
public:
    virtual ~SelectManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
