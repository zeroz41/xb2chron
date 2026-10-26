#ifndef CLASSES_EVENT_SEQMANAGER_END_STREAM_H
#define CLASSES_EVENT_SEQMANAGER_END_STREAM_H

#include "classes/event/ICmd.h"
#include "classes/event/SeqManager.h"

namespace event {
// table 0x7100B3EAE0
class SeqManager::end_stream : public ::event::ICmd {
public:
    virtual ~end_stream() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
    virtual bool update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif
