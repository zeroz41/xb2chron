#ifndef CLASSES_EVENT_EFFECTMANAGER_H
#define CLASSES_EVENT_EFFECTMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::EffectManager no evidence names yet
class TUnk_B3CED8 {
public:
    virtual ~TUnk_B3CED8();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::EffectManager no evidence names yet
class TUnk_B3CF00 {
public:
    virtual ~TUnk_B3CF00();
};
// table 0x7100B3CED8; base at 0x0 unknown (TUnk_B3CED8), base at 0x8 unknown (TUnk_B3CF00)
class EffectManager : public TUnk_B3CED8, public TUnk_B3CF00 {
public:
    virtual ~EffectManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
