#ifndef CLASSES_EVENT_EFFECTRES_H
#define CLASSES_EVENT_EFFECTRES_H

#include "classes/event/IResEvent.h"

namespace fw { class EffectPack; }

namespace event {
// table 0x7100B3CEB0
class EffectRes : public IResEvent {
public:
    virtual void OnResEvent(event::IResEvent::PARAM const&);  // slot 0
    virtual ~EffectRes();  // slot 1
    // bit 0: loading (OnResEvent clears it); the name is not the original's
    unsigned int m_flags;  // 0x8
    unsigned char pad_c[0x44];
    // the pack OnResEvent makes from the loaded file (one reference, the destructor releases it); the name is not
    // the original's
    fw::EffectPack* m_pack;  // 0x50
};
}  // namespace event

#endif
