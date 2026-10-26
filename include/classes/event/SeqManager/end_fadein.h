#ifndef CLASSES_EVENT_SEQMANAGER_END_FADEIN_H
#define CLASSES_EVENT_SEQMANAGER_END_FADEIN_H

#include "classes/event/ICmd.h"
#include "classes/event/SeqManager.h"

namespace event {
// table 0x7100B3EE98
class SeqManager::end_fadein : public ::event::ICmd {
public:
    virtual ~end_fadein() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
    virtual bool update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif
