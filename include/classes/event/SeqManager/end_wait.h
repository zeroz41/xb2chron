#ifndef CLASSES_EVENT_SEQMANAGER_END_WAIT_H
#define CLASSES_EVENT_SEQMANAGER_END_WAIT_H

#include "classes/event/ICmd.h"
#include "classes/event/SeqManager.h"

namespace event {
// table 0x7100B3EB18
class SeqManager::end_wait : public ::event::ICmd {
public:
    virtual ~end_wait() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
    virtual bool update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif
