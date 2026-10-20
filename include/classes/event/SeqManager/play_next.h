#ifndef CLASSES_EVENT_SEQMANAGER_PLAY_NEXT_H
#define CLASSES_EVENT_SEQMANAGER_PLAY_NEXT_H

#include "classes/event/ICmd.h"
#include "classes/event/SeqManager.h"

namespace event {
// table 0x7100B3EB88
class SeqManager::play_next : public ::event::ICmd {
public:
    virtual ~play_next();  // slot 0
    virtual void update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif
