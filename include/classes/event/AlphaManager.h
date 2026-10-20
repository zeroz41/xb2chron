#ifndef CLASSES_EVENT_ALPHAMANAGER_H
#define CLASSES_EVENT_ALPHAMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::AlphaManager no evidence names yet
class TUnk_B3C120 {
public:
    virtual ~TUnk_B3C120();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::AlphaManager no evidence names yet
class TUnk_B3C148 {
public:
    virtual ~TUnk_B3C148();
};
// table 0x7100B3C120; base at 0x0 unknown (TUnk_B3C120), base at 0x8 unknown (TUnk_B3C148)
class AlphaManager : public TUnk_B3C120, public TUnk_B3C148 {
public:
    virtual ~AlphaManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
