#ifndef CLASSES_EVENT_SEQMANAGER_START_AREAJUMP_H
#define CLASSES_EVENT_SEQMANAGER_START_AREAJUMP_H

#include "classes/event/ICmd.h"
#include "classes/event/SeqManager.h"

namespace event {
// table 0x7100B3EC30
class SeqManager::start_areajump : public ::event::ICmd {
public:
    virtual ~start_areajump();  // slot 0
    virtual void update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif
