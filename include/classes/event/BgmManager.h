#ifndef CLASSES_EVENT_BGMMANAGER_H
#define CLASSES_EVENT_BGMMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::BgmManager no evidence names yet
class TUnk_B3C660 {
public:
    virtual ~TUnk_B3C660();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::BgmManager no evidence names yet
class TUnk_B3C688 {
public:
    virtual ~TUnk_B3C688();
};
// table 0x7100B3C660; base at 0x0 unknown (TUnk_B3C660), base at 0x8 unknown (TUnk_B3C688)
class BgmManager : public TUnk_B3C660, public TUnk_B3C688 {
public:
    virtual ~BgmManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
