#ifndef CLASSES_EVENT_FADEMANAGER_H
#define CLASSES_EVENT_FADEMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::FadeManager no evidence names yet
class TUnk_B3CF60 {
public:
    virtual ~TUnk_B3CF60();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::FadeManager no evidence names yet
class TUnk_B3CF88 {
public:
    virtual ~TUnk_B3CF88();
};
// table 0x7100B3CF60; base at 0x0 unknown (TUnk_B3CF60), base at 0x8 unknown (TUnk_B3CF88)
class FadeManager : public TUnk_B3CF60, public TUnk_B3CF88 {
public:
    virtual ~FadeManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
