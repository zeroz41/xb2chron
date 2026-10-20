#ifndef CLASSES_EVENT_CSSNDMANAGER_H
#define CLASSES_EVENT_CSSNDMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::CsSndManager no evidence names yet
class TUnk_B3CD78 {
public:
    virtual ~TUnk_B3CD78();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::CsSndManager no evidence names yet
class TUnk_B3CDA0 {
public:
    virtual ~TUnk_B3CDA0();
};
// table 0x7100B3CD78; base at 0x0 unknown (TUnk_B3CD78), base at 0x8 unknown (TUnk_B3CDA0)
class CsSndManager : public TUnk_B3CD78, public TUnk_B3CDA0 {
public:
    virtual ~CsSndManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
