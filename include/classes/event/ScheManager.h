#ifndef CLASSES_EVENT_SCHEMANAGER_H
#define CLASSES_EVENT_SCHEMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::ScheManager no evidence names yet
class TUnk_B3D580 {
public:
    virtual ~TUnk_B3D580();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::ScheManager no evidence names yet
class TUnk_B3D5A8 {
public:
    virtual ~TUnk_B3D5A8();
};
// table 0x7100B3D580; base at 0x0 unknown (TUnk_B3D580), base at 0x8 unknown (TUnk_B3D5A8)
class ScheManager : public TUnk_B3D580, public TUnk_B3D5A8 {
public:
    virtual ~ScheManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
