#ifndef CLASSES_EVENT_MSTXTRES_H
#define CLASSES_EVENT_MSTXTRES_H

#include "classes/event/IResEvent.h"

namespace event {
// table 0x7100B3C5A0
class MstxtRes : public IResEvent {
public:
    virtual void OnResEvent(event::IResEvent::PARAM const&);  // slot 0
    virtual ~MstxtRes();  // slot 1
    // bit 0: loading (OnResEvent clears it), bit 1: loaded (set on a type 3 event), bit 2: its BDAT is registered (the destructor unregisters it); the name is not the original's
    unsigned int m_flags;  // 0x8
    unsigned char pad_c[0x44];
};
}  // namespace event

#endif
