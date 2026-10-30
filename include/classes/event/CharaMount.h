#ifndef CLASSES_EVENT_CHARAMOUNT_H
#define CLASSES_EVENT_CHARAMOUNT_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3E798
class CharaMount {
public:
    virtual ~CharaMount() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
    virtual void init();  // slot 2
    virtual bool update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
};
}  // namespace event

#endif
