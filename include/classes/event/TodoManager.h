#ifndef CLASSES_EVENT_TODOMANAGER_H
#define CLASSES_EVENT_TODOMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::TodoManager no evidence names yet
class TUnk_B3DBA8 {
public:
    virtual ~TUnk_B3DBA8();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::TodoManager no evidence names yet
class TUnk_B3DBD0 {
public:
    virtual ~TUnk_B3DBD0();
};
// table 0x7100B3DBA8; base at 0x0 unknown (TUnk_B3DBA8), base at 0x8 unknown (TUnk_B3DBD0)
class TodoManager : public TUnk_B3DBA8, public TUnk_B3DBD0 {
public:
    virtual ~TodoManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
