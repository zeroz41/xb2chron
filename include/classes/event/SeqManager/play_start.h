#ifndef CLASSES_EVENT_SEQMANAGER_PLAY_START_H
#define CLASSES_EVENT_SEQMANAGER_PLAY_START_H

#include "classes/event/ICmd.h"
#include "classes/event/SeqManager.h"

namespace event {
// table 0x7100B3EB50
class SeqManager::play_start : public ::event::ICmd {
public:
    virtual ~play_start() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
    virtual bool update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif
