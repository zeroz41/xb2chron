#ifndef CLASSES_EVENT_QUESTMANAGER_H
#define CLASSES_EVENT_QUESTMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::QuestManager no evidence names yet
class TUnk_B3D698 {
public:
    virtual ~TUnk_B3D698();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::QuestManager no evidence names yet
class TUnk_B3D6C0 {
public:
    virtual ~TUnk_B3D6C0();
};
// table 0x7100B3D698; base at 0x0 unknown (TUnk_B3D698), base at 0x8 unknown (TUnk_B3D6C0)
class QuestManager : public TUnk_B3D698, public TUnk_B3D6C0 {
public:
    virtual ~QuestManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
