#ifndef CLASSES_EVENT_BGMMANAGER_H
#define CLASSES_EVENT_BGMMANAGER_H

namespace event { enum MSG_TYPE : int; }

#include "mm/mtl/FixStr.h"

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
    BgmManager();  // out of line (Singleton<BgmManager>::getPtr calls it)
    void play(const char*, float, float, float, float, float, float, float, bool, float);
    void changeVolume(float, float);
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    // fields the constructor initializes; what they hold is not known yet
    unsigned int pad_10;
    unsigned int pad_14;
    mm::mtl::FixStr<64> pad_18;
    unsigned char pad_5c[0x20];
    unsigned int pad_7c;
    unsigned char pad_80[0x8];
};
}  // namespace event

#endif
