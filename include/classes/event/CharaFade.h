#ifndef CLASSES_EVENT_CHARAFADE_H
#define CLASSES_EVENT_CHARAFADE_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3E7D0
class CharaFade : public ::event::ICmd {
public:
    virtual ~CharaFade();  // slot 0
    virtual int update(event::ICmd::Param const&);  // slot 3
    unsigned char pad_8[0x118];  // CharaObj holds one at 0xb80; update reaches +0xd0 (its CharaObj table store at +0x10 is an AnmF32 inside it), sized up to CharaObj's next known field at +0x120
};
}  // namespace event

#endif
