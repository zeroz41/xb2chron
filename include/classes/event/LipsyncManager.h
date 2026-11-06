#ifndef CLASSES_EVENT_LIPSYNCMANAGER_H
#define CLASSES_EVENT_LIPSYNCMANAGER_H

#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
class LipsyncRes;

// table 0x7100B3D2C0; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::LipsyncManager>
class LipsyncManager : public IManager, public mm::mtl::Singleton<LipsyncManager> {
public:
    // inline: Singleton<LipsyncManager>::getPtr's static (VoiceManager::playAuto) builds it in place
    LipsyncManager() : pad_10(0), pad_60(0), pad_f0(0) {}
    virtual ~LipsyncManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    void clear();
    // named by the symbols: makes and keeps a LipsyncRes for name unless one of that name is kept
    void load(const char* name);
    // true when it found the lip-sync data of a voice path (VoiceManager::playAuto keeps the result in bit 1)
    bool setTarget(const char* path);
    unsigned int pad_10;
    unsigned char pad_14[0x4];
    // the loaded lip-sync resources (LipsyncManager::load pushes each new LipsyncRes); the name is not the original's
    mm::mtl::FixedVector<LipsyncRes*, 8> m_res;  // 0x18
    unsigned long pad_60;
    mm::mtl::FixStr<128> pad_68;
    unsigned char pad_ec[0x4];
    unsigned long pad_f0;
};
}  // namespace event

#endif
