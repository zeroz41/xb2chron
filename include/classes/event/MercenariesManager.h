#ifndef CLASSES_EVENT_MERCENARIESMANAGER_H
#define CLASSES_EVENT_MERCENARIESMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::MercenariesManager no evidence names yet
class TUnk_B3D6E0 {
public:
    virtual ~TUnk_B3D6E0();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::MercenariesManager no evidence names yet
class TUnk_B3D708 {
public:
    virtual ~TUnk_B3D708();
};
// table 0x7100B3D6E0; base at 0x0 unknown (TUnk_B3D6E0), base at 0x8 unknown (TUnk_B3D708)
class MercenariesManager : public TUnk_B3D6E0, public TUnk_B3D708 {
public:
    virtual ~MercenariesManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
