#ifndef CLASSES_EVENT_MDLSTMOBJ_H
#define CLASSES_EVENT_MDLSTMOBJ_H

#include "classes/event/IResEvent.h"

namespace event {
// table 0x7100B3C4E8
// slot 0 OnResEvent comes from IResEvent; the destructor (out of line, D2/D0 mid-text before finishFree) is the key
// function. Size 0xF0: MdlstmManager destroys an array of them at stride 0xF0.
class MdlstmObj : public IResEvent {
public:
    // inline: MdlstmManager's constructor (Singleton<MdlstmManager>::getPtr) zeroes these ranges of each object
    // (0x8-0x14, 0x94-0xA5, 0xA8, 0xB0-0xE7); the field sizes inside a range are not known
    MdlstmObj()
        : pad_8(0), pad_c(0), pad_10(0), pad_14(0), pad_94(0), pad_98(0), pad_9c(0), pad_a0(0), pad_a4(0),
          pad_a8(0), pad_b0(0), pad_b8(0), pad_c0(0), pad_c8(0), pad_d0(0), pad_d8(0), pad_e0(0) {}
    virtual ~MdlstmObj();  // slot 1
    virtual void OnResEvent(event::IResEvent::PARAM const&);  // slot 0

    unsigned int pad_8;
    unsigned int pad_c;
    unsigned int pad_10;
    unsigned char pad_14;
    unsigned char pad_15[0x94 - 0x15];
    unsigned int pad_94;
    unsigned int pad_98;
    unsigned int pad_9c;
    unsigned int pad_a0;
    unsigned short pad_a4;
    unsigned int pad_a8;
    unsigned long pad_b0;
    unsigned long pad_b8;
    unsigned long pad_c0;
    unsigned long pad_c8;
    unsigned long pad_d0;
    unsigned long pad_d8;
    unsigned long pad_e0;
    unsigned char pad_e8[0xF0 - 0xE8];
};
}  // namespace event

#endif
