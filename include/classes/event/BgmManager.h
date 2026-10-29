#ifndef CLASSES_EVENT_BGMMANAGER_H
#define CLASSES_EVENT_BGMMANAGER_H

namespace event { enum MSG_TYPE : int; }

#include "mm/mtl/FixStr.h"
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event {
// table 0x7100B3C660; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::BgmManager>
class BgmManager : public IManager, public mm::mtl::Singleton<BgmManager> {
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
