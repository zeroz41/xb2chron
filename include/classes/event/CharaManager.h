#ifndef CLASSES_EVENT_CHARAMANAGER_H
#define CLASSES_EVENT_CHARAMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::CharaManager no evidence names yet
class TUnk_B3CD30 {
public:
    virtual ~TUnk_B3CD30();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::CharaManager no evidence names yet
class TUnk_B3CD58 {
public:
    virtual ~TUnk_B3CD58();
};
// table 0x7100B3CD30; base at 0x0 unknown (TUnk_B3CD30), base at 0x8 unknown (TUnk_B3CD58)
class CharaManager : public TUnk_B3CD30, public TUnk_B3CD58 {
public:
    virtual ~CharaManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
