#ifndef CLASSES_EVENT_LIPSYNCRES_H
#define CLASSES_EVENT_LIPSYNCRES_H

#include "classes/event/IResEvent.h"
#include "arc/CArcData.h"

namespace event {
// table 0x7100B3D298
class LipsyncRes : public IResEvent {
public:
    virtual void OnResEvent(event::IResEvent::PARAM const&);  // slot 0
    virtual ~LipsyncRes() {}  // slot 1
    // bit 0: loading (OnResEvent clears it), bit 1: loaded (set on a type 3 event); the name is not the original's
    unsigned int m_flags;  // 0x8
    unsigned char pad_c[0x44];
    // the loaded archive (OnResEvent sets its data); the name is not the original's
    arc::CArcData m_arc;  // 0x50
};
}  // namespace event

#endif
