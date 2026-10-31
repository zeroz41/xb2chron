#ifndef CLASSES_EVENT_CHARATURNROT_H
#define CLASSES_EVENT_CHARATURNROT_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3E450
class CharaTurnRot : public ::event::ICmd {
public:
    virtual ~CharaTurnRot() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
    virtual void init();  // slot 2
    virtual bool update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4

    // 0x8: an int, 0x10: the owner, 0x18: zeroed (CharaObj's constructor); not read here yet
    unsigned char pad_8[0x18];
};
}  // namespace event

#endif
