#ifndef CLASSES_EVENT_BLURMANAGER_H
#define CLASSES_EVENT_BLURMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::BlurManager no evidence names yet
class TUnk_B3CE08 {
public:
    virtual ~TUnk_B3CE08();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::BlurManager no evidence names yet
class TUnk_B3CE30 {
public:
    virtual ~TUnk_B3CE30();
};
// table 0x7100B3CE08; base at 0x0 unknown (TUnk_B3CE08), base at 0x8 unknown (TUnk_B3CE30)
class BlurManager : public TUnk_B3CE08, public TUnk_B3CE30 {
public:
    virtual ~BlurManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
