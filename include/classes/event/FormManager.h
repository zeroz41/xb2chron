#ifndef CLASSES_EVENT_FORMMANAGER_H
#define CLASSES_EVENT_FORMMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::FormManager no evidence names yet
class TUnk_B3CFA8 {
public:
    virtual ~TUnk_B3CFA8();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::FormManager no evidence names yet
class TUnk_B3CFD0 {
public:
    virtual ~TUnk_B3CFD0();
};
// table 0x7100B3CFA8; base at 0x0 unknown (TUnk_B3CFA8), base at 0x8 unknown (TUnk_B3CFD0)
class FormManager : public TUnk_B3CFA8, public TUnk_B3CFD0 {
public:
    virtual ~FormManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
