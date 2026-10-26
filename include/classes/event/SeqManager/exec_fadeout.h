#ifndef CLASSES_EVENT_SEQMANAGER_EXEC_FADEOUT_H
#define CLASSES_EVENT_SEQMANAGER_EXEC_FADEOUT_H

#include "classes/event/ICmd.h"
#include "classes/event/SeqManager.h"

namespace event {
// table 0x7100B3EA38
class SeqManager::exec_fadeout : public ::event::ICmd {
public:
    virtual ~exec_fadeout() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
    virtual bool update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif
