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
    void clear();  // 1.0.0 symbol; 3.0.1 keeps only OnEventProc's inlined copies
    void update();  // OnEventProc runs it (3.0.1 symbol)
    void render();  // OnEventProc runs it (3.0.1 symbol)
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    // fields the constructor initializes; what they hold is not known yet
    unsigned int pad_10;
    unsigned int pad_14;
    mm::mtl::FixStr<64> pad_18;
    // the volume changeVolume last asked for, clamped to 0..1; the name is not the original's
    float m_volume;  // 0x5c
    unsigned char pad_60[0x1c];
    unsigned int pad_7c;
    unsigned char pad_80[0x8];
};
}  // namespace event

#endif
