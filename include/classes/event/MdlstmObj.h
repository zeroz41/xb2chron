#ifndef CLASSES_EVENT_MDLSTMOBJ_H
#define CLASSES_EVENT_MDLSTMOBJ_H

#include "classes/event/IResEvent.h"

namespace event {
// table 0x7100B3C4E8
// slot 0 OnResEvent comes from IResEvent; the destructor (out of line, D2/D0 mid-text before finishFree) is the key
// function. Size 0xF0: MdlstmManager destroys an array of them at stride 0xF0.
class MdlstmObj : public IResEvent {
public:
    virtual ~MdlstmObj();  // slot 1
    virtual void OnResEvent(event::IResEvent::PARAM const&);  // slot 0

    unsigned char pad_8[0xE8];
};
}  // namespace event

#endif
