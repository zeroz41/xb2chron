#ifndef CLASSES_EVENT_SEQMANAGER_START_OTHER_H
#define CLASSES_EVENT_SEQMANAGER_START_OTHER_H

#include "classes/event/ICmd.h"
#include "classes/event/SeqManager.h"

namespace event {
// table 0x7100B3ECA0
class SeqManager::start_other : public ::event::ICmd {
public:
    virtual ~start_other() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
    virtual bool update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif
