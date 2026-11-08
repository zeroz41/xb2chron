#ifndef CLASSES_EVENT_EFFECTRES_H
#define CLASSES_EVENT_EFFECTRES_H

#include "classes/event/IResEvent.h"
#include "mm/mtl/FixStr.h"

namespace fw { class EffectPack; }

namespace event {
// table 0x7100B3CEB0
class EffectRes : public IResEvent {
public:
    // named by the symbols (EffectManager::load news one, 0x58 bytes)
    EffectRes(const char* name);
    virtual void OnResEvent(event::IResEvent::PARAM const&);  // slot 0
    virtual ~EffectRes();  // slot 1
    // bit 0: loading (OnResEvent clears it); the name is not the original's
    unsigned int m_flags;  // 0x8
    // the name it was made with (EffectManager::load compares it); the name is not the original's
    // a FixStr<64>: the constructor's assignment asserts the length below 64 and stores it at 0x4c
    mm::mtl::FixStr<64> m_name;  // 0xc
    // the pack OnResEvent makes from the loaded file (one reference, the destructor releases it); the name is not
    // the original's
    fw::EffectPack* m_pack;  // 0x50
};
}  // namespace event

#endif
