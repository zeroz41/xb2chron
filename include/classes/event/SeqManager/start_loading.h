#ifndef CLASSES_EVENT_SEQMANAGER_START_LOADING_H
#define CLASSES_EVENT_SEQMANAGER_START_LOADING_H

#include "classes/event/ICmd.h"
#include "classes/event/SeqManager.h"

namespace event {
// table 0x7100B3E920
class SeqManager::start_loading : public ::event::ICmd {
public:
    virtual ~start_loading() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
    virtual bool update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif
