#ifndef CLASSES_EVENT_LIPSYNCRES_H
#define CLASSES_EVENT_LIPSYNCRES_H

#include "classes/event/IResEvent.h"
#include "arc/CArcData.h"
#include "mm/mtl/FixStr.h"

namespace event {
// table 0x7100B3D298
class LipsyncRes : public IResEvent {
public:
    // named by the symbols (LipsyncManager::load news one, 0x68 bytes)
    LipsyncRes(const char* name);
    virtual void OnResEvent(event::IResEvent::PARAM const&);  // slot 0
    virtual ~LipsyncRes() {}  // slot 1
    // bit 0: loading (OnResEvent clears it), bit 1: loaded (set on a type 3 event); the name is not the original's
    unsigned int m_flags;  // 0x8
    // the name it was made with (LipsyncManager::load compares it); the name is not the original's
    mm::mtl::FixStr<32> m_name;  // 0xc
    unsigned char pad_30[0x20];
    // the loaded archive (OnResEvent sets its data); the name is not the original's
    arc::CArcData m_arc;  // 0x50
    unsigned int pad_60;  // the constructor clears it (0x68 bytes: LipsyncManager::load news that many)
    unsigned char pad_64[0x4];
};
}  // namespace event

#endif
