#ifndef CLASSES_EVENT_MOTSTMMANAGER_H
#define CLASSES_EVENT_MOTSTMMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::MotstmManager no evidence names yet
class TUnk_B3C558 {
public:
    virtual ~TUnk_B3C558();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::MotstmManager no evidence names yet
class TUnk_B3C580 {
public:
    virtual ~TUnk_B3C580();
};
// table 0x7100B3C558; base at 0x0 unknown (TUnk_B3C558), base at 0x8 unknown (TUnk_B3C580)
class MotstmManager : public TUnk_B3C558, public TUnk_B3C580 {
public:
    virtual ~MotstmManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
